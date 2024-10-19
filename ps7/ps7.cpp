#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "fssimplewindow.h"


class CharBitmap {
public:
    int wid, hei;
    char* pix;

    CharBitmap() : wid(0), hei(0), pix(nullptr) {}

    ~CharBitmap() {
        CleanUp();
    }

    void CleanUp() {
        delete[] pix;
        wid = 0;
        hei = 0;
        pix = nullptr;
    }

    void Create(int w, int h) {
        CleanUp();
        wid = w;
        hei = h;
        pix = new char[w * h];
        for (int i = 0; i < w * h; ++i) {
            pix[i] = 0;
        }
    }

    void SetPixel(int x, int y, char p) {
        if (x >= 0 && x < wid && y >= 0 && y < hei) {
            pix[y * wid + x] = p;
        }
    }

    char GetPixel(int x, int y) const {
        if (x >= 0 && x < wid && y >= 0 && y < hei) {
            return pix[y * wid + x];
        }
        return 0;
    }

    void Draw() const {
        for (int y = 0; y < hei; ++y) {
            for (int x = 0; x < wid; ++x) {
                char pixelValue = GetPixel(x, y);
                switch (pixelValue) {
                    case 0: glColor3ub(0, 0, 0); break;
                    case 1: glColor3ub(0, 0, 255); break;
                    case 2: glColor3ub(255, 0, 0); break;
                    case 3: glColor3ub(255, 0, 255); break;
                    case 4: glColor3ub(0, 255, 0); break;
                    case 5: glColor3ub(0, 255, 255); break;
                    case 6: glColor3ub(255, 255, 0); break;
                    case 7: glColor3ub(255, 255, 255); break;
                }
                glBegin(GL_QUADS);
                glVertex2i(x * 20, y * 20);
                glVertex2i(x * 20 + 20, y * 20);
                glVertex2i(x * 20 + 20, y * 20 + 20);
                glVertex2i(x * 20, y * 20 + 20);
                glEnd();
            }
        }
    }

    int GetWidth() const { return wid; }
    int GetHeight() const { return hei; }

    bool SaveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        file << wid << " " << hei << std::endl;
        for (int y = 0; y < hei; ++y) {
            for (int x = 0; x < wid; ++x) {
                file << static_cast<char>('0' + GetPixel(x, y));
            }
            file << std::endl;
        }

        file.close();
        return true;
    }

    bool LoadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        int newWidth, newHeight;
        file >> newWidth >> newHeight;

        if (newWidth <= 0 || newHeight <= 0 || newWidth > 64 || newHeight > 64) {
            return false;
        }

        Create(newWidth, newHeight);

        std::string line;
        std::getline(file, line); 

        for (int y = 0; y < hei; ++y) {
            std::getline(file, line);
            for (int x = 0; x < wid && x < line.length(); ++x) {
                char pixelValue = line[x] - '0';
                if (pixelValue >= 0 && pixelValue <= 7) {
                    SetPixel(x, y, pixelValue);
                }
            }
        }

        file.close();
        return true;
    }
};

std::vector <std::string> ParseString(std::string input)
{
	int state=0;
	std::vector <std::string> args;
	for(auto c : input)
	{
		if(0==state)
		{
			if(' '!=c && '\t'!=c)
			{
				std::string str;
				str.push_back(c);
				args.push_back(str);
				state=1;
			}
		}
		else
		{
			if(' '==c || '\t'==c)
			{
				state=0;
			}
			else
			{
				args.back().push_back(c);
			}
		}
	}
	return args;
}

int main() {
    CharBitmap bitmap;
    int width, height;

    while (true) {
        std::cout << "Enter Dimension> ";
        std::string input;
        std::getline(std::cin, input);

        auto args = ParseString(input);
        if (args.size() == 2) {
            width = std::stoi(args[0]);
            height = std::stoi(args[1]);
            if (width > 0 && width <= 64 && height > 0 && height <= 64) {
                break;
            }
        }
        std::cout << "Invalid input. Please enter two numbers between 1 and 64." << std::endl;
    }

    bitmap.Create(width, height);

    int windowWidth = width * 20;
    int windowHeight = height * 20;
    FsOpenWindow(0, 0, windowWidth, windowHeight, 1);

    int key = FSKEY_NULL;
    int currentColor = 0;
    int cursorX = 0, cursorY = 0;
    int lb, mb, rb, mx, my;

    while (key != FSKEY_ESC) {
        FsPollDevice();
        key = FsInkey();

        FsGetMouseState(lb, mb, rb, mx, my);

        // clamp cursorX and cursorY to the bounds of the bitmap
        cursorX = std::min(std::max(mx / 20, 0), width - 1);
        cursorY = std::min(std::max(my / 20, 0), height - 1);

        if (key >= FSKEY_0 && key <= FSKEY_7) {
            currentColor = key - FSKEY_0;
            bitmap.SetPixel(cursorX, cursorY, currentColor);
        } else if (key == FSKEY_S) {
            if (bitmap.SaveToFile("pattern.txt")) {
                std::cout << "Bitmap saved to pattern.txt" << std::endl;
            } else {
                std::cout << "Failed to save bitmap" << std::endl;
            }
        } else if (key == FSKEY_L) {
            if (bitmap.LoadFromFile("pattern.txt")) {
                std::cout << "Bitmap loaded from pattern.txt" << std::endl;
                width = bitmap.GetWidth();
                height = bitmap.GetHeight();
            } else {
                std::cout << "Failed to load bitmap" << std::endl;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        bitmap.Draw();

        // Draw lattice
        glColor3ub(255, 255, 255);  
        for (int i = 0; i <= width; ++i) {
            glBegin(GL_LINES);
            glVertex2i(i * 20, 0);
            glVertex2i(i * 20, windowHeight);
            glEnd();
        }
        for (int i = 0; i <= height; ++i) {
            glBegin(GL_LINES);
            glVertex2i(0, i * 20);
            glVertex2i(windowWidth, i * 20);
            glEnd();
        }

        // Highlight current box
        glColor3ub(255, 0, 0);  
        glBegin(GL_LINE_LOOP);
        glVertex2i(cursorX * 20, cursorY * 20);
        glVertex2i(cursorX * 20 + 20, cursorY * 20);
        glVertex2i(cursorX * 20 + 20, cursorY * 20 + 20);
        glVertex2i(cursorX * 20, cursorY * 20 + 20);
        glEnd();

        FsSwapBuffers();
        FsSleep(20);
    }

    return 0;
}

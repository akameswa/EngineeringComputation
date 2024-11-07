#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"  
#include <vector>
#include <string>

class EngineSlide {
private:
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int margin = 50;
    const int tableStartY = 150;
    const int rowHeight = 40;
    const int colWidth = 200;

    const int tableWidth = colWidth * 3;
    const int tableStartX = (windowWidth - tableWidth) / 2;

    std::vector<std::string> characteristics = {
        "Inlet Design",
        "Operating Speed", 
        "Thrust Priority",
        "Engine Type",
        "Application"
    };

    std::vector<std::string> subsonic = {
        "Thick, rounded lip",
        "Below Mach 0.8",
        "Fuel efficiency",
        "High-bypass turbofan",
        "A-10 Thunderbolt II"
    };

    std::vector<std::string> supersonic = {
        "Sharp, pointed lip",
        "Above Mach 1.0", 
        "Maximum thrust",
        "Low-bypass with afterburner",
        "NASA X-59"
    };

    YsRawPngDecoder subsonicImage;
    YsRawPngDecoder supersonicImage;

public:
    bool LoadImages(const char* subsonicFile, const char* supersonicFile) {
        if (YSOK != subsonicImage.Decode(subsonicFile) || YSOK != supersonicImage.Decode(supersonicFile)) {
            printf("Failed to load images.\n");
            return false;
        }
        subsonicImage.Flip();
        supersonicImage.Flip();
        return true;
    }

    void Draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DrawHeading();
        DrawTable();
        DrawImagePlaceholders();

        FsSwapBuffers();
    }

private:
    void DrawHeading() {
        glColor3ub(0, 0, 0);
        const char* heading = "Aircraft Engine Types: Subsonic vs Supersonic";
        int headingWidth = strlen(heading) * 12;
        int headingX = (windowWidth - headingWidth) / 2;
        glRasterPos2i(headingX, 50);
        YsGlDrawFontBitmap12x16(heading);
    }

    void DrawTable() {
        glColor3ub(0, 0, 0);
        
        for(int i = 0; i <= characteristics.size(); i++) {
            glBegin(GL_LINES);
            glVertex2i(tableStartX, tableStartY + i * rowHeight);
            glVertex2i(tableStartX + tableWidth, tableStartY + i * rowHeight);
            glEnd();
        }

        for(int i = 0; i <= 3; i++) {
            glBegin(GL_LINES);
            glVertex2i(tableStartX + i * colWidth, tableStartY);
            glVertex2i(tableStartX + i * colWidth, tableStartY + characteristics.size() * rowHeight);
            glEnd();
        }

        glRasterPos2i(tableStartX + 20, tableStartY - 20);
        YsGlDrawFontBitmap6x7("Characteristic");
        glRasterPos2i(tableStartX + colWidth + 20, tableStartY - 20);
        YsGlDrawFontBitmap6x7("Subsonic");
        glRasterPos2i(tableStartX + colWidth * 2 + 20, tableStartY - 20);
        YsGlDrawFontBitmap6x7("Supersonic");

        for(int i = 0; i < characteristics.size(); i++) {
            glRasterPos2i(tableStartX + 10, tableStartY + i * rowHeight + 25);
            YsGlDrawFontBitmap6x7(characteristics[i].c_str());
            
            glRasterPos2i(tableStartX + colWidth + 10, tableStartY + i * rowHeight + 25);
            YsGlDrawFontBitmap6x7(subsonic[i].c_str());
            
            glRasterPos2i(tableStartX + colWidth * 2 + 10, tableStartY + i * rowHeight + 25);
            YsGlDrawFontBitmap6x7(supersonic[i].c_str());
        }
    }

    void DrawImagePlaceholders() {
        const int imageWidth = 200;
        const int imageHeight = 150;
        const int spacing = 50; 
        const int totalWidth = imageWidth * 2 + spacing;
        const int startX = (windowWidth - totalWidth) / 2;
        const int imageY = tableStartY + characteristics.size() * rowHeight * 1.6 + 50;

        int subsonicImageX = startX;
        int supersonicImageX = startX + imageWidth + spacing;

        glRasterPos2i(subsonicImageX, imageY);
        glDrawPixels(subsonicImage.wid, subsonicImage.hei, GL_RGBA, GL_UNSIGNED_BYTE, subsonicImage.rgba);

        glRasterPos2i(supersonicImageX, imageY);
        glDrawPixels(supersonicImage.wid, supersonicImage.hei, GL_RGBA, GL_UNSIGNED_BYTE, supersonicImage.rgba);

        const char* subsonicCaption = "Subsonic Inlet";
        const char* supersonicCaption = "Supersonic Inlet";
        int subCaptionWidth = strlen(subsonicCaption) * 6;
        int superCaptionWidth = strlen(supersonicCaption) * 6;
        
        glColor3ub(0, 0, 0);
        glRasterPos2i(subsonicImageX + (imageWidth - subCaptionWidth)/2, 
                    imageY + 20);
        YsGlDrawFontBitmap6x7(subsonicCaption);
        
        glRasterPos2i(supersonicImageX + (imageWidth - superCaptionWidth)/2, 
                    imageY + 20);
        YsGlDrawFontBitmap6x7(supersonicCaption);
    }
};

int main(void) {
    FsOpenWindowOption opt;
    opt.x0 = 16;
    opt.y0 = 16;
    opt.wid = 800;
    opt.hei = 600;
    opt.useDoubleBuffer = true;
    FsOpenWindow(opt);

    EngineSlide slide;
    if (!slide.LoadImages("subsonic.png", "supersonic.png")) {
        return 1;
    }

    while(FsInkey() != FSKEY_ESC) {
        FsPollDevice();
        slide.Draw();
        FsSleep(25);
    }

    return 0;
}
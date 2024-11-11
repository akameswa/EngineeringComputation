/* 
Overall Instructions:
The class Slide should not be modified at all.
Each of your slides will be similar to Slide_andrewID1 or Slide_andrewID2 (feel free to edit these). Please rename the classes according to your actual andrewID
For example if your andrew ID is acar, your slide classes should be named Slide_acar1, Slide_acar2, Slide_acar3 and so on.
The classes Slide_andrewID1 and Slide_andrewID2 should be modified according to the following rules:
        Anything in Private can be changed. New functions/variables should be added here, not to public. 
        RunSlide():    
            RunSlide() will essentially serve as a substitute for the typical main function. Do not modify the arguments or Return type of this function. All the animation logic will happen here. This is the only place where you'll have the "while (FsCheckWindowOpen() && slideRunning)"
            The global slide controls should not be changed. The spacebar will be used to pause, don't change that either. You are free to change what happens to the animations on pausing/unpausing.

        Slide_andrewID1 is an example of non-interactive animation.
        Slide_andrewID2 is an example of interactive animation.
        
Most of the code comments are on Slide_andrewID1. Slide_andrewID2 is a copy of Slide_andrewID1 with some changes, which are explained in comments.
The main function should only be modified to change the number/names of slides. No other changes.

Right now, the user pause functionality for sound isn't implemented. Don't worry about this, I will make the necessary changes to class Slide (PauseAudio, ResumeAudio) later.
*/


#define M_PI 3.14
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include <iostream>
#include <cmath>
#include "ysglfontdata.h"
#include "yspng.h"  
#include <vector>
#include <string>
#include "yssimplesound.h"

/*
This enum declared globally is needed for the main function to run.
It is declared as an enum for the sake of code readability (instead of just using numbers)
DO NOT declare a new enum, append an element onto the end of this one if neccessary
*/
enum SlideTransition {
        STAY,
        NEXT,
        PREVIOUS
    };

















// DO NOT Modify this. You should only be changing Slide_andrewID1 and 2 (and adding more if necessary)
class Slide {
protected:
    YsSoundPlayer player;
    bool slideRunning = true;

public:
    Slide() {
        player.Start();
    }

    ~Slide() {
        // StopAll();  
        player.End();
    }

    void PrepAudio(YsSoundPlayer::SoundData& audio, const char *audioFile) {
        if (YSOK == audio.LoadWav(audioFile)) {
            player.PreparePlay(audio);
        }
    }

    void PlayBGMAudio(YsSoundPlayer::SoundData& audio) {

        player.PlayBackground(audio); // This is to play audio in the background (that includes voiceovers)
        
    }

    void StopAudio(YsSoundPlayer::SoundData& audio) {
        player.Stop(audio);
    }

    void StopAll(YsSoundPlayer::SoundData& audio) {
        player.Stop(audio);
        slideRunning = false;
    }

    bool IsAudioPlaying(YsSoundPlayer::SoundData& audio) {
        return player.IsPlaying(audio);
    }

    void PauseAudio(YsSoundPlayer::SoundData& audio) {
        StopAudio(audio); // Placeholder until I figure out how to pause and play
    }

    void ResumeAudio(YsSoundPlayer::SoundData& audio) {
        PlayBGMAudio(audio); // Placeholder until I figure out how to pause and play
    }

    virtual SlideTransition RunSlide() = 0;
};
















// This shows that the Slide you create (for eg: Slide1) inherits from Slide Do not change this
class Slide_andrewID1 : public Slide {
private:
    // This is where you should be declaring your variables
    double aerofoilAngle = 0.0;
    bool dragging = false;
    bool isPaused = false;
    YsSoundPlayer::SoundData audio; // If you have more than one audio file, declare audio1, audio2, etc.

public:
    // This is the class constructor
    Slide_andrewID1() : Slide() {}


    SlideTransition RunSlide() 
    /*
    This will act as a substitute for your usual main function, do all the necessary commands in here.
    DO NOT Change the return type
    The following code should be enough to run your entire slide (make sure you write code accordingly):
        Slide* currentSlide = nullptr;
        currentSlide = new Slide1();
        SlideTransition result = currentSlide->RunSlide();
    If you have a main function that contains just these 3 lines of code and your slide is displayed properly, then your code is formatted correctly.
    */
    {
        PrepAudio(audio, "crowd.wav"); // If you have more than 1 audio file, load them into audio1, audio2, etc. You'll have to call the PrepAudio fn for each of them
        PlayBGMAudio(audio);

        while (FsCheckWindowOpen() && slideRunning) {
            FsPollDevice();
            int lb, mb, rb, mx, my;
            int keyCode = FsInkey();
            FsGetMouseState(lb, mb, rb, mx, my);
            

            // Pause Control
            if (keyCode == FSKEY_SPACE) { 
                if (!isPaused) {
                    PauseAudio(audio);  // Pause audio
                    isPaused = true;
                } else {
                    ResumeAudio(audio);  // Resume audio
                    isPaused = false;
                }
            }
            player.KeepPlaying(); // This is needed to keep the music player instance alive (I think). It doesn't affect the code

            if(!isPaused)
            {
                PassiveAnimation(); // This is inside of the below loop because I don't want the animation running if Paused
            }

            Render();
            FsSleep(20);
            
            /*
            This section below takes care of global slide controls (PREV, NEXT, etc.).
            The return types are of type SlideTransition, which is a globally defined enum (declared at the very top of this code)
            If any further controls are required, modify the enum accordingly by adding your keyword to the end
            */ 
        
            if (keyCode == FSKEY_LEFT) {
                StopAll(audio); // Ideally only one audio is played at a time. If there is more than one playing, explicitly mention StopAudio() for each of them
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                return PREVIOUS;
            } else if (keyCode == FSKEY_RIGHT) {
                StopAll(audio); // Ideally only one audio is played at a time. If there is more than one playing, explicitly mention StopAudio() for each of them
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                return NEXT;
            }
        }
        return STAY;
    }

private:
/*
You can add any additional functions here, whatever is needed to make the slide functional.
Private Functions don't get inherited.
*/
    void PassiveAnimation() 
    {
        aerofoilAngle += 0.01;
    }

    void Render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawAerofoil();
        FsSwapBuffers();
    }

    void DrawAerofoil() {
    double angle = aerofoilAngle;  // Current angle of the aerofoil

    double halfWidth = 50.0;
    double halfHeight = 10.0;

    double centerX = 400.0;
    double centerY = 300.0;

    double cosAngle = cos(angle);
    double sinAngle = sin(angle);

    double x1 = centerX + (-halfWidth * cosAngle - (-halfHeight) * sinAngle);
    double y1 = centerY + (-halfWidth * sinAngle + (-halfHeight) * cosAngle);

    double x2 = centerX + (halfWidth * cosAngle - (-halfHeight) * sinAngle);
    double y2 = centerY + (halfWidth * sinAngle + (-halfHeight) * cosAngle);

    double x3 = centerX + (halfWidth * cosAngle - halfHeight * sinAngle);
    double y3 = centerY + (halfWidth * sinAngle + halfHeight * cosAngle);

    double x4 = centerX + (-halfWidth * cosAngle - halfHeight * sinAngle);
    double y4 = centerY + (-halfWidth * sinAngle + halfHeight * cosAngle);

    glColor3ub(0, 255, 0);  

    glBegin(GL_QUADS);
        glVertex2d(x1, y1);  
        glVertex2d(x2, y2);  
        glVertex2d(x3, y3);  
        glVertex2d(x4, y4);  
    glEnd();
    }
};



















class Slide_akameswa : public Slide {
private:
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int tableStartY = 150;
    const int rowHeight = 40;
    const int colWidth = 200;
    
    YsSoundPlayer::SoundData audio;
    YsSoundPlayer::SoundData subsonicWav;
    YsSoundPlayer::SoundData supersonicWav;
    YsRawPngDecoder subsonicImage;
    YsRawPngDecoder supersonicImage;
    bool isPaused = false;

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

public:
    Slide_akameswa() : Slide() {
        subsonicImage.Decode("subsonic.png");
        supersonicImage.Decode("supersonic.png");
        subsonicImage.Flip();
        supersonicImage.Flip();
        
        PrepAudio(subsonicWav, "subsonic_cut.wav");
        PrepAudio(supersonicWav, "supersonic_cut.wav");
    }

    SlideTransition RunSlide() {
        while (FsCheckWindowOpen() && slideRunning) {
            FsPollDevice();
            int lb, mb, rb, mx, my;
            int keyCode = FsInkey();
            FsGetMouseState(lb, mb, rb, mx, my);

            if (keyCode == FSKEY_SPACE) {
                if (!isPaused) {
                    StopAudio(audio);
                    isPaused = true;
                } else {
                    PlayBGMAudio(audio);
                    isPaused = false;
                }
            }

            if (lb) {
                StopAudio(supersonicWav);  
                PlayBGMAudio(subsonicWav);
            }
            if (rb) {
                StopAudio(subsonicWav);    
                PlayBGMAudio(supersonicWav);
            }

            player.KeepPlaying();
            Render();
            FsSleep(20);

            if (keyCode == FSKEY_LEFT) {
                StopAll(audio);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                return PREVIOUS;
            } else if (keyCode == FSKEY_RIGHT) {
                StopAll(audio);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                return NEXT;
            }
        }
        return STAY;
    }

private:
    void DrawTable() {
        const int tableWidth = colWidth * 3;
        const int tableStartX = (windowWidth - tableWidth) / 2;

        glColor3ub(0, 0, 0);
        
        // Draw table grid
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

        // Draw headers and content
        glRasterPos2i(tableStartX + 20, tableStartY - 20);
        YsGlDrawFontBitmap12x16("Characteristic");
        glRasterPos2i(tableStartX + colWidth + 20, tableStartY - 20);
        YsGlDrawFontBitmap12x16("Subsonic");
        glRasterPos2i(tableStartX + colWidth * 2 + 20, tableStartY - 20);
        YsGlDrawFontBitmap12x16("Supersonic");

        for(int i = 0; i < characteristics.size(); i++) {
            glRasterPos2i(tableStartX + 10, tableStartY + i * rowHeight + 25);
            YsGlDrawFontBitmap8x12(characteristics[i].c_str());
            
            glRasterPos2i(tableStartX + colWidth + 10, tableStartY + i * rowHeight + 25);
            YsGlDrawFontBitmap8x12(subsonic[i].c_str());
            
            glRasterPos2i(tableStartX + colWidth * 2 + 10, tableStartY + i * rowHeight + 25);
            YsGlDrawFontBitmap8x12(supersonic[i].c_str());
        }
    }

    void DrawImages() {
        const int imageWidth = 200;
        const int imageHeight = 150;
        const int spacing = 50;
        const int totalWidth = imageWidth * 2 + spacing;
        const int startX = (windowWidth - totalWidth) / 2;
        const int imageY = tableStartY + characteristics.size() * rowHeight * 1.6 + 50;

        glRasterPos2i(startX, imageY);
        glDrawPixels(subsonicImage.wid, subsonicImage.hei, GL_RGBA, GL_UNSIGNED_BYTE, subsonicImage.rgba);

        glRasterPos2i(startX + imageWidth + spacing, imageY);
        glDrawPixels(supersonicImage.wid, supersonicImage.hei, GL_RGBA, GL_UNSIGNED_BYTE, supersonicImage.rgba);
    }

    void Render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Draw heading
        const char* heading = "Aircraft Engine Types: Subsonic vs Supersonic";
        int headingWidth = strlen(heading) * 12;
        int headingX = (windowWidth - headingWidth) / 2;
        glRasterPos2i(headingX, 50);
        YsGlDrawFontBitmap12x16(heading);

        DrawTable();
        DrawImages();
        
        // Draw instructions
        glColor3ub(0, 0, 0);
        glRasterPos2i(50, windowHeight - 50);
        YsGlDrawFontBitmap8x12("Left Click: Play Subsonic Sound  |  Right Click: Play Supersonic Sound  |  Space: Pause/Resume");
        
        FsSwapBuffers();
    }
};
















// You should not be making any changes to the main function, apart from renaming the slides
int main() {
    FsOpenWindow(16, 16, 800, 600, true);

    int currentSlideIndex = 0;
    const int totalSlides = 2;
    Slide* currentSlide = nullptr;

    while (FsCheckWindowOpen()) {
        if (currentSlide == nullptr) {
            if (currentSlideIndex == 0) {
                currentSlide = new Slide_andrewID1(); //rename
            } else if (currentSlideIndex == 1) {
                currentSlide = new Slide_akameswa(); //rename
            }
            // If you have more/less slides, add that here. You should not be changing anything else in the main function
        }

        SlideTransition result = currentSlide->RunSlide();

        if (result == NEXT && currentSlideIndex < totalSlides - 1) {
            delete currentSlide;
            currentSlide = nullptr;
            currentSlideIndex++;
        } else if (result == PREVIOUS && currentSlideIndex > 0) {
            delete currentSlide;
            currentSlide = nullptr;
            currentSlideIndex--;
        } else if (result == STAY) {
            break;
        }
    }

    delete currentSlide;
    return 0;
}



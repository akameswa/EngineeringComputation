#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"  
#include <vector>
#include <string>
#include "yssimplesound.h"

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
    
    const int buttonWidth = 200;
    const int buttonHeight = 40;
    const int buttonSpacing = 50;

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
    YsSoundPlayer soundPlayer;
    YsSoundPlayer::SoundData subsonicWav;
    YsSoundPlayer::SoundData supersonicWav;
    YsSoundPlayer::SoundData narrationWav;
    bool isNarrationPlaying;

public:
    EngineSlide() : isNarrationPlaying(false) {}

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
        DrawButtons();
        FsSwapBuffers();
    }

    bool LoadResources(const char* subsonicImgFile, const char* supersonicImgFile,
                      const char* subsonicSndFile, const char* supersonicSndFile) {
        if (YSOK != subsonicImage.Decode(subsonicImgFile) || 
            YSOK != supersonicImage.Decode(supersonicImgFile)) {
            printf("Failed to load images.\n");
            return false;
        }

        subsonicImage.Flip();
        supersonicImage.Flip();

        soundPlayer.Start();
        if (YSOK != subsonicWav.LoadWav(subsonicSndFile) ||
            YSOK != supersonicWav.LoadWav(supersonicSndFile) ||
            YSOK != narrationWav.LoadWav("narration.wav")) {
            printf("Failed to load audio files.\n");
            return false;
        }

        soundPlayer.PlayBackground(narrationWav);
        isNarrationPlaying = true;

        return true;
    }

    void ToggleNarration() {
        if (isNarrationPlaying) {
            soundPlayer.Stop(narrationWav);
            isNarrationPlaying = false;
        } else {
            soundPlayer.PlayBackground(narrationWav);
            isNarrationPlaying = true;
        }
    }

    void CleanUp() {
        soundPlayer.Stop(narrationWav);
        soundPlayer.End();
    }

    void StopAllSounds() {
        soundPlayer.Stop(subsonicWav);
        soundPlayer.Stop(supersonicWav);
    }

    void HandleClick(int mx, int my) {
        int key = FsInkey();
        if (key == 'm') {
            StopAllSounds();
            soundPlayer.PlayOneShot(subsonicWav);
        }
        else if (key == 'n') {
            StopAllSounds();
            soundPlayer.PlayOneShot(supersonicWav);
        }

        int buttonY = tableStartY + characteristics.size() * rowHeight * 1.6 + 250;
        int subsonicX = (windowWidth - 2 * buttonWidth - buttonSpacing) / 2;
        int supersonicX = subsonicX + buttonWidth + buttonSpacing;

        if (mx >= subsonicX && mx <= subsonicX + buttonWidth &&
            my >= buttonY && my <= buttonY + buttonHeight) {
            StopAllSounds();
            soundPlayer.PlayOneShot(subsonicWav);
        }
        else if (mx >= supersonicX && mx <= supersonicX + buttonWidth &&
                my >= buttonY && my <= buttonY + buttonHeight) {
            StopAllSounds();
            soundPlayer.PlayOneShot(supersonicWav);
        }
    }

    void PlaySubsonicSound() {
        StopAllSounds();
        soundPlayer.PlayOneShot(subsonicWav);
    }

    void PlaySupersonicSound() {
        StopAllSounds();
        soundPlayer.PlayOneShot(supersonicWav);
    }

private:
    void DrawButtons() {
        const int charWidth = 8;  
        const int spacing = 50;
        const int buttonPadding = 20;  
        
        const char* subText = "Press M to play Subsonic";
        const char* superText = "Press N to play Supersonic";
        
        const int subTextWidth = strlen(subText) * charWidth;
        const int superTextWidth = strlen(superText) * charWidth;
        const int subButtonWidth = subTextWidth + 2 * buttonPadding;
        const int superButtonWidth = superTextWidth + 2 * buttonPadding;

        const int totalWidth = subButtonWidth + superButtonWidth + spacing;
        const int startX = (windowWidth - totalWidth) / 2;
        const int buttonY = tableStartY + characteristics.size() * rowHeight * 1.6 + 75;

        int subsonicX = startX;
        int supersonicX = startX + subButtonWidth + spacing;

        glColor3ub(200, 200, 200);
        glBegin(GL_QUADS);
        glVertex2i(subsonicX, buttonY);
        glVertex2i(subsonicX + subButtonWidth, buttonY);
        glVertex2i(subsonicX + subButtonWidth, buttonY + buttonHeight);
        glVertex2i(subsonicX, buttonY + buttonHeight);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2i(supersonicX, buttonY);
        glVertex2i(supersonicX + superButtonWidth, buttonY);
        glVertex2i(supersonicX + superButtonWidth, buttonY + buttonHeight);
        glVertex2i(supersonicX, buttonY + buttonHeight);
        glEnd();

        glColor3ub(0, 0, 0);
        glRasterPos2i(subsonicX + buttonPadding, buttonY + 25);
        YsGlDrawFontBitmap8x12(subText);
        
        glRasterPos2i(supersonicX + buttonPadding, buttonY + 25);
        YsGlDrawFontBitmap8x12(superText);

        glColor3ub(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(subsonicX, buttonY);
        glVertex2i(subsonicX + subButtonWidth, buttonY);
        glVertex2i(subsonicX + subButtonWidth, buttonY + buttonHeight);
        glVertex2i(subsonicX, buttonY + buttonHeight);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2i(supersonicX, buttonY);
        glVertex2i(supersonicX + superButtonWidth, buttonY);
        glVertex2i(supersonicX + superButtonWidth, buttonY + buttonHeight);
        glVertex2i(supersonicX, buttonY + buttonHeight);
        glEnd();
    }

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
    }
};

int main(void) {
    FsOpenWindow(16, 16, 800, 600, 1);
    EngineSlide slide;
    
    if (!slide.LoadResources("subsonic.png", "supersonic.png",
                            "subsonic_cut.wav", "supersonic_cut.wav")) {
        return 1;
    }

    while(FsInkey() != FSKEY_ESC) {
        FsPollDevice();
        
        int key = FsInkey();
        if (key == FSKEY_M) {
            slide.PlaySubsonicSound();
        }
        else if (key == FSKEY_N) {
            slide.PlaySupersonicSound();
        }
        else if (key == FSKEY_SPACE) {
            slide.ToggleNarration();
        }
        
        slide.Draw();
        FsSleep(25);
    }

    slide.CleanUp();
    return 0;
}
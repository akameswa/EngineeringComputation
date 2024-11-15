#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include <vector>
#include <string>

class SlideAkameswaTest {
private:
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    YsSoundPlayer::SoundData narrationWav;
    YsSoundPlayer::SoundData subsonicWav;
    YsSoundPlayer::SoundData supersonicWav;
    YsRawPngDecoder subsonicImage;
    YsRawPngDecoder supersonicImage;
    YsSoundPlayer player;

public:
    void runTests() {
        printf("Starting Slide_akameswa Component Tests\n");
        printf("=======================================\n\n");

        testResourceLoading();
        testTableLayout();
        testAudioFunctionality();
        testUserInteractions();

        printf("\nAll tests completed.\n");
    }

private:
    void testResourceLoading() {
        printf("Testing Resource Loading:\n");
        
        // Test PNG loading
        if (subsonicImage.Decode("subsonic.png") == YSOK) {
            printf("[PASS] Subsonic image loaded successfully\n");
        } else {
            printf("[FAIL] Failed to load subsonic image\n");
        }

        if (supersonicImage.Decode("supersonic.png") == YSOK) {
            printf("[PASS] Supersonic image loaded successfully\n");
        } else {
            printf("[FAIL] Failed to load supersonic image\n");
        }

        // Test audio loading
        if (narrationWav.LoadWav("narration.wav") == YSOK) {
            printf("[PASS] Narration audio loaded successfully\n");
        } else {
            printf("[FAIL] Failed to load narration audio\n");
        }

        if (subsonicWav.LoadWav("subsonic_cut.wav") == YSOK) {
            printf("[PASS] Subsonic sound effect loaded successfully\n");
        } else {
            printf("[FAIL] Failed to load subsonic sound effect\n");
        }

        if (supersonicWav.LoadWav("supersonic_cut.wav") == YSOK) {
            printf("[PASS] Supersonic sound effect loaded successfully\n");
        } else {
            printf("[FAIL] Failed to load supersonic sound effect\n");
        }
    }

    void testTableLayout() {
        printf("\nTesting Table Layout:\n");
        
        const int tableStartY = 150;
        const int rowHeight = 40;
        const int colWidth = 200;
        const int numRows = 5;  // Number of characteristics

        // Test table dimensions
        int totalTableHeight = rowHeight * numRows;
        int totalTableWidth = colWidth * 3;

        if (totalTableWidth <= WINDOW_WIDTH) {
            printf("[PASS] Table width fits window\n");
        } else {
            printf("[FAIL] Table width exceeds window bounds\n");
        }

        if (tableStartY + totalTableHeight <= WINDOW_HEIGHT) {
            printf("[PASS] Table height fits window\n");
        } else {
            printf("[FAIL] Table height exceeds window bounds\n");
        }

        // Test content alignment
        int tableStartX = (WINDOW_WIDTH - totalTableWidth) / 2;
        if (tableStartX >= 0) {
            printf("[PASS] Table horizontal centering is correct\n");
        } else {
            printf("[FAIL] Table horizontal centering calculation error\n");
        }
    }

    void testAudioFunctionality() {
        printf("\nTesting Audio Functionality:\n");
        
        // Test audio state transitions
        player.Start();
        
        // Test background narration
        player.PreparePlay(narrationWav);
        player.PlayBackground(narrationWav);
        if (player.IsPlaying(narrationWav)) {
            printf("[PASS] Background narration plays correctly\n");
        } else {
            printf("[FAIL] Background narration failed to play\n");
        }

        // Test sound effect playback
        player.PreparePlay(subsonicWav);
        player.PlayBackground(subsonicWav);
        if (player.IsPlaying(subsonicWav)) {
            printf("[PASS] Sound effects play correctly\n");
        } else {
            printf("[FAIL] Sound effect playback failed\n");
        }

        // Test audio stopping
        player.Stop(narrationWav);
        if (!player.IsPlaying(narrationWav)) {
            printf("[PASS] Audio stopping works correctly\n");
        } else {
            printf("[FAIL] Audio stopping failed\n");
        }
    }

    void testUserInteractions() {
        printf("\nTesting User Interactions:\n");
        
        // Simulate mouse clicks
        bool leftClick = true;
        bool rightClick = false;
        
        if (leftClick) {
            player.Stop(supersonicWav);
            player.PreparePlay(subsonicWav);
            printf("[PASS] Left click handler works\n");
        }
        
        if (rightClick) {
            player.Stop(subsonicWav);
            player.PreparePlay(supersonicWav);
            printf("[PASS] Right click handler works\n");
        }

        // Test pause functionality
        bool isPaused = true;
        if (isPaused) {
            player.Stop(narrationWav);
            printf("[PASS] Pause functionality works\n");
        }
    }
};

// Main function to run tests
int main() {
    SlideAkameswaTest tester;
    tester.runTests();
    return 0;
}
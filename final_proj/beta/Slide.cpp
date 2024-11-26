#include "slide.h"
#include "saisravy.h"
#include "sselvam.h"
#include "abadagab.h"
#include "akameswa.h"
#include "acar.h"


int main() {
    FsOpenWindow(16, 16, 800, 600, true);

    int currentSlideIndex = 0;
    const int totalSlides = 15;
    Slide* currentSlide = nullptr;

    while (FsCheckWindowOpen()) {
        if (currentSlide == nullptr) {
            if (currentSlideIndex == 0) {
                currentSlide = new Slide_sselvam1(); //rename
            } else if (currentSlideIndex == 1) {
                currentSlide = new Slide_sselvam2(); //rename
            } else if (currentSlideIndex == 2) {
                currentSlide = new Slide_sselvam3(); //rename
            } else if (currentSlideIndex == 3) {
                currentSlide = new saisravy_slide1_intro(); //rename
            } else if (currentSlideIndex == 4) {
                currentSlide = new saisravy_slide1; //rename
            } else if (currentSlideIndex == 5) {
                currentSlide = new saisravy_slide2; //rename
            } else if (currentSlideIndex == 6) {
                currentSlide = new saisravy_slide3_intro(); //rename
            } else if (currentSlideIndex == 7) {
                currentSlide = new saisravy_slide3; //rename
            } else if (currentSlideIndex == 8) {
                currentSlide = new abadagab_slide1; //rename
            } else if (currentSlideIndex == 9) {
                currentSlide = new abadagab_slide2; //rename
            }  else if (currentSlideIndex == 10) {
                currentSlide = new abadagab_slide3; //rename
            }  else if (currentSlideIndex == 11) {
                currentSlide = new abadagab_slide4; //rename
            }  else if (currentSlideIndex == 12) {
                currentSlide = new abadagab_slide5; //rename
            }  else if (currentSlideIndex == 13) {
                currentSlide = new Slide_akameswa; //rename
            }  else if (currentSlideIndex == 14) {
                currentSlide = new Slide_acar1; //rename
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
        } else if (result == EXIT || (result == NEXT && currentSlideIndex == totalSlides - 1)) {
            break;
        }
    }

    delete currentSlide;
    return 0;
}



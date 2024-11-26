#ifndef SLIDE_H
#define SLIDE_H

#include "yssimplesound.h"
#include "yssimplesound.h"

enum SlideTransition {
    EXIT,
    NEXT,
    PREVIOUS,
    STAY,
};

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

    void PrepAudio(YsSoundPlayer::SoundData& audio, const char* audioFile) {
        if (YSOK == audio.LoadWav(audioFile)) {
            player.PreparePlay(audio);
        }
    }

    void PlayBGMAudio(YsSoundPlayer::SoundData& audio) {

        player.PlayOneShot(audio); // This is to play audio in the background 
        
    }

    void PlayForever(YsSoundPlayer::SoundData& audio) {

        player.PlayBackground(audio); // This is to play audio once (that includes voiceovers)
        
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

#endif 

#include "fssimplewindow.h"
#include "yssimplesound.h"
#include <stdio.h>
#include <string>
#include <iostream>

int main(void)
{
    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav;

	FsChangeToProgramDir();

    if(YSOK!=wav.LoadWav("o4cdefgab.wav"))
    {
        printf("Failed to read WAV file\n");
        return 1;
    }

    player.Start();
    player.PlayOneShot(wav);  // <-> Use PlayBackground if you want to repeat automatically.
    while(YSTRUE==player.IsPlaying(wav))
    {
        player.KeepPlaying();

		double pos=player.GetCurrentPosition(wav);
		printf("%lf\n",pos);
    }

    player.End();
    return 0;
}

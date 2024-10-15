#include "yssimplesound.h"
#include <stdio.h>
#include <string>
#include <iostream>

int main(void)
{
    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav;

	std::string fName;
    std::cout << "WAV File Name:";
    std::getline(std::cin,fName);

    if(YSOK!=wav.LoadWav(fName.c_str()))
    {
        printf("Failed to read %s\n",fName);
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

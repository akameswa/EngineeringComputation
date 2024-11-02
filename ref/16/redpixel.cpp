#include <stdio.h>
#include <algorithm>
#include "fssimplewindow.h"
#include "yspng.h"

void RedPixel(YsRawPngDecoder &png)
{
	// png.wid
	// png.hei
	// png.rgba
	for(int i=0; i<png.wid*png.hei; ++i)
	{
		auto *pix=png.rgba+i*4;

		if(200<pix[0] && pix[1]<200 && pix[2]<200)
		{
		}
		else
		{
			pix[0]=255;
			pix[1]=255;
			pix[2]=255;
		}
	}
}

int main(void)
{
	FsChangeToProgramDir();

    YsRawPngDecoder png;
    if(YSOK==png.Decode("ClarkY.png"))
    {
		printf("Wid %d Hei %d\n",png.wid,png.hei);
	}
	else
	{
		printf("Failed to open file.\n");
		return 1;
	}
	png.Flip();

	FsOpenWindow(0,0,png.wid,png.hei,1);
	for(;;)
	{
		FsPollDevice();
		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		if(FSKEY_SPACE==key)
		{
			RedPixel(png);
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glRasterPos2i(0,png.hei-1);
		glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
		FsSwapBuffers();
	}

	return 0;
}

#include <stdio.h>
#include <algorithm>
#include "fssimplewindow.h"
#include "yspng.h"
#include <algorithm>

void Sort(int n,int x[])
{
	for(int i=0; i<n; ++i)
	{
		for(int j=i+1; j<n; ++j)
		{
			if(x[i]>x[j])
			{
				std::swap(x[i],x[j]);
			}
		}
	}
}

void Median(YsRawPngDecoder &png)
{
	for(int i=0; i<png.wid*png.hei; ++i)
	{
		int x=i%png.wid;
		int y=i/png.wid;

		for(int j=0; j<3; ++j)
		{
			int ctr=0;
			int sample[9];
			for(int dx=-1; dx<=1; ++dx)
			{
				for(int dy=-1; dy<=1; ++dy)
				{
					int X=x+dx;
					int Y=y+dy;
					if(0<=X && X<png.wid && 0<=Y && Y<png.hei)
					{
						auto *pix=png.rgba+(Y*png.wid+X)*4;
						sample[ctr++]=pix[j];
					}
				}
			}
			Sort(ctr,sample);
			auto *pix=png.rgba+(y*png.wid+x)*4;
			pix[j]=sample[ctr/2];
		}
	}
}

int main(int ac,char *argv[])
{
    YsRawPngDecoder png;
	if(2<=ac)
	{
	    if(YSOK==png.Decode(argv[1]))
	    {
			printf("Wid %d Hei %d\n",png.wid,png.hei);
		}
		else
		{
			printf("Failed to open file.\n");
			return 1;
		}
	}
	else
	{
		printf("Need file name.\n");
		return 1;
	}

	png.Flip();


	double w=0.5;

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
			Median(png);
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glRasterPos2i(0,png.hei-1);
		glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
		FsSwapBuffers();
	}

	return 0;
}

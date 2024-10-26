#include <stdio.h>
#include <algorithm>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"


void MakeHistogram(unsigned int hist[256],const YsRawPngDecoder &png)
{
	for(int i=0; i<256; ++i)
	{
		hist[i]=0;
	}
	for(int i=0; i<png.wid*png.hei; ++i)
	{
		auto r=png.rgba[i*4];
		auto g=png.rgba[i*4+1];
		auto b=png.rgba[i*4+2];
		hist[r]=hist[r]+1;
		hist[g]=hist[g]+1;
		hist[b]=hist[b]+1;
	}
}

void PrintHistogram(const unsigned int hist[256])
{
	int maxNum=0;
	for(int i=0; i<256; ++i)
	{
		maxNum=std::max<unsigned int>(maxNum,hist[i]);
	}

	for(int i=0; i<256; ++i)
	{
		printf("%3d:",i);

		int len;
		len=hist[i]*80/maxNum;
		for(int j=0; j<len; ++j)
		{
			printf("#");
		}
		printf("\n");
	}
}

void FindThreshold(int minmax[2],const unsigned int hist[256])
{
	unsigned total=0;
	for(int i=0; i<256; ++i)
	{
		total+=hist[i];
	}

	unsigned sum=0;
	for(int i=0; i<256; ++i)
	{
		sum+=hist[i];
		if(total/100<=sum)
		{
			minmax[0]=i;
			break;
		}
	}
	sum=0;
	for(int i=255; 0<=i; --i)
	{
		sum+=hist[i];
		if(total/100<=sum)
		{
			minmax[1]=i;
			break;
		}
	}
}

unsigned char Expand(int in,int minmax[2])
{
	if(minmax[0]!=minmax[1])
	{
		int out;
		out=(in-minmax[0])*255/(minmax[1]-minmax[0]);
		if(out<0)
		{
			return 0;
		}
		if(255<out)
		{
			return 255;
		}
		return out;
	}
	return 0;
}

void IncreaseContrast(YsRawPngDecoder &png)
{
	unsigned int hist[256];
	MakeHistogram(hist,png);

	int minmax[2];
	FindThreshold(minmax,hist);

	for(int i=0; i<png.wid*png.hei; ++i)
	{
		png.rgba[i*4  ]=Expand(png.rgba[i*4],minmax);
		png.rgba[i*4+1]=Expand(png.rgba[i*4+1],minmax);
		png.rgba[i*4+2]=Expand(png.rgba[i*4+2],minmax);
	}
}

int main(void)
{
	FsChangeToProgramDir();

    YsRawPngDecoder png;
    if(YSOK==png.Decode("imagesample1.png"))
    {
		printf("Wid %d Hei %d\n",png.wid,png.hei);
	}
	else
	{
		printf("Failed to open file.\n");
		return 1;
	}
	png.Flip();

	unsigned int hist[256];
	MakeHistogram(hist,png);
	PrintHistogram(hist);

	int minmax[2];
	FindThreshold(minmax,hist);
	printf("Min %d  Max %d\n",minmax[0],minmax[1]);

	FsOpenWindow(0,0,png.wid,png.hei,1);
	for(;;)
	{
		FsPollDevice();
		int key=FsInkey();

		if(FSKEY_ESC==key)
		{
			break;
		}
		if(FSKEY_SPACE==key)
		{
			IncreaseContrast(png);

			YsRawPngEncoder encoder;
			png.Flip();
			encoder.EncodeToFile("output.png",png.wid,png.hei,8,6,png.rgba);
			png.Flip();
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glRasterPos2i(0,png.hei-1);
		glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
		FsSwapBuffers();
	}

	return 0;
}

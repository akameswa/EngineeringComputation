#include <stdio.h>
#include <algorithm>
#include "fssimplewindow.h"
#include "yspng.h"


double ApplyCurveFilter(double x,double w)
{
	return (2.0-4.0*w)*x*x+(4.0*w-1.0)*x;
}

inline int Bound(int i,int MIN,int MAX)
{
	if(i<MIN)
	{
		return MIN;
	}
	if(MAX<i)
	{
		return MAX;
	}
	return i;
}

void Curve(YsRawPngDecoder &png,double w)
{
	for(int i=0; i<png.wid*png.hei; ++i)
	{
		auto *pix=png.rgba+i*4;

		double r,g,b;
		r=pix[0];
		g=pix[1];
		b=pix[2];

		r/=255.0;
		g/=255.0;
		b/=255.0;

		r=ApplyCurveFilter(r,w);
		g=ApplyCurveFilter(g,w);
		b=ApplyCurveFilter(b,w);

		int R,G,B;
		R=(int)(r*255.0);
		G=(int)(g*255.0);
		B=(int)(b*255.0);

		pix[0]=Bound(R,0,255);
		pix[1]=Bound(G,0,255);
		pix[2]=Bound(B,0,255);
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

		if(FSKEY_DOWN==key && 0.1<w)
		{
			w-=0.1;
			png.Decode(argv[1]);
			png.Flip();
			Curve(png,w);
		}
		else if(FSKEY_UP==key && w<0.9)
		{
			w+=0.1;
			png.Decode(argv[1]);
			png.Flip();
			Curve(png,w);
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glRasterPos2i(0,png.hei-1);
		glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
		FsSwapBuffers();
	}

	return 0;
}

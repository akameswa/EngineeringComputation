#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	int N=100000000;
	int K=0;

	srand(time(nullptr));

	FsOpenWindow(0,0,500,500,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	const int NPlot=100;
	double xy[NPlot][2];
	int inout[NPlot];

	for(int i=0; i<N; ++i)
	{
		int x=rand();
		int y=rand();

		double X=double(x)/(double)RAND_MAX;
		double Y=double(y)/(double)RAND_MAX;

		xy[i%NPlot][0]=X;
		xy[i%NPlot][1]=Y;

		if(X*X+Y*Y<=1.0)
		{
			inout[i%NPlot]=1;
			++K;
		}
		else
		{
			inout[i%NPlot]=0;
		}


		if(i%NPlot==(NPlot-1))
		{
			glBegin(GL_POINTS);
			for(int i=0; i<NPlot; ++i)
			{
				if(1==inout[i])
				{
					glColor3f(0,0,1);
				}
				else
				{
					glColor3f(1,0,0);
				}
				glVertex2d(X*500.0,Y*500.0);
			}
			glEnd();

			glColor3f(1,1,1);
			glBegin(GL_QUADS);
			glVertex2i(0,0);
			glVertex2i(120,0);
			glVertex2i(120,16);
			glVertex2i(0,16);
			glEnd();

			glColor3f(0,0,0);
			double PI=4.0*double(K)/double(i);
			char str[256];
			sprintf(str,"%lf",PI);
			glRasterPos2i(0,16);
			YsGlDrawFontBitmap12x16(str);

			glFlush();
		}
	}

	// K=N*(0.25*PI*1.0^2)
	double PI=4.0*double(K)/double(N);

	printf("PI=%lf\n",PI);
	return 0;
}

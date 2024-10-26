#include <stdio.h>
#include <math.h>
#include "yspng.h"
#include "fssimplewindow.h"

const double PI=3.1415927;

class MainData
{
public:
    YsRawPngDecoder png[2];
    GLuint texId[2];
    double angle=0;
};

void Render(MainData &data)
{
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor4d(1.0,1.0,1.0,1.0);

    glEnable(GL_TEXTURE_2D);  // Begin using texture mapping


    glBindTexture(GL_TEXTURE_2D,data.texId[1]);

    glBegin(GL_QUADS);

    glTexCoord2d(0.0,0.0);
    glVertex2i(0,0);

    glTexCoord2d(1.0,0.0);
    glVertex2i(800,0);

    glTexCoord2d(1.0,1.0);
    glVertex2i(800,600);

    glTexCoord2d(0.0,1.0);
    glVertex2i(0,600);

    glEnd();



    glBindTexture(GL_TEXTURE_2D,data.texId[0]);

    glBegin(GL_QUADS);

    glTexCoord2d(0.0,0.0);   // For each vertex, assign texture coordinate before vertex coordinate.
    glVertex2d(400.0+200.0*cos(data.angle),300.0-200.0*sin(data.angle));

    glTexCoord2d(1.0,0.0);
    glVertex2d(400.0+200.0*cos(data.angle+PI/2.0),300.0-200.0*sin(data.angle+PI/2.0));

    glTexCoord2d(1.0,1.0);
    glVertex2d(400.0+200.0*cos(data.angle+PI),300.0-200.0*sin(data.angle+PI));

    glTexCoord2d(0.0,1.0);
    glVertex2d(400.0+200.0*cos(data.angle-PI/2.0),300.0-200.0*sin(data.angle-PI/2.0));

    glEnd();

    glDisable(GL_TEXTURE_2D);  // End using texture mapping

    FsSwapBuffers();
}

int main(void)
{
    FsChangeToProgramDir();

	MainData data;
	data.png[0].Decode("imagesample1.png");
	data.png[1].Decode("imagesample2.png");

    FsOpenWindow(16,16,800,600,1);

    // glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.

	for(int i=0; i<2; ++i)
	{
	    glGenTextures(1,&data.texId[i]);  // Reserve one texture identifier
	    glBindTexture(GL_TEXTURE_2D,data.texId[i]);  // Making the texture identifier current (or bring it to the deck)

	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	    glTexImage2D
	        (GL_TEXTURE_2D,
	         0,    // Level of detail
	         GL_RGBA,
	         data.png[i].wid,
	         data.png[i].hei,
	         0,    // Border width, but not supported and needs to be 0.
	         GL_RGBA,
	         GL_UNSIGNED_BYTE,
	         data.png[i].rgba);
	}

    int key=FSKEY_NULL;
    while(FSKEY_ESC!=key)
    {
        FsPollDevice();
        key=FsInkey();
        data.angle+=0.01;
        Render(data);
        FsSleep(25);
    }

    return 0;
}



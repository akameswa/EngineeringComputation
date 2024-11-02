#include <stdio.h>
#include "fssimplewindow.h"
#include "yspng.h"

void Binarize(YsRawPngDecoder &png)
{
    for(int i=0; i<png.wid*png.hei; ++i)
    {
        auto *pix=png.rgba+i*4;
        
        if(pix[0] < 220 || pix[1] < 220 || pix[2] < 220)
        {
            pix[0]=0;
            pix[1]=0;
            pix[2]=0;
        }
        else
        {
            pix[0]=255;
            pix[1]=255;
            pix[2]=255;
        }
    }
}

void ExtractContour(YsRawPngDecoder &png)
{
    // First mark contour pixels by clearing their green component
    for(int y=1; y<png.hei-1; ++y)
    {
        for(int x=1; x<png.wid-1; ++x)
        {
            auto *pix=png.rgba+(y*png.wid+x)*4;
            
            // Check if current pixel is white (255)
            if(pix[0]==255)
            {
                // Check all 8 neighbors
                bool hasBlackNeighbor=false;
                for(int dy=-1; dy<=1; ++dy)
                {
                    for(int dx=-1; dx<=1; ++dx)
                    {
                        if(dx!=0 || dy!=0)
                        {
                            auto *neighbor=png.rgba+((y+dy)*png.wid+(x+dx))*4;
                            if(neighbor[0]==0) // If any neighbor is black
                            {
                                hasBlackNeighbor=true;
                                break;
                            }
                        }
                    }
                    if(hasBlackNeighbor)
                        break;
                }
                
                if(!hasBlackNeighbor)
                {
                    pix[1]=0; // Clear green to mark non-contour
                }
            }
        }
    }

    // Copy green channel status to all channels
    for(int i=0; i<png.wid*png.hei; ++i)
    {
        auto *pix=png.rgba+i*4;
        if(pix[1]==0)
        {
            pix[0]=0;
            pix[2]=0;
        }
    }
}

int main(void)
{
    FsChangeToProgramDir();

    YsRawPngDecoder png;
    if(YSOK==png.Decode("ps9.png"))
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
            Binarize(png);
        }
        else if(FSKEY_ENTER==key)
        {
            ExtractContour(png);
        }

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glRasterPos2i(0,png.hei-1);
        glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        FsSwapBuffers();
    }

    return 0;
}

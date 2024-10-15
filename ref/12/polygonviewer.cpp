#include "fssimplewindow.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>  // #include <cstdlib>



std::vector <std::string> ParseString(std::string input)
{
	int state=0;
	std::vector <std::string> args;
	for(auto c : input)
	{
		if(0==state)
		{
			if(' '!=c && '\t'!=c)
			{
				std::string str;
				str.push_back(c);
				args.push_back(str);
				state=1;
			}
		}
		else
		{
			if(' '==c || '\t'==c)
			{
				state=0;
			}
			else
			{
				args.back().push_back(c);
			}
		}
	}
	return args;
}



class Pollygon
{
protected:
	int nVtx=0;
	int *vtx=nullptr;

public:
	Pollygon();
	~Pollygon();
	void CleanUp(void);

	bool Open(std::string fileName);
	void Draw(void);
};

Pollygon::Pollygon()
{
}
Pollygon::~Pollygon()
{
	CleanUp();
}
void Pollygon::CleanUp(void)
{
	if(nullptr!=vtx)
	{
		delete [] vtx;
	}
	vtx=nullptr;
	nVtx=0;
}

bool Pollygon::Open(std::string fileName)
{
	// With C standard library
	// FILE *fp=fopen(fileName.c_str(),"r");
	// if(nullptr!=fp)
	// {
	// 	char str[256];
	// 	while(nullptr!=fgets(str,255,fp))
	// 	{
	// 	}
	// 	fclose(fp);
	// }


	std::ifstream ifp(fileName);
	if(true==ifp.is_open())
	{
		std::string str;
		std::getline(ifp,str);

		CleanUp();

		nVtx=atoi(str.c_str());
		vtx=new int [nVtx*2];

		std::cout << nVtx << "\n";

		int nRead=0;
		while(true!=ifp.eof() && nRead<nVtx)
		{
			std::getline(ifp,str);
			auto argv=ParseString(str);
			if(2<=argv.size())
			{
				// vtx[0] is x1
				// vtx[1] is y1
				// vtx[2] is x2
				// vtx[3] is y2
				vtx[nRead*2  ]=atoi(argv[0].c_str());
				vtx[nRead*2+1]=atoi(argv[1].c_str());

				std::cout << vtx[nRead*2] << " " << vtx[nRead*2+1] << "\n";

				++nRead;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Pollygon::Draw(void)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<nVtx; ++i)
	{
		glVertex2i(vtx[i*2],vtx[i*2+1]);
	}
	glEnd();
}




int main(void)
{
	Pollygon plg;

	FsOpenWindow(0,0,800,600,1);

	FsChangeToProgramDir();
	plg.Open("cardinal.txt");
	plg.Open("cardinal.txt");

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		plg.Draw();
		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}

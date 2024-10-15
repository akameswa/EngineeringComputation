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



class Mesh
{
public:
	class Node
	{
	public:
		double v[2];
	};
	class Triangle
	{
	public:
		int ndId[3];
	};

protected:
	int nNodes=0;
	int nTris=0;
	Node *nodes=nullptr;
	Triangle *tris=nullptr;

public:
	Mesh();
	~Mesh();
	void CleanUp(void);

	bool Open(char fileName[]);
	void Draw(void);
};

Mesh::Mesh()
{
}
Mesh::~Mesh()
{
	CleanUp();
}
void Mesh::CleanUp(void)
{
	if(nullptr!=nodes)
	{
		delete [] nodes;
	}
	if(nullptr!=tris)
	{
		delete [] tris;
	}
	nNodes=0;
	nTris=0;
	nodes=nullptr;
	tris=nullptr;
}

bool Mesh::Open(char fileName[])
{
	FILE *fp=fopen(fileName,"r");
	if(nullptr!=fp)
	{
		CleanUp();

		char str[256];
		int nNodeRead=0,nTrisRead=0;
		while(nullptr!=fgets(str,255,fp))
		{
			auto argv=ParseString(str);
			if(3<=argv.size() && "N"==argv[0])
			{
				if(nNodeRead<nNodes)
				{
					nodes[nNodeRead].v[0]=atof(argv[1].c_str());
					nodes[nNodeRead].v[1]=atof(argv[2].c_str());
					++nNodeRead;
				}
			}
			else if(4<=argv.size() && "D"==argv[0])
			{
				if(nTrisRead<nTris)
				{
					tris[nTrisRead].ndId[0]=atoi(argv[1].c_str());
					tris[nTrisRead].ndId[1]=atoi(argv[2].c_str());
					tris[nTrisRead].ndId[2]=atoi(argv[3].c_str());
					++nTrisRead;
				}
			}
			else if(2<=argv.size() && "NNODE"==argv[0] && nullptr==nodes)
			{
				nNodes=atoi(argv[1].c_str());
				nodes=new Node [nNodes];
			}
			else if(2<=argv.size() && "NELEM"==argv[0] && nullptr==tris)
			{
				nTris=atoi(argv[1].c_str());
				tris=new Triangle [nTris];
			}
		}
		fclose(fp);
		return true;
	}
	else
	{
		return false;
	}
}

void Mesh::Draw(void)
{
	glColor3f(0.2,0.2,0.6);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<nTris; ++i)
	{
		if(tris[i].ndId[0]<nNodes &&
		   tris[i].ndId[1]<nNodes &&
		   tris[i].ndId[2]<nNodes)
		{
			auto &tri=tris[i];
			glVertex2dv(nodes[tri.ndId[0]].v);
			glVertex2dv(nodes[tri.ndId[1]].v);
			glVertex2dv(nodes[tri.ndId[2]].v);
		}
	}
	glEnd();

	glColor3f(0,0,0);

	glBegin(GL_LINES);
	for(int i=0; i<nTris; ++i)
	{
		if(tris[i].ndId[0]<nNodes &&
		   tris[i].ndId[1]<nNodes &&
		   tris[i].ndId[2]<nNodes)
		{
			auto &tri=tris[i];
			glVertex2dv(nodes[tri.ndId[0]].v);
			glVertex2dv(nodes[tri.ndId[1]].v);

			glVertex2dv(nodes[tri.ndId[1]].v);
			glVertex2dv(nodes[tri.ndId[2]].v);

			glVertex2dv(nodes[tri.ndId[2]].v);
			glVertex2dv(nodes[tri.ndId[0]].v);
		}
	}
	glEnd();
}


int main(void)
{
	FsOpenWindow(0,0,800,600,1);
	FsChangeToProgramDir();

	Mesh mesh;
	mesh.Open("airfoil.txt");

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		mesh.Draw();
		FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
	}
}

#include <stdio.h>


class FilePtr
{
protected:
	FILE *fp=nullptr;
public:
	FilePtr()
	{
	}
	~FilePtr()
	{
		Close();
	}
	bool Open(char fn[],char mode[])
	{
		fp=fopen(fn,mode);
		if(nullptr!=fp)
		{
			return true;
		}
		return false;
	}
	void Close(void)
	{
		if(nullptr!=fp)
		{
			fclose(fp);
			printf("File closed.\n");
		}
		fp=nullptr;
	}
	FILE *GetFP(void)
	{
		return fp;
	}
};

int main(void)
{
	FilePtr fp;
	char str[256];

	fp.Open("auto_close.cpp","r");
	while(nullptr!=fgets(str,255,fp.GetFP()))
	{
		printf("%s",str);
	}

	return 0;
}

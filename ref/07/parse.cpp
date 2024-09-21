#include <stdio.h>


int ParseString(
	int wordPos[],
	int wordLen[],
	char input[],
	int wordLimit)
{
	int state=0;
	int nWords=0;
	for(int i=0; 0!=input[i]; ++i)
	{
		auto c=input[i];
		switch(state)
		{
		case 0:
			if(' '!=c && '\t'!=c && '\n'!=c)
			{
				wordPos[nWords]=i;
				wordLen[nWords]=1;
				++nWords;
				state=1;
			}
			break;
		case 1:
			if(' '==c || '\t'==c || '\n'==c)
			{
				if(nWords==wordLimit)
				{
					goto LOOP_OUT;
				}
				state=0;
			}
			else
			{
				++wordLen[nWords-1];
			}
			break;
		}
	}
LOOP_OUT:
	return nWords;
}


int main(void)
{
	char input[256];
	printf("Enter Text>");
	fgets(input,255,stdin);
	input[255]=0;

	int nWords;
	int wordPos[10],wordLen[10];
	nWords=ParseString(wordPos,wordLen,input,10);

	for(int i=0; i<nWords; ++i)
	{
		char ext[256];
		for(int j=0; j<wordLen[i]; ++j)
		{
			ext[j]=input[wordPos[i]+j];
		}
		ext[wordLen[i]]=0;
		printf("%s\n",ext);
	}
}

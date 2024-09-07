#include <iostream>
#include <stdlib.h>
#include <time.h>



int main(void)
{
	srand(time(nullptr));

	int r[20],nr=0;
	while(nr<20)
	{
		int x=rand()%20;

		bool found=false;
		for(int i=0; i<nr; ++i)
		{
			if(x==r[i])
			{
				found=true;
				break;
			}
		}

		if(found!=true)
		{
			r[nr]=x;
			++nr;
		}
	}

	for(auto x : r)
	{
		std::cout << x << "\n";
	}

	return 0;
}

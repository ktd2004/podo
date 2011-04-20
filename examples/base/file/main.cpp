#include "base/PDFile.h"
#include <string>


int main(int argc, char** argv)
{
	printf("file test program!!\n");
	if(argc != 2)
	{
		printf("usage : ./file 'path' \n");
		return -1;
	}

	long size = PD::File::size(argv[1]);

	printf("size :%ld\n", size);


	PD::File f(argv[1]);
	f.open( PD::File::ReadOnly);
	std::string xx;
	while(1)
	{
		if (!f.readLine(xx)) break;
		printf("main %s", xx.c_str());
	}

	return 0;
}

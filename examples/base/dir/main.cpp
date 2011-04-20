#include "base/PDDir.h"
#include <string.h>


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage : ./dir 'path' \n");
		return -1;
	}

	PD::Dir dir(argv[1]);

	// files
	PD::String::StringList list = dir.entryList();
	PD::String::StringList::iterator it = list.begin();
	while(it != list.end())
	{
		printf("list : %s\n", (*it).c_str());
		it++;
	}

	printf("============= dir size ===========\n");
	uintmax_t dirSize = 0;
	dirSize = dir.size(argv[1]);
	printf("dirSize = %jd byte\n", dirSize);

	return 0;
}

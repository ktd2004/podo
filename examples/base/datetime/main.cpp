#include <stdio.h>
#include <string>
#include "base/PDDateTime.h"

int main(int argc, char** argv)
{
	std::string cmd;
	std::string arg;

	if (argc > 1)
	{
		if (argc == 3)
		{
			cmd = argv[1];	
			arg = argv[2];
		}
		else
		{
			printf("usage) ./datetime -s YYYYMMDDhhmmss\n");
			return -1;
		}
	}

	if (cmd.empty())
	{
		PD::DateTime cur;
		cur.print();
	}
	else if (cmd == "-s") // set system time
	{
		if (arg.size() != 14)
		{
			printf("usage) ./datetime -s -g YYYYMMDDhhmmss\n");
			return -1;
		}
		PD::DateTime cur;
		if (!cur.fromString(arg.c_str()))
		{
			printf("failed to update '%s'\n", arg.c_str());
			return -1;
		}
		cur.setSystemTime();
		cur.print();

	}

	return 0;
}

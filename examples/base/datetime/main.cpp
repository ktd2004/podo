/* 
   Copyright 2011 PODO. 
   This file is part of PODO. 
   
   PODO is free software: you can redistribute it and/or modify 
   it under the terms of the GNU Lesser General Public License as  
   published by the Free Software Foundation, either version 3 of  
   the License, or (at your option) any later version. 
   
   PODO is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of 
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU Lesser General Public License for more details. 
   
   You should have received a copy of the GNU Lesser General Public  
   License along with PODO. If not, see <http://www.gnu.org/licenses/>. 
 */
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

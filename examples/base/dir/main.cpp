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

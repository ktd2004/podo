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

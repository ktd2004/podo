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
#include "base/PDFlagScoper.h"
#include <stdio.h>

int main(int /*argc*/, char** /*argv*/)
{
	bool condition=true;
	printf("condition is %d\n", condition);
	while(condition)
	{
		PD::FlagScoper flagscoper(&condition, false);
		break;
		condition=false;
	}
	printf("condition is %d\n", condition);
	return 0;
}



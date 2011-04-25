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
#include <base/PDIniFile.h>
#include <stdio.h>

int main(int /*argc*/, char** /*argv*/)
{
	PD::IniFile iniFile("./config.ini");

	iniFile.writeEntry("general", "name", "podo");
	iniFile.writeEntry("general", "age", "30");
	iniFile.writeEntry("general", "tel", "82-31-704-9390");
	iniFile.write();

	printf("%s\n", iniFile.readEntry("general", "name").c_str());
	printf("%s\n", iniFile.readEntry("general", "age").c_str());
	printf("%s\n", iniFile.readEntry("general", "tel").c_str());

	return 0;
}

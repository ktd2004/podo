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
#ifndef _PDINIFILE_P_H_
#define _PDINIFILE_P_H_

namespace PD {

class IniFilePrivate
{
public:
	bool isOpen;

	int lineNo;
    std::map<std::string, IniFile::Group*> groups;
    std::string filename;
	IniFile::Group* currentGroup;

public:
	IniFilePrivate()
	{
		lineNo = 1;
		currentGroup = NULL;
		isOpen = false;
	}

	IniFilePrivate(const std::string& fn)
	{
		filename = fn;
		currentGroup = NULL;
		isOpen = false;
	}

	int parse(const std::string &l)
	{
		std::string line = String::trim(l);

		if (line.empty())
		{
			//printf("IniFile::parse line is empty\n");
			return 0;
		}

		// check comment
		if (line[0] == '#')
		{
			//printf("IniFile::parse this is a comment\n");
			return 0;
		}
		
		// check group
		if (line[0] == '[' && line[line.length()-1] == ']')
		{
			std::string group = std::string(line, 1, line.length()-2); 	
			//printf("IniFile::parse this is a group:[%s]\n", group.c_str());

			IniFile::Group* grp = new IniFile::Group;
			groups[group] = grp;

			currentGroup = grp;

		}


		//String::StringList list = String::split(line, " ");
		// check key = value
		int n = line.find_first_of("=");
		if (n != -1)
		{
			std::string key = std::string(line, 0, n);
			key = String::trim(key);

			std::string val = std::string(line, n+1, line.length()-n);
			val = String::trim(val);
			if((int)(line.length()-1) == n) val = "";

			if (currentGroup == NULL)
			{
				//printf("IniFile::parse does not have a group "
				//	"key:[%s] value:[%s]\n",
				//	key.c_str(), value.c_str());
				return -1;
			}

			//printf("IniFile::parse key:[%s] value:[%s]\n",
			//	key.c_str(), value.c_str());

			(*currentGroup)[key] = val;
		}

		return 0;
	}


};
} // namespace PD {
#endif

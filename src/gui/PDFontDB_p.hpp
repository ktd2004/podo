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
#ifndef _PDFONTDB_P_H_
#define _PDFONTDB_P_H_

namespace PD {

class FontDBPrivate
{
public:
	FontDB::FontMap map;
	FontDB::CacheFontMapList cacheFontMapList;
	std::string cacheFontMapFile;

public:
	FontDBPrivate()
	{
	}

	~FontDBPrivate()
	{
	}

	Font* open(const char* name, size_t size)
	{
		Font* f = new Font(name, size);
		if (f == 0)
		{
			printf("FontDBPrivate::open failed to open '%s' size:%d\n", 
					name, size);
			return 0;
		}

		std::string key = String::format("%s_%d", name, size);
		map[key] = f;

		//printf("FontDBPrivate::open name:%s size:%d %X\n", name, size, f);
		return f;
	}


};

} //namespace PD {
#endif

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
#include "PDFontDB.h"
#include "PDApp.h"
#include "../base/PDFile.h"
#include "../base/PDString.h"
#include "PDFontDB_p.hpp"

namespace PD {

FontDB::FontDB()
{
	d = new FontDBPrivate;
}

FontDB::~FontDB()
{
	clearCacheFontMap();

	FontMapIt it = d->map.begin();
	while(it != d->map.end())
	{
		std::string name = (*it).first;
		Font* f = (*it).second;

		delete f;

		it++;
	}

	delete d;
}

FontDB::CacheFontMapList& FontDB::cacheFontMapList() 
{ 
	return d->cacheFontMapList; 
}

void FontDB::clearCacheFontMap()
{
	int count = d->cacheFontMapList.size();
	for (int i=0; i<count; i++)
	{
		CacheFontMap* map = d->cacheFontMapList[i];
		if (map == 0) continue;
		delete map;
	}
}

bool FontDB::loadCacheFontMap(const char* fn)
{
	d->cacheFontMapFile = fn;

	PD::File f;
	if (f.open(fn, File::ReadOnly) == -1) 
	{
		printf("FontDB::loadCacheFontMap failed to open '%s'\n", fn);
		return false;
	}

	int count = 0;	
	if (f.read((unsigned char*)&count, sizeof(count)) != 
		sizeof(count)) 
	{
		printf("FontDB::loadCacheFontMap failed to read count:%d\n", count);
		return false;
	}

	clearCacheFontMap();

	for (int i=0; i<count; i++)
	{
		CacheFontMap* data = new CacheFontMap;
		data->map = (Uint8*)malloc(256);

		if (f.read((unsigned char*)&data->penColor.r, 
			sizeof(data->penColor)) != sizeof(data->penColor)) 
		{
			printf("FontDB::loadCacheFontMap failed to read...1\n");
			return false;
		}
		if (f.read((unsigned char*)&data->brushColor.r, 
			sizeof(data->penColor)) != sizeof(data->penColor)) 
		{
			printf("FontDB::loadCacheFontMap failed to read...2\n");
			return false;
		}
		if (f.read((unsigned char*)data->map, 256) != 256) 
		{
			printf("FontDB::loadCacheFontMap failed to read...3\n");
			return false;
		}

		d->cacheFontMapList.push_back(data);
	}

	printf("FontDB::loadCacheFontMap fn:%s count:%d\n", fn, count);

	return true;
};

bool FontDB::saveCacheFontMap(const char* fn)
{
	unlink(fn);
	PD::File f;
	if (f.open(fn, File::WriteOnly | File::Create) == -1) return false;

	int count = d->cacheFontMapList.size();
	if (f.write((unsigned char*)&count, sizeof(count)) != 
		sizeof(count)) return false;

	for (int i=0; i<count; i++)
	{
		CacheFontMap* map = d->cacheFontMapList[i];
		if (map == 0) continue;

		if (f.write((unsigned char*)&map->penColor.r, sizeof(map->penColor)) != 
			sizeof(map->penColor)) return false;
		if (f.write((unsigned char*)&map->brushColor.r, sizeof(map->brushColor)) != 
			sizeof(map->brushColor)) return false;
		if (f.write((unsigned char*)map->map, 256) != 256) return false;
	}

	//printf("FontDB::saveCacheFontMap fn:%s count:%d\n", fn, count);

	return true;
};


FontDB::CacheFontMap* FontDB::findCacheFontMap(Color penColor, Color brushColor)
{
	int count = d->cacheFontMapList.size();
	for (int i=0; i<count; i++)
	{
		CacheFontMap* map = d->cacheFontMapList[i];
		if (map == 0) continue;

		if (map->penColor == penColor &&
			map->brushColor == brushColor)
		{
			return map;
		}
	}

	return 0;
}

bool FontDB::addCacheFontMap(CacheFontMap* data)
{
	if (data == 0) return false;

	d->cacheFontMapList.push_back(data);

	printf("FontDB::addCacheFontMap count:%d\n", d->cacheFontMapList.size());
	printf("\n\n\n\n");

	//if (!d->cacheFontMapFile.empty())
	//	saveCacheFontMap(d->cacheFontMapFile.c_str());

	return true;
}

Font* FontDB::font(const char* name, size_t size)
{
	std::string query = String::format("%s_%d", name, size);
	
	Font* f = d->map[query];
	if (f == 0) f = d->open(name, size);

	return f;
}

} //namespace PD {

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
#ifndef _PDFONTDB_H_
#define _PDFONTDB_H_

#include "PDFont.h"
#include <map>
#include <string>
#include <vector>

#ifdef WIN32
#undef RGB
#endif

namespace PD {

class FontDBPrivate;

/**
 * \brief font database
 * \ingroup gui
 */
class FontDB
{
public:
	typedef std::map<std::string, Font*> FontMap;
	typedef std::map<std::string, Font*>::iterator FontMapIt;

	class CacheFontMap
	{
	public:
		Color penColor;
		Color brushColor;
		Uint8* map;

		CacheFontMap()
		{
			penColor = Color(0, 0, 0);
			brushColor = Color(0, 0, 0);
			map = 0;
		}
		~CacheFontMap()
		{
			if (map) 
			{
				SDL_free((void*)map);
				map = 0;
			}
		}
	};
	typedef std::vector<CacheFontMap*> CacheFontMapList;


private:
	FontDBPrivate* d;

public:
	FontDB();
	~FontDB();

	CacheFontMapList& cacheFontMapList();
	CacheFontMap* findCacheFontMap(Color penColor, Color brushColor);
	void clearCacheFontMap();
	bool addCacheFontMap(CacheFontMap* data);
	bool loadCacheFontMap(const char* fn);
	bool saveCacheFontMap(const char* fn);

	Font* font(const char* name, size_t size);
};


} //namespace PD {

#endif

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
#ifndef _PDFONT_H_
#define _PDFONT_H_

#include "PDColor.h"
#include "3rdparty/SDL_ttf/SDL_ttf.h"
#include <string>
#include <base/PDMutex.h>

#ifdef WIN32
#pragma warning(disable:4312) 
#endif

namespace PD {

class FontPrivate;

/**
 * \brief font
 * \ingroup gui
 */
class Font
{
private:
	FontPrivate* d;

public:
	Font();
	Font(const char* fn, int size);
	virtual ~Font();

	const char* name();
	void setName(const char* fn);

	int size();

	TTF_Font* font();

	void textSize(const char* text, int& w, int& h);
	SDL_Surface* renderText(const char* text, Color fg, Color bg);
};

} //namespace PD {

#endif

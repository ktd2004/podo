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
#include "PDFont.h"
#include "PDApp.h"
#include <string>
#include <assert.h>
#include <base/PDMutexLocker.h>
#include "PDFont_p.hpp"

namespace PD {

Font::Font()
{
	d = new FontPrivate;
}

Font::Font(const char* fn, int size)
{
	d = new FontPrivate(fn, size);
	setName(fn);
}

Font::~Font()
{
	delete d;
}

const char* Font::name()
{
	return d->name.c_str();
}	

int Font::size()
{
	return d->size;
}

TTF_Font* Font::font() { return d->font; }

void Font::setName(const char* fn)
{
	d->name = fn;
}

void Font::textSize(const char* text, int& w, int& h)
{
	PD::MutexLocker ml(&d->mutex);
	w = 0;
	h = 0;

	if (!d->isOpen())
	{
		if (d->open() == -1) return;
	}

	w = h = 0;
	if (text == NULL) return;
	if (strlen(text) == 0) return;

	TTF_SizeUTF8(d->font, text, &w, &h);
}

SDL_Surface* Font::renderText(const char* text, Color fg, Color bg)
{
	PD::MutexLocker ml(&d->mutex);
	if (text == NULL) return NULL;
	if (strlen(text) == 0) return NULL;
	if (!d->isOpen())
	{
		if (d->open() == -1) return NULL;
	}

	SDL_Color fgCol = {255, 255, 255, 0};
	fgCol.r = fg.r;
	fgCol.g = fg.g;
	fgCol.b = fg.b;

	SDL_Color bgCol = {0, 0, 0, 0};
	bgCol.r = bg.r;
	bgCol.g = bg.g;
	bgCol.b = bg.b;

	//printf("Font::renderText text:[%s] fg(0x%02X, 0x%02X, 0x%02X)"
	//	" bg(0x%02X, 0x%02X, 0x%02X)\n",
	//	text, fg.r, fg.g, fg.b, bg.r, bg.g, bg.b);

	SDL_Surface* surface = NULL;	
	surface = TTF_RenderUTF8_Blended(d->font, text, fgCol);//, bgCol);
	if (surface == NULL)
	{
		//printf("Font::renderText text:[%s] error:%s\n", text, SDL_GetError());
		return NULL;
	}

	//printf("Font::renderText text:[%s] w:%d h:%d\n",
	//	text, surface->w, surface->h);

	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format,
											bgCol.r, bgCol.g, bgCol.b));
	return surface;
}

} //namespace PD {

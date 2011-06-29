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
#ifndef _PDIMAGE_H_
#define _PDIMAGE_H_

#include <SDL.h>
#include "PDRect.h"

namespace PD {

class ImagePrivate;

/**
 * \brief image
 * \ingroup gui
 */
class Image 
{
public:
	enum ImageFormat
	{
		Bmp = 0,
		Png,
		Jpg,
		Xpm
	};

private:
	ImagePrivate* d;

public:
	Image(const char* filename=0);
	~Image();

	bool load(const char* filename, ImageFormat f=Bmp);
	const char* filename();

	bool loadXpm(const char** xpm);

	SDL_Surface* surface() const;

	int width() const;
	int height() const;

	PD::Rect rect();
};

} //namespace PD {

#endif

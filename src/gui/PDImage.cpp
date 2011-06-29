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
#include "PDImage.h"
#include "PDImage_p.hpp"
#include "3rdparty/SDL_image/SDL_image.h"

namespace PD {

Image::Image(const char* filename/*=0*/)
{
	d = new ImagePrivate;
	if (filename != 0) 
	{
		load(filename);
		d->fileName = filename;
	}
}
Image::~Image()
{
	delete d;
}

const char* Image::filename() { return d->fileName; };

bool Image::load(const char* filename, ImageFormat /*f=Bmp*/)
{
	d->surface = IMG_Load(filename);
	if (d->surface == 0)
	{
		//printf("Image::load failed to load '%s'\n", filename);
		//printf("Image::load IMG_GetError: %s\n", IMG_GetError() );
		return false;
	}
	d->fileName = filename;

	return true;
}

bool Image::loadXpm(const char** xpm)
{
	d->surface = IMG_ReadXPMFromArray((char**)xpm);
	if(!d->surface)
	{
		printf("Image::loadXpm load failed\n");
		return false;
	}

	return true;
}


int Image::width() const
{
	if(!d->surface) return 0;
	return d->surface->w;
}

int Image::height() const
{
	if(!d->surface) return 0;
	return d->surface->h;
}


Rect Image::rect()
{
	Rect r;
	if(!d->surface) return r;
	
	r.setWidth(d->surface->w);
	r.setHeight(d->surface->h);

	return r;
}

SDL_Surface* Image::surface() const
{
	return d->surface;
}

} // PD


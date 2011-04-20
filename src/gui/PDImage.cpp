#include "PDImage.h"
#include "PDImage_p.hpp"

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


#ifndef _PDIMAGE_H_
#define _PDIMAGE_H_

#include <SDL.h>
#include <SDL_image.h>
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

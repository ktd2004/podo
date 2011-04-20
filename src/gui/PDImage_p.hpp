#ifndef _PDIMAGE_P_H_
#define _PDIMAGE_P_H_

namespace PD {

class ImagePrivate
{
public:
	SDL_Surface* surface;
	const char*	fileName;

public:
	ImagePrivate()
	{
		fileName = NULL;
		surface = NULL;		
	}

	~ImagePrivate()
	{
		if (surface) { SDL_FreeSurface(surface); surface = NULL; }
	}
};
} // namespace PD {
#endif

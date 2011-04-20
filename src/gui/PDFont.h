#ifndef _PDFONT_H_
#define _PDFONT_H_

#include "PDColor.h"
#include "SDL_ttf.h"
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

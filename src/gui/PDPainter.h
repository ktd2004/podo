#ifndef _PDPAINTER_H_
#define _PDPAINTER_H_

#include "PDWidget.h"
#include "PDImage.h"
#include "PDFontDB.h"

namespace PD {

class PainterPrivate;

/**
 * \brief
 * \ingroup gui
 */
class Painter
{
private:
	PainterPrivate* d;

public:
	Painter(Widget* widget);
	~Painter();

	Widget* parent();

	void setPenColor(const Color& color);
	void setBrushColor(const Color& color);

	void save();
	void restore();

	void drawHLine(int x, int y, int x2, int y2);
	void drawVLine(int x, int y, int x2, int y2);

	void drawHLine(int x, int y, int x2, int y2, int color);
	void drawVLine(int x, int y, int x2, int y2, int color);

	void drawRect(const Rect& rect);
	void drawRect(int x, int y, int x2, int y2);

	void drawPixel(int x, int y);

	void fillRect(int x, int y, int w, int h, const Color& color);
	void fillRect(int x, int y, int w, int h, int color);
	void fillRect(int x, int y, int w, int h);
	void fillRect(const Rect& rect);
	void fillRect(const Rect& rect, int color);
	void fillRect(const Rect& rect, const Color& color);

	void drawText(int x, int y, const char* text, bool resizeToFit=false);
	void drawText(const Rect& rect, const char* text, 
		int align=AlignCenter, bool resizeToFit=false);

	void drawImage(int x, int y, const Image& image);
	void drawImage(const Rect& rect, const Image& image);
	void drawImage(int x, int y, int w, int h, const Image& image);

	static bool blitSurface(Widget* widget, SDL_Surface* src, SDL_Rect* srcRect,
		SDL_Surface* dst, SDL_Rect* dstRect);
};

} //namespace PD {

#endif

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
#include "PDPainter.h"
#include "PDApp.h"
#include <assert.h>
#include <iostream>
#include "../base/PDString.h"
#include "PDPainter_p.hpp"

#ifdef WIN32
#undef min
#undef max
#endif

namespace PD {

Painter::Painter(Widget* widget)
{
	assert (widget != NULL);
	d = new PainterPrivate(widget);
}

Painter::~Painter()
{
	delete d;
}

Widget* Painter::parent() { return d->widget; }

void Painter::save()
{
	d->savedPenColor = d->penColor;
	d->savedBrushColor = d->brushColor;
}

void Painter::restore()
{
	d->penColor = d->savedPenColor;
	d->brushColor = d->savedBrushColor;
}

void Painter::setPenColor(const Color& color)
{
	d->penColor = color;
}

void Painter::setBrushColor(const Color& color)
{
	d->brushColor = color;
}


void Painter::drawPixel(int /*x*/, int /*y*/)
{
	// TODO: ...
}

void Painter::drawHLine(int x, int y, int x2, int /*y2*/)
{
	SDL_Surface* surface = d->widget->surface();
	Uint32 c = SDL_MapRGB(surface->format, d->penColor.r, d->penColor.g, d->penColor.b);

	SDL_Rect rect;
	rect.x = std::min(x, x2);
	rect.y = y;
	rect.w = std::max(x2 - x + 1, x - x2 + 1);
	rect.h = 1;

	SDL_FillRect(surface, &rect, c);
	//printf("Painter::drawHLine x:%d y:%d w:%d h:%d\n", rect.x, rect.y, rect.w, rect.h);
}

void Painter::drawVLine(int x, int y, int /*x2*/, int y2)
{
	SDL_Surface* surface = d->widget->surface();
	Uint32 c = SDL_MapRGB(surface->format, d->penColor.r, d->penColor.g, d->penColor.b);

	SDL_Rect rect;
	rect.x = x;
	rect.y = std::min(y, y2);
	rect.w = 1;
	rect.h = std::max(y2 - y + 1, y - y2 + 1);

	SDL_FillRect(surface, &rect, c);
	//printf("Painter::drawVLine x:%d y:%d w:%d h:%d\n", rect.x, rect.y, rect.w, rect.h);

}

void Painter::drawHLine(int x, int y, int x2, int /*y2*/, int color)
{
	SDL_Surface* surface = d->widget->surface();

	SDL_Rect rect;
	rect.x = std::min(x, x2);
	rect.y = y;
	rect.w = std::max(x2 - x + 1, x - x2 + 1);
	rect.h = 1;

	SDL_FillRect(surface, &rect, color);
	//printf("Painter::drawHLine x:%d y:%d w:%d h:%d\n", rect.x, rect.y, rect.w, rect.h);
}

void Painter::drawVLine(int x, int y, int /*x2*/, int y2, int color)
{
	SDL_Surface* surface = d->widget->surface();

	SDL_Rect rect;
	rect.x = x;
	rect.y = std::min(y, y2);
	rect.w = 1;
	rect.h = std::max(y2 - y + 1, y - y2 + 1);

	SDL_FillRect(surface, &rect, color);
	//printf("Painter::drawVLine x:%d y:%d w:%d h:%d\n", rect.x, rect.y, rect.w, rect.h);

}


void Painter::drawRect(const Rect& rect)
{
	drawRect(rect.x(), rect.y(), rect.right(), rect.bottom());
}

void Painter::drawRect(int x, int y, int x2, int y2)
{
	//printf("Painter::drawRect x:%d y:%d x2:%d y2:%d\n", x, y, x2, y2);
	drawHLine(x, y, x2, y); 		// -------
	drawVLine(x, y, x, y2); 		// +
	drawVLine(x2, y, x2, y2);		//       +
	drawHLine(x, y2, x2, y2); 		// -------
}

void Painter::fillRect(int x, int y, int w, int h, const Color& color)
{
	SDL_Surface* surface = d->widget->surface();
	if (surface == 0) return;

	Uint32 c = SDL_MapRGBA(surface->format, 
			color.r, color.g, color.b, color.a);
	//printf("Painter::fillRect r:%d g:%d b:%d --> %d\n",
	//	color.r, color.g, color.b, c);
	fillRect(x, y, w, h, c);
}

void Painter::fillRect(int x, int y, int w, int h, int color)
{
	SDL_Surface* surface = d->widget->surface();
	if (surface == 0) return;

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	//printf("Painter::fillRect x:%d y:%d w:%d h:%d color:%d\n", 
	//	rect.x, rect.y, rect.w, rect.h, color);
	SDL_FillRect(surface, &rect, color);
}

void Painter::fillRect(int x, int y, int w, int h)
{
	SDL_Surface* surface = d->widget->surface();
	if (surface == 0) return;

	Uint32 c = SDL_MapRGBA(surface->format, 
			d->brushColor.r, d->brushColor.g, d->brushColor.b, d->brushColor.a);
	fillRect(x, y, w, h, c);
}

void Painter::fillRect(const Rect& rect)
{
	fillRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void Painter::fillRect(const Rect& rect, int color)
{
	fillRect(rect.x(), rect.y(), rect.width(), rect.height(), color);
}

void Painter::fillRect(const Rect& rect, const Color& color)
{
	fillRect(rect.x(), rect.y(), rect.width(), rect.height(), color);
}

void Painter::drawText(int x, int y, const char* text, bool 
	resizeToFit/*=false*/)
{
	if (text == NULL) return;
	if (strlen(text) == 0) return;

	Color brushColor = d->brushColor;
	SDL_Surface* textSurface = 
		d->widget->font()->renderText(text, d->penColor, brushColor);
	if (textSurface == NULL)
	{
		printf("Painter::drawText Failed to renderText text:[%s]\n", text);
		return;
	}

	int w, h;
	w = h = 0;
	d->widget->font()->textSize(text, w, h);
	h = d->widget->font()->size();
	h += 3;
	
	SDL_Rect srcRect;
	if (resizeToFit)
	{
		int diffH = h - d->widget->font()->size();

		srcRect.x = 0;
		srcRect.w = w;
		if (diffH) 
		{
			srcRect.y = diffH/2;
			srcRect.h = h-diffH;
		}
		else 
		{
			srcRect.y = 0;
			srcRect.h = h;
		}
	}
	else
	{
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = w;
		srcRect.h = h;
	}

	SDL_Rect sdlRect;
	sdlRect.x = x;
	sdlRect.y = y;
	sdlRect.w = srcRect.w;
	sdlRect.h = srcRect.h;

	if (sdlRect.w > d->widget->width()-x) 
	{
		sdlRect.w = d->widget->width()-x;
		srcRect.w = d->widget->width()-x;
	}
	if (sdlRect.h > d->widget->height()-y) 
	{
		sdlRect.h = d->widget->height()-y;
		srcRect.h = d->widget->height()-y;
	}

	if (d->widget && d->widget->surface() && 
		d->widget->surface()->pixels && textSurface->pixels)

	{
		Painter::blitSurface(d->widget, textSurface, &srcRect, 
			d->widget->surface(), &sdlRect);
	}
	
	SDL_FreeSurface(textSurface);
}


void Painter::drawText(const Rect& rect, const char* text, 
	int align/*=AlignCenter*/, bool resizeToFit/*=false*/)
{
	if (text == NULL) return;
	if (strlen(text) == 0) return;

	SDL_Surface* textSurface = NULL;

	Color brushColor = d->brushColor;
	textSurface = d->widget->font()->renderText(text, 
			d->penColor, brushColor);
	if (textSurface == NULL)
	{
		printf("Painter::drawText Failed to renderText text:[%s]\n", text);
		return;
	}

	int w, h;
	w = h = 0;
	d->widget->font()->textSize(text, w, h);

	Rect newRect = rect;
	int dh = rect.height() - h;	
	int dw = rect.width() - w;

	if (align & AlignHCenter)
	{
		if (dw > 0) newRect.setX( newRect.x() + dw/2 );
	}
	if (align & AlignVCenter)
	{
		if (dh > 0) newRect.setY( newRect.y() + (dh/2));
	}
	if (align & AlignRight)
	{
		if (dw > 0) newRect.setX( newRect.x() + dw );	
	}
	if (align & AlignBottom)
	{
		if (dh > 0) newRect.setY ( newRect.y() + dh );
	}

	if (align & AlignLeft) 
	{
		if (newRect.x() == 0) newRect.setX(2);
	}
	if (align & AlignTop) 
	{
		if (newRect.y() == 0) newRect.setY(2);
	}
	
	SDL_Rect srcRect;
	if (resizeToFit)
	{
		int diffH = h - d->widget->font()->size();

		srcRect.x = 0;
		srcRect.w = w;
		if (diffH) 
		{
			srcRect.y = diffH/2;
			srcRect.h = h-diffH;
		}
		else 
		{
			srcRect.y = 0;
			srcRect.h = h;
		}
	}
	else
	{
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = w;
		srcRect.h = h;
	}

	SDL_Rect sdlRect;
	sdlRect.x = newRect.x();
	sdlRect.y = newRect.y();
	sdlRect.w = srcRect.w;
	sdlRect.h = srcRect.h;

	if (sdlRect.w > rect.width()) 
	{
		sdlRect.w = rect.width();
		srcRect.w = rect.width();
	}
	if (sdlRect.h >rect.height()) 
	{
		sdlRect.h = rect.height();
		srcRect.h = rect.height();
	}

	if (d->widget && d->widget->surface() && 
			d->widget->surface()->pixels && textSurface->pixels)
	{
		Painter::blitSurface(d->widget, textSurface, &srcRect, 
				d->widget->surface(), &sdlRect);
	}
	SDL_FreeSurface(textSurface);
}

void Painter::drawImage(int x, int y, const Image& image)
{
	drawImage(x, y, image.width(), image.height(), image);
}

void Painter::drawImage(const Rect& rect, const Image& image)
{
	SDL_Surface* imgSur = image.surface();
	if (imgSur == 0) return;
		
	SDL_Rect sdlRect;
	sdlRect.x = rect.x();
	sdlRect.y = rect.y();
	sdlRect.w = rect.width();
	sdlRect.h = rect.height();

	Painter::blitSurface(d->widget, imgSur, NULL, d->widget->surface(), &sdlRect);
}

void Painter::drawImage(int x, int y, int w, int h, const Image& image)
{
	Rect rect;
	rect.setX(x);
	rect.setY(y);
	rect.setWidth(w);
	rect.setHeight(h);
	drawImage(rect, image);
}

bool Painter::blitSurface(Widget* widget, SDL_Surface* src, SDL_Rect* srcRect,
	SDL_Surface* dst, SDL_Rect* dstRect)
{
	if (src == 0 || dst == 0) 
	{
		printf("Painter::blitSurface name:%s surface is NULL\n",
			widget->name());
		return false;
	}

	int retryCnt = 3;
	while(retryCnt)
	{
		int n = SDL_BlitSurface(src, srcRect, dst, dstRect);
		if (n < 0)
		{
			printf("Painter::blitSurface name:%s "
				"failed to SDL_BlitSurface retryCnt:%d n:%d %s\n",
					widget->name(), retryCnt, n, SDL_GetError());
#ifndef WIN32
			usleep(1000);
#endif
			retryCnt--;
			continue;
		}

		break;
	}

	return true;
}


} //namespace PD {


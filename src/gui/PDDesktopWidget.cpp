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
#include "PDDesktopWidget.h"
#include "PDDesktopWidget_p.hpp"
#include "PDApp.h"
#include "PDPainter.h"
#include <assert.h>
#include <algorithm>

namespace PD {

DesktopWidget::DesktopWidget()
{
	d = new DesktopWidgetPrivate;
}

DesktopWidget::~DesktopWidget()
{
	delete d;
}

SDL_Surface* DesktopWidget::surface()
{
	return d->surface;
}

int DesktopWidget::width() { return d->width; }
int DesktopWidget::height() { return d->height; }

Uint32 DesktopWidget::rMask() { return d->rMask; }
Uint32 DesktopWidget::gMask() { return d->gMask; }
Uint32 DesktopWidget::bMask() { return d->bMask; }
Uint32 DesktopWidget::aMask() { return d->aMask; }
Uint8 DesktopWidget::bpp() { return d->bpp; }

DesktopWidget::WidgetList&	DesktopWidget::childList() { return d->childList; }

void DesktopWidget::setBackground(int color)
{
	if (d->surface == 0) return;

	SDL_GetRGBA(color, 
		d->surface->format,
		&d->brushColor.r, &d->brushColor.g,
		&d->brushColor.b, &d->brushColor.a);
}


void DesktopWidget::setBackground(const Color& rgb)
{
	Uint32 c = SDL_MapRGBA(d->surface->format,
			rgb.r, rgb.g, rgb.b, rgb.a);
	setBackground(c);
}

int DesktopWidget::create(int w, int h, int bpp)
{
	const SDL_VideoInfo* vinfo = SDL_GetVideoInfo();
	assert(vinfo != 0);

	if (w == 0) 
	{
		w = theApp->screenWidth();
		if (w == 0) w = vinfo->current_w;
	}
	if (h == 0) 
	{
		h = theApp->screenHeight();
		if (h == 0) h = vinfo->current_h;
	}
	if (bpp == 0) 
	{
		bpp = theApp->screenBpp();
		if (bpp == 0) bpp = vinfo->vfmt->BitsPerPixel;
	}

	d->rMask = vinfo->vfmt->Rmask;
	d->gMask = vinfo->vfmt->Gmask;
	d->bMask = vinfo->vfmt->Bmask;
	d->aMask = vinfo->vfmt->Amask;

	int flags = SDL_SWSURFACE;
	if (theApp->isFullScreen()) 
	{
		flags |= SDL_NOFRAME;
	}
	//printf("DesktopWidget::create %dx%dx%d\n", w, h, bpp);
	d->surface = SDL_SetVideoMode(w, h, bpp, flags);
	if (d->surface == 0)
	{
		printf("DesktopWidget::create Failed to create surface(%s)\n",
				SDL_GetError());
		exit(-1);
	}

	d->width = vinfo->current_w;
	d->height = vinfo->current_h;
	d->bpp = vinfo->vfmt->BitsPerPixel;

	//printf("DesktopWidget::create w:%d h:%d bpp:%d\n",
	//	d->width, d->height, d->bpp);

	return 0;
}

bool DesktopWidget::screenShot(const std::string& fn)
{
	if (fn.empty()) return false;
	if (d->surface == 0) return false;

	if (SDL_SaveBMP(d->surface, fn.c_str()) == -1)
	{
		//printf("DesktopWidget::screenShot failed to save '%s'\n", fn.c_str());
		return false;
	}

	//printf("DesktopWidget:screenShot save fn:%s\n", fn.c_str());
	return true;
}

void DesktopWidget::paintBg(Rect& r)
{
	SDL_Rect srcRect;
	srcRect.x = r.x();
	srcRect.y = r.y();
	srcRect.w = r.width();
	srcRect.h = r.height();

	//printf("DesktopWidget::paintBg x:%d y:%d w:%d h:%d\n",
	//	srcRect.x, srcRect.y, srcRect.w, srcRect.h);
	SDL_FillRect(d->surface, &srcRect, d->brushColor);
}

void DesktopWidget::paintBg()
{
	Rect r(0, 0, width(), height());
	paintBg(r);
}

void DesktopWidget::paintChild(Rect& r)
{
	if (r.width() == 0 && r.height() == 0) return;
	//printf("DesktopWidget::paintChild input x:%d y:%d w:%d h:%d\n", 
	//	r.x(), r.y(), r.width(), r.height());

	WidgetListIt it = d->childList.begin();
	while (it != d->childList.end())
	{
		Widget* widget = *it;

		if (widget && widget->isVisible())
		{
			//printf("DesktopWidget::paintChild child paint name:%s\n", 
			//  widget->name()?widget->name():"NULL");
			//printf("widget x:%d y:%d w:%d h:%d\n", 
			//  widget->x(), widget->y(), 
			//  widget->width(), widget->height());
			if (widget->geometry().intersect(r))
			{
				//printf("DesktopWidget::paintChild paint name:%s\n",
				//	widget->name());

				int w = r.width() > widget->width() ? widget->width() : r.width();
				int h = r.height() > widget->height() ? widget->height() : r.height();

				SDL_Rect srcRect;
				srcRect.x = r.x() - widget->x();
				if (srcRect.x < 0)
				{
					srcRect.x = 0;
				}
				srcRect.y = r.y() - widget->y();
				if (srcRect.y < 0)
				{
					srcRect.y = 0;
				}
				srcRect.w = w;
				srcRect.h = h;


				Rect repaintRect(srcRect.x, srcRect.y, srcRect.w, srcRect.h);
				widget->paint(repaintRect);

				SDL_Rect dstRect;
				dstRect.x = r.x();
				dstRect.y = r.y();
				dstRect.w = w;
				dstRect.h = h;

				//printf("DesktopWidget::paintChild src(x:%d y:%d w:%d h:%d)\n",
				//		srcRect.x, srcRect.y, srcRect.w, srcRect.h);
				//printf("DesktopWidget::paintChild dst(x:%d y:%d w:%d h:%d)\n",
				//		dstRect.x, dstRect.y, dstRect.w, dstRect.h);

				Painter::blitSurface(widget, widget->surface(), &srcRect,
					d->surface, &dstRect);
			}
		}
		it++;
	}

	SDL_UpdateRect(d->surface, r.x(), r.y(), r.width(), r.height());
	//printf("DesktopWidget::paintChild update x:%d y:%d w:%d h:%d\n\n\n\n",
	//	r.x(), r.y(), r.width(), r.height());
}

void DesktopWidget::paintChild()
{
    Rect r(0, 0, width(), height());
    paintChild(r);
}

void DesktopWidget::paint(Rect& r)
{
	//printf("DesktopWidget::paint x:%d y:%d w:%d h:%d\n",
	//	r.x(), r.y(), r.width(), r.height());
    paintBg(r);
    paintChild(r);
}

void DesktopWidget::paint()
{
    Rect r(0, 0, width(), height());
    paint(r);
}

Widget* DesktopWidget::findMouseWidget(const Point& pt)
{
	Widget* findW = 0;

	WidgetListReverseIt it = d->childList.rbegin();
	while (it != d->childList.rend())
	{
		Widget* widget = *it;
		//printf("DeskopWidget::findMouseWidget checking name:%s\n", widget->name());
		if (widget && widget->isVisible() &&
			widget->geometry().contains(pt))
		{
			findW = widget->findMouseWidget(pt);
			//printf("DeskopWidget::findMouseWidget found name:%s\n", findW->name());
			break;
		}

		it++;
	}

	return findW;

}

Widget* DesktopWidget::findChild(Widget* w)
{
	Widget* findW = 0;
	if (w == 0) return findW;

	WidgetListIt it = d->childList.begin();
	while (it != d->childList.end())
	{
		Widget* widget = *it;
		if (widget && w == widget)
		{
			findW = widget;
			break;
		}

		it++;
	}

	return findW;
}

void DesktopWidget::addChild(Widget* w)
{
    assert(w != NULL);

	if (d->surface == 0) create(0, 0, 0);

    d->childList.push_back(w);

	if(!theApp->mainWidget())
	{
		theApp->setMainWidget(w);
	}
    //printf("DesktopWidget::addChild name:%s\n", w->name());
}

Widget* DesktopWidget::nextMainWidget(Widget* w)
{
	if (w == 0) return 0;
	if (d->childList.size() <= 1) return 0;

	//printf("DesktoWidget::nextMainWidget w->name():%s\n", w->name());

	Widget* next = 0;

	WidgetListIt it = std::find(d->childList.begin(), d->childList.end(), w);
	if (it == d->childList.end()) 
	{
		//printf("DesktopWidget::nextMainWidget failed to find name:%s\n",
		//	w->name());
		theApp->setMainWidget(next);
		return next;
	}

	while(1)
	{
		it--;	
		next = *it;
		if (next == 0) break;
		if (next->isVisible()) break;

		if (it == d->childList.begin()) break;
	}

	theApp->setMainWidget(next);

	//printf("DesktopWidget::nextMainWidget next:%s\n", next->name());

	return next;
}

void DesktopWidget::removeChild(Widget* w)
{
    assert (w != NULL);

    d->childList.remove(w);
    //printf("DesktopWidget::removeChild name:%s\n", w->name());
}

} //namespace PD 

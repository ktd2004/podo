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
#include "PDWidget.h"
#include <SDL_quit.h>
#include "PDApp.h"
#include "PDPainter.h"
#include <assert.h>
#include <algorithm>
#include <stack>
#include "PDWidget_p.hpp"

namespace PD {

WidgetKeyMover::WidgetKeyMover()
{
	m_up = NULL; 
	m_down = NULL; 
	m_left = NULL; 
	m_right = NULL;
}

WidgetKeyMover::WidgetKeyMover(Widget* up, Widget* down, 
	Widget* left, Widget* right)
{
	m_up = up;
	m_down = down;
	m_left = left;
	m_right = right;
}

void WidgetKeyMover::setUp(Widget* up) { m_up = up; }
Widget* WidgetKeyMover::up() const { return m_up; }

void WidgetKeyMover::setDown(Widget* down) { m_down = down; }
Widget* WidgetKeyMover::down() const { return m_down; }

void WidgetKeyMover::setLeft(Widget* left) { m_left = left; }
Widget* WidgetKeyMover::left() const { return m_left; }

void WidgetKeyMover::setRight(Widget* right) { m_right = right; }
Widget* WidgetKeyMover::right() const { return m_right; }

WidgetKeyMover& WidgetKeyMover::operator=(const WidgetKeyMover& ctrl)
{
	m_up = ctrl.up();
	m_down = ctrl.down();
	m_left = ctrl.left();
	m_right = ctrl.right();

	return *this;
}

Widget::Widget(Widget* parent/*=0*/, const char* name/*=0*/, Uint32 style/*=0*/,
	Theme::Control themeControl/*=Theme::Widget*/)
{
	d = new WidgetPrivate(parent, name, style);

	if (parent)
	{
		setFont(parent->font()->name(), parent->font()->size());
	}
	else
	{
		setFont(PD::theApp->fontName().c_str(), 
				PD::theApp->fontSize());
	}

	if (parent) parent->addChild(this);
	else 
		theApp->desktopWidget()->addChild(this);

	Theme* theme = theApp->theme();
	if (theme)
	{
		Palette* p = theme->palette(themeControl);
		if (p) setPalette(*p);
	}
}

Widget::~Widget()
{
	//printf("Widget::~Widget name:%s...start\n", name());
	if (parent()) parent()->removeChild(this);
	else theApp->desktopWidget()->removeChild(this);

	if (d) { delete d; }
	//printf("Widget::~Widget name:%s...end\n", name());
}

int Widget::result() { return d->result; }

bool Widget::isClosed() 
{ 
	if (d == 0) return true;
	if (d->closed) return true;

	Widget* p = parent();
	while(p)
	{
		if (p->isClosed()) return true;
		p = p->parent();
	}

	return false;
}

bool Widget::isClosing() 
{ 
	if (d == 0) return true;
	if (d->closing) return true;

	Widget* p = parent();
	while(p)
	{
		if (p->isClosing()) return true;
		p = p->parent();
	}

	return false;
}

void Widget::setPopup(bool f) { d->popup = f; }
bool Widget::isPopup() { return d->popup; }

void Widget::setModal(bool f) { d->modal = f; }
bool Widget::isModal() { return d->modal; }

FocusPolicy	Widget::focusPolicy() { return d->focusPolicy; }
void Widget::setFocusPolicy(FocusPolicy f) { d->focusPolicy = f; }

void Widget::setResult(int r) { d->result = r; }


void Widget::setBgMode(BgMode mode)
{
	d->bgMode = mode;
}

BgMode Widget::bgMode()
{
	return d->bgMode;
}

void Widget::setName(const char* name)
{
	if (name == NULL) return;
	d->name = name;
}

void Widget::setParent(Widget* p)
{
	d->parent = p;
}

const char* Widget::name()
{
	return d->name.c_str();
}

Widget* Widget::topParent()
{
	Widget* tmpW = this;
	while(tmpW)
	{
		if (tmpW->parent())
		{
			//printf("Widget::topParent '%s' parent:%s\n", 
			//	name(), tmpW->parent()->name());
			tmpW = tmpW->parent();
			continue;
		}
		break;
	}

	//printf("Widget::topParent found '%s' topParent name:%s\n",
	//	name(), tmpW->name());

	return tmpW;
}

Widget* Widget::parent()
{
	return d->parent;
}

Font* Widget::setFont(const char* name, int size)
{
	d->font = theApp->fontDB().font(name, size);
	return d->font;
}

void Widget::setFontSize(int size)
{
	d->font = theApp->fontDB().font(
		theApp->fontName().c_str(), size);
}

Font* Widget::font() 
{ 
	return d->font; 
}

void Widget::setDisable(bool disable)
{
	//printf("Widget::setDisable name:%s disable:%d\n", name(), disable);
	d->disable = disable;
}

bool Widget::disable()
{
	return d->disable;
}

SDL_Surface* Widget::surface()
{
	return d->surface;
}

void Widget::setWidgetKeyMover(WidgetKeyMover a) 
{ 
	d->keyMover = a; 
}

WidgetKeyMover& Widget::keyMover()
{
	return d->keyMover;
}

Palette& Widget::palette()
{
	return d->palette;
}

void Widget::setPalette(Palette p)
{
	d->palette = p;
}

int Widget::x() { return d->geometry.x(); }

int Widget::y() { return d->geometry.y(); }

int Widget::width() { return d->geometry.width(); }

int Widget::height() { return d->geometry.height(); }

Rect Widget::geometry() { return d->geometry; }

void Widget::center(int w, int h)
{
	int screenW = theApp->desktopWidget()->width();
	int screenH = theApp->desktopWidget()->height();

	setGeometry((screenW-w)/2, (screenH-h)/2, w, h);
}

void Widget::center()
{
	center(width(), height());
}

void Widget::setGeometry(int x, int y, int w, int h)
{
	//printf("Widget::setGeometry name:%s newRect(x:%d y:%d w:%d h:%d)\n", 
	//	name(), x, y, w, h);
	if (!isVisible())
	{
		d->geometry = Rect(x, y, w, h);
		//printf("Widget::setGeometry name:%s not visible\n", name());
		return;
	}

	if (width() != w || height() != h)
	{
		Rect oldRect = 
			Rect(geometry().x(), geometry().y(), width(), height());
		Rect newRect = Rect(x, y, w, h);
		ResizeEvent* evt = new ResizeEvent(oldRect, newRect);
		theApp->postEvent(this, evt);
	}
	else
	{
		Point oldPt(geometry().x(), geometry().y());
		Point newPt(x, y);
		MoveEvent* evt = new MoveEvent(oldPt, newPt);
		theApp->postEvent(this, evt);
	}
}

void Widget::resize(int w, int h)
{
	setGeometry(x(), y(), w, h);
}

Image* Widget::background()
{
	return d->bgImage;
}

void Widget::setBackground(const char* fn)
{
	if (d->bgImage != 0)
	{
		delete d->bgImage;
		d->bgImage = 0;
	}

	d->bgImage = new Image;
	if (!d->bgImage->load(fn))
	{
		delete d->bgImage;
		d->bgImage = 0;
		//printf("Widget::setBackground failed to open '%s'\n", fn);
		return;
	}
}

void Widget::setMaskClear()
{
	d->maskColorFlag = false;
}

void Widget::setMaskColor(const Color& rgb)
{
	d->maskColor = rgb;
	d->maskColorFlag = true;
}

Color Widget::maskColor()
{
	return d->maskColor;
}

bool Widget::create()
{
	//printf("Widget::create name:%s\n",  name());
	bool f = create(&d->surface, width(), height());

	return f;
}

bool Widget::create(SDL_Surface** s, int w, int h)
{
	//printf("Widget::create name:%s w:%d h:%d\n", name(), w, h);
	if (w == 0 || h == 0) return true;

	SDL_Surface* surface = *s;
	bool doCreate = true;

	if (surface)
	{
		// check changed size
		if (surface->w != w || surface->h != h)
		{
			SDL_FreeSurface(surface);
			surface = 0;
		}
		else
		{
			// already created
			return true;
		}
	}

	if (doCreate)
	{
		//printf("Widget::create name:%s\n",  name());
		int flags = SDL_SWSURFACE | SDL_DOUBLEBUF;
		if (d->style & Style_NoTitle) flags |= SDL_NOFRAME;

		int Rmask = theApp->desktopWidget()->rMask();
		int Gmask = theApp->desktopWidget()->gMask();
		int Bmask = theApp->desktopWidget()->bMask();
		int Amask = theApp->desktopWidget()->aMask();
		int bpp = theApp->desktopWidget()->bpp();

		surface = SDL_CreateRGBSurface(flags, w, h, bpp, Rmask, 
										Gmask, Bmask, Amask);
		if (theApp->desktopWidget()->surface()->format->palette)
		{
			SDL_Palette* pal = 
				theApp->desktopWidget()->surface()->format->palette;
			SDL_SetPalette(surface, SDL_LOGPAL|SDL_PHYSPAL, 
				pal->colors, 0, pal->ncolors);
		}

		if (!surface)
		{
			printf("Widget::create Failed to create surface name:%s (%s)\n", 
				name()?name():"NULL", SDL_GetError());
			return false;
		}
		if ( surface && d->maskColorFlag )
		{
			Uint32 colorKey = SDL_MapRGB(surface->format, d->maskColor.r,
					d->maskColor.g, d->maskColor.b);
			SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorKey);
		}

		//printf("Widget::create SDL_CreateRGBSurface name:%s w:%d h:%d\n", 
		//	name(), w, h);
	}

	*s = surface;
	return true;
}

void Widget::close(int ret)
{
	//printf("Widget::close name:%s ret:%d\n", name(), ret);
	hide();
	if (!isModal()) return;

	setResult(ret);
	Event* evt = new Event(Event::Close);
	theApp->postEvent(this, evt);
	d->closing = true;
}

void Widget::close()
{
	close(0);
}

int Widget::exec()
{
	d->closed = false;
	d->closing = false;
	setResult(0);
	setModal(true);

	Widget* savedModalWidget = theApp->modalWidget();
	theApp->setModalWidget(this);

	Widget* savedFocusWidget = theApp->focusWidget();

	show();

	//printf("Widget::exec name:%s...1\n", name());
	while (!d->closed)
	{
		theApp->processEvent();
	}

	//printf("Widget::exec name:%s...2\n", name());
	theApp->setModalWidget(savedModalWidget);

	theApp->setFocusWidget(savedFocusWidget);

	return d->result;
}

void Widget::event(Event* evt)
{
	switch(evt->msg())
	{
		case Event::Show:
		{
			//printf("\n\nWidget::event Show name:%s\n", name());

			setVisible(true);

			// focus
			if (d->focusPolicy != NoFocus)
			{
				Widget* focusW = focusWidget();
				focusW->d->hasFocus = true;
				theApp->setFocusWidget(focusW);
			}

			showEvent();

			if (!isVisible())
			{
				//printf("Widget::event Show name:%s is not visible\n", name());
				return;
			}

			Point globalPt = mapToGlobal(0, 0);
			Rect rect(globalPt.x(), globalPt.y(), width(), height());
			theApp->desktopWidget()->paint(rect);

			showFinishedEvent();

			break;
		}
		case Event::Hide:
		{
			//printf("\n\nWidget::event Hide name:%s\n", name());
			releaseMouse();	

			setVisible(false);

			d->hasFocus = false;

			if (theApp->focusWidget() == this)
			{
				theApp->setFocusWidget(0);
			}

			hideEvent();
			
			if (!isModal() && parent() == 0)
			{
				theApp->desktopWidget()->nextMainWidget(this);
			}

			Point globalPt = mapToGlobal(0, 0);
			Rect rect(globalPt.x(), globalPt.y(), width(), height());
			theApp->desktopWidget()->paint(rect);

			break;
		}
		case Event::Paint:
		{
			//printf("\n\nWidget::event Paint name:%s\n", name());
			if (!isVisible()) 
			{
				//printf("Widget::event Paint name:%s isVisible:%d\n", 
				//	name(), isVisible());
				return;
			}
			if (parent() && !parent()->isVisible()) 
			{
				//printf("Widget::event Paint name:%s parent is not visible:%d\n", 
				//	name(), parent()->isVisible());
				return;
			}

			PaintEvent* e = (PaintEvent*)evt;
			Point globalPt = mapToGlobal(e->rect().x(), e->rect().y());
			Rect rect(globalPt.x(), globalPt.y(), 
					e->rect().width(), e->rect().height());
			//printf("Widget::event Paint name:%s orig(x:%d y:%d w:%d h:%d)\n", 
			//	name(), e->rect().x(), e->rect().y(), 
			//	e->rect().width(), e->rect().height());
			//printf("Widget::event Paint name:%s global(x:%d y:%d w:%d h:%d)\n", 
			//	name(), rect.x(), rect.y(), rect.width(), rect.height());
			theApp->desktopWidget()->paint(rect);
			break;
		}

		case Event::Close:
		{
			//printf("\n\nWidget::event Close name:%s\n", name());
			setModal(false);
			d->closed = true;
			d->closing = false;
			break;
		}

		case Event::Move:
		{
			MoveEvent* e = (MoveEvent*)evt;

			//printf("Widget::event Move name:%s oldPoint:%d, %d\n", 
			//	name(),
			//	e->oldPoint().x(),
			//	e->oldPoint().y());
			//printf("Widget::event Move name:%s newPoint:%d, %d\n", 
			//	name(),
			//	e->newPoint().x(),
			//	e->newPoint().y());

			Point oldGlobalPt = mapToGlobal();
			d->geometry = 
				Rect(e->newPoint().x(), e->newPoint().y(), width(), height());
			Point newGlobalPt = mapToGlobal();

			Rect oldRect(oldGlobalPt.x(), oldGlobalPt.y(), width(), height());
			// 이전좌표값의 내용이 한번 더 그려지는것을 방지하기 위해
			setVisible(false); 
			theApp->desktopWidget()->paint(oldRect);
			setVisible(true);

			Rect newRect(newGlobalPt.x(), newGlobalPt.y(), width(), height());
			theApp->desktopWidget()->paint(newRect);

			break;
		}

		case Event::Resize:
		{
			ResizeEvent* e = (ResizeEvent*)evt;

			//printf("Widget::event Resize name:%s oldRect:%d, %d, %d, %d\n", 
			//	name(),
			//	e->oldRect().x(),
			//	e->oldRect().y(),
			//	e->oldRect().width(),
			//	e->oldRect().height());
			//printf("Widget::event Resize name:%s newRect:%d, %d, %d, %d\n", 
			//	name(),
			//	e->newRect().x(),
			//	e->newRect().y(),
			//	e->newRect().width(),
			//	e->newRect().height());

			Point oldGlobalPt = mapToGlobal();
			d->geometry = Rect(
				e->newRect().x(), e->newRect().y(), 
				e->newRect().width(), e->newRect().height());
			Point newGlobalPt = mapToGlobal();

			Rect oldRect(oldGlobalPt.x(), oldGlobalPt.y(), 
					e->oldRect().width(), e->oldRect().height());
			// 이전좌표값의 내용이 한번 더 그려지는것을 방지하기 위해
			setVisible(false); 
			theApp->desktopWidget()->paint(oldRect);
			setVisible(true); 

			create();

			Rect newRect(newGlobalPt.x(), newGlobalPt.y(), 
					e->newRect().width(), e->newRect().height());
			theApp->desktopWidget()->paint(newRect);

			break;
		}

		case Event::FocusIn:
		{
			//printf("\n\nWidget::event FocusIn name:%s\n", name());
			//printf("Widget::event FocusIn name:%s isClosed:%d\n",
			//	name(), isClosed());
			FocusInEvent* e = (FocusInEvent*)evt;
			focusInEvent(e);
			break;
		}

		case Event::FocusOut:
		{
			//printf("\n\nWidget::event FocusOut name:%s\n", name());
			d->hasFocus = false;

			//printf("Widget::event FocusOut name:%s isClosed:%d\n",
			//	name(), isClosed());
			FocusOutEvent* e = (FocusOutEvent*)evt;
			focusOutEvent(e);
			break;
		}

		case Event::Enter:
		{
			//printf("Widget::event Enter name:%s\n", name());
			enterEvent();
			break;
		}

		case Event::Leave:
		{
			//printf("Widget::event Leave name:%s\n", name());
			leaveEvent();
			break;
		}

		case Event::Timer:
		{
			break;
		}

		case Event::KeyPress:
		case Event::KeyRelease:
		{
			Widget* w = this;
			while(1)
			{
				
				if (w->keyEvent((KeyEvent*)evt)) break;
				if (w->parent() == 0) break;
				if (w->parent()->isModal()) break;
				w = w->parent();
			}
			break;
		}

		case Event::MousePress:
		case Event::MouseRelease:
		case Event::MouseMove:
		{
			mouseEvent((MouseEvent*)evt);
			break;
		}

		case Event::Custom:
		{
			customEvent((CustomEvent*)evt);
			break;
		}
		default: { break; }
	}
}

void Widget::showEvent()
{
	//printf("Widget::showEvent name:%s\n", name());
}

void Widget::showFinishedEvent()
{
	//printf("Widget::showFinishedEvent name:%s\n", name());
}


void Widget::hideEvent()
{
	//printf("Widget::hideEvent name:%s\n", name());
}

void Widget::show()
{
	if (isVisible()) return;

	theApp->postEvent(this, new Event(Event::Show));
}

void Widget::hide()
{
	if (!isVisible()) return;
	if (isClosed()) return;

	//printf("Widget::hide name:%s\n", name());
	theApp->postEvent(this, new Event(Event::Hide));
}

Widget::WidgetList& Widget::childList() { return d->childList; };

Widget* Widget::findChild(Widget* w)
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

bool Widget::isVisible()
{
	if (!d->visible) return false;

	Widget* p = parent();
	while(p)
	{
		if (!p->isVisible()) return false;
		p = p->parent();
	}

	return true;
}

void Widget::setVisible(bool f/*=true*/)
{
	d->visible = f;
}

bool Widget::hasFocus()
{
	return d->hasFocus;
}

void Widget::killFocus()
{
	d->hasFocus = false;
}

void Widget::setFocus(bool f/*=true*/)
{
	if (disable()) return;

	//printf("Widget::setFocus name:%s f:%d\n", name(), f);

	if (d->focusPolicy == NoFocus) return;
	if (d->hasFocus == f) return;

	d->hasFocus = f;

	Widget* w = focusWidget();
	if (w->isVisible())
	{
		FocusInEvent* evt = new FocusInEvent;
		theApp->postEvent(w, evt);
	}
	theApp->setFocusWidget(w);
}

void Widget::update()
{
	update(Rect(0, 0, width(), height()));
}

void Widget::update(const Rect& rect)
{	
	if (d->surface == 0) return;
	if (rect.width() == 0 || rect.height() == 0) return;

	if (!isVisible()) return;

	paint(rect);

	//printf("Widget::update region name:%s "
	//	"isVisible:%d local x:%d y:%d w:%d h:%d\n", 
	//	name(), isVisible(), 
	//	rect.x(), rect.y(), rect.width(), rect.height());

	SDL_Rect srcRect;
	srcRect.x = rect.x();
	srcRect.y = rect.y();
	srcRect.w = rect.width();
	srcRect.h = rect.height();

	Point localPt(rect.x(), rect.y());
	Point globalPt = mapToGlobal(localPt);

	//printf("Widget::update region name:%s global x:%d y:%d w:%d h:%d\n",
	//	name(),
	//	globalPt.x(), globalPt.y(), rect.width(), rect.height());

	SDL_Rect dstRect;
	dstRect.x = globalPt.x();
	dstRect.y = globalPt.y();
	dstRect.w = rect.width();
	dstRect.h = rect.height();

	SDL_Surface* desktopSurface = theApp->desktopWidget()->surface();
	SDL_Surface* targetSurface = d->surface;

	Painter::blitSurface(this, targetSurface, &srcRect,
		desktopSurface, &dstRect);

	SDL_UpdateRect(desktopSurface, 
		globalPt.x(), globalPt.y(), rect.width(), rect.height());
}

void Widget::repaint(PaintEvent* evt)
{
	//printf("Widget::repaint name:%s x:%d y:%d w:%d h:%d\n",
	//	name(), evt->rect().x(), evt->rect().y(), 
	//	evt->rect().width(), evt->rect().height());
	paint(evt);
}

void Widget::repaint(const Rect& rect)
{
	PaintEvent* evt = new PaintEvent(rect);
	theApp->postEvent(this, evt);
}

void Widget::repaint()
{
	Rect rect(0, 0, width(), height());
	repaint(rect);
}

void Widget::paintBg(const Rect& r)
{
	if (surface() == 0) return;

	//printf("Widget::paintBg name:%s x:%d y:%d w:%d h:%d\n", 
	//	name(), r.x(), r.y(), r.width(), r.height());
	SDL_Rect srcRect;
	srcRect.x = r.x();
	srcRect.y = r.y();
	srcRect.w = r.width();
	srcRect.h = r.height();

	if (d->bgImage && d->bgImage->surface())
	{
		PD::Painter p(this);
		p.setBrushColor( palette().color(Palette::Background));
		p.fillRect(r);

		SDL_Surface* bg = d->bgImage->surface();
		Painter::blitSurface(this, bg, &srcRect, surface(), NULL);
		//printf("Widget::paintBg imageBg name:%s\n", name());
	}
	else
	{
		if (d->bgMode == FillBg)
		{
			PD::Painter p(this);
			p.setBrushColor( palette().color(Palette::Background));
			p.fillRect(r);
			//printf("Widget::paintBg fillBg name:%s\n", name());
		}
		else if (d->bgMode == ParentBg)
		{
			if (parent())
			{
				SDL_Rect srcRect;
				srcRect.x = geometry().x();
				srcRect.y = geometry().y();
				srcRect.w = geometry().width();
				srcRect.h = geometry().height();

				SDL_Rect dstRect;
				dstRect.x = 0;
				dstRect.y = 0;
				dstRect.w = width();
				dstRect.h = height();


				Painter::blitSurface(this, parent()->surface(), &srcRect, 
					surface(), &dstRect);

				//printf("Widget::paintBg parentBg name:%s\n", name());
			}
		}
		else  // NoBg
		{
			// nothing to do
		}
	}
}

void Widget::paintBg()
{
	Rect r(0, 0, width(), height());
	paintBg(r);
}

void Widget::paintChild(const Rect& r)
{
	if (d->childList.size() == 0) return;

	//printf("\tWidget::paintChild name:%s x:%d y:%d w:%d h:%d\n", 
	//	name(), r.x(), r.y(), r.width(), r.height());

	WidgetListIt it = d->childList.begin();
	while (it != d->childList.end())
	{
		Widget* widget = *it;

		if (widget && widget->isVisible())
		{
			//printf("Widget::paintChild child name:%s\n", 
			//	widget->name());
			//printf("widget x:%d y:%d w:%d h:%d\n", 
			//	widget->x(), widget->y(), 
			//	widget->width(), widget->height());
			if (widget->geometry().intersect(r))
			{
				//printf("\tWidget::paintChild name:%s childName:%s x:%d y:%d w:%d h:%d\n",
				//	name(), widget->name(),
				//	widget->x(), widget->y(), widget->width(), widget->height()
				//	);
					
				int x = 0;
				int y = 0;
				int w = 0;
				int h = 0;
				Rect childRect = widget->geometry();
				x = r.x() - childRect.x();
				y = r.y() - childRect.y();
				w = r.width();
				h = r.height();

				if (w > childRect.width()) w = childRect.width();
				if (h > childRect.height()) h = childRect.height();

				if (x < 0) x = 0;
				if (y < 0) y = 0;

				Rect repaintRect(x, y, w, h);
				widget->paint(repaintRect);

				SDL_Rect srcRect;
				srcRect.x = x;
				srcRect.y = y;
				srcRect.w = w;
				srcRect.h = h;

				//printf("widget->x():%d y:%d r(x:%d y:%d)\n", widget->x(), widget->y(), r.x(), r.y());

				SDL_Rect dstRect;
				dstRect.x = widget->x() + x;
				dstRect.y = widget->y() + y;
				dstRect.w = w;
				dstRect.h = h;

				//printf("\tWidget::paintChild parentName:%s childName:%s src(x:%d y:%d w:%d h:%d)\n",
				//	name(), widget->name(), srcRect.x, srcRect.y, srcRect.w, srcRect.h);
				//printf("\tWidget::paintChild parentName:%s childName:%s dst(x:%d y:%d w:%d h:%d)\n",
				//	name(), widget->name(), dstRect.x, dstRect.y, dstRect.w, dstRect.h);

				Painter::blitSurface(widget, widget->surface(), &srcRect,
						d->surface, &dstRect);
			}
		}
		it++;
	}
}

void Widget::paintChild()
{
	Rect r(0, 0, width(), height());
	paintChild(r);
}

void Widget::paint(PaintEvent* evt)
{
	//printf("\n\nWidget::paint name:%s x:%d y:%d w:%d h:%d\n", name(),
	//	evt->rect().x(), evt->rect().y(), 
	//	evt->rect().width(), evt->rect().height());
	if (!create()) return;

	paintBg(evt->rect());
	paintEvent(evt);
	paintChild(evt->rect());
}

void Widget::paint(const Rect& r)
{
	PaintEvent evt(r);	
	paint(&evt);
}

void Widget::paint()
{
	Rect r(0, 0, width(), height());
	paint(r);
}

void Widget::paintEvent(PaintEvent*)
{
	//printf("\tWidget::paintEvent name:%s\n", name());
}

void Widget::resizeEvent(ResizeEvent*)
{
	//printf("Widget::resizeEvent name:%s\n", name());
}


bool Widget::focusInEvent(FocusInEvent*)
{
	//printf("Widget::focusInEvent name:%s\n", name());
	return true;
}

bool Widget::focusOutEvent(FocusOutEvent*)
{
	//printf("Widget::focusOutEvent name:%s\n", name());
	return true;
}

void Widget::enterEvent()
{
	//printf("Widget::enterEvent name:%s\n", name());
}

void Widget::leaveEvent()
{
	//printf("Widget::leaveEvent name:%s\n", name());
}

Widget* Widget::focusWidget()
{
	Widget* focusWidget = this;

	if (d->childList.size())
	{
		WidgetListIt it = d->childList.begin();
		while (it != d->childList.end())
		{
			Widget* w = *it;
			//printf("Widget::focusWidget name:%s child:(%s, focus:%d visible:%d)\n",
			//	name(), w->name(), w->hasFocus(), w->isVisible());
			if (w && w->hasFocus() && w->isVisible()) focusWidget = w;
			it++;
		}
	}
	//printf("Widget::focusWidget name:%s found:%s\n",
	//	name(), focusWidget->name());
	return focusWidget;

}

void Widget::timerEvent()
{
}

/**
 * \brief
 * 
 * \param type SDL_KEYDOWN, SDL_KEYUP
 * \param key 
 * 
 * \return bool
 */
bool Widget::keyEvent(KeyEvent* evt)
{
	//printf("Widget::keyEvent name:%s msg:%d key:%d\n", 
	//	name(), evt->msg(), evt->key());
	bool f = false;
	if (evt->msg() == Event::KeyPress) f = keyPressEvent(evt);
	else if (evt->msg() == Event::KeyRelease) f = keyReleaseEvent(evt);

	return f;
}

bool Widget::keyPressEvent(KeyEvent*)
{
	//printf("Widget::keyPressEvent name:%s key:%d\n", name(), evt->key());
	return false;
}

bool Widget::keyReleaseEvent(KeyEvent* evt)
{
	if (evt->key() == SDLK_UP || evt->key() == SDLK_DOWN || 
		evt->key() == SDLK_LEFT || evt->key() == SDLK_RIGHT)
	{
		if (handleKeyMove(evt)) return true;
	}
	//printf("Widget::keyReleaseEvent name:%s key:%d\n", name(), evt->key());
	return false;
}

bool Widget::hasContains(int x, int y)
{
	Point inputPt(x, y);
	Point localPt(0, 0);
	Point globalPt = mapToGlobal(localPt);

	//printf("Widget::hasContains name:%s input(x:%d,y:%d) x:%d y:%d w:%d h:%d\n",
	//	name(), x, y, globalPt.x(), globalPt.y(), width(), height());

	Rect globalRect(globalPt.x(), globalPt.y(), width(), height());
	return globalRect.contains(inputPt);
}

Widget* Widget::findMouseWidget(const Point& pt)
{
	Widget* findWidget = this;

	WidgetListReverseIt it = d->childList.rbegin();
	while (it != d->childList.rend())
	{
		Widget* widget = (*it);
		//printf("Widget::findMouseWidget checking name:%s\n", widget->name());
		if (widget && widget->isVisible())
		{
			Rect rect = Rect(widget->mapToGlobal(), widget->width(), widget->height());
			if (rect.contains(pt))
			{
				findWidget = widget->findMouseWidget(pt);
				//printf("Widget::findMouseWidget found name:%s\n", findWidget->name());
				break;
			}
		}
		it++;
	}

	return findWidget;
}

void Widget::mouseEvent(MouseEvent* evt)
{
	MouseEvent::Msg msg = evt->msg(); 
	MouseEvent::Button button = evt->button();

	if (theApp->mouseWidget() && theApp->mouseWidget() != this)
	{
		//Event* evt = new Event(Event::Leave);
		//theApp->postEvent(theApp->mouseWidget(), evt);
		theApp->mouseWidget()->leaveEvent();
	}

	if (theApp->mouseWidget() != this)
	{
		grabMouse();
		//Event* evt = new Event(Event::Enter);
		//theApp->postEvent(this, evt);
		enterEvent();
	}

	// wheel
	if (button == MouseEvent::WheelUp || button == MouseEvent::WheelDown)
	{	
		//printf("Widget::mouseEvent wheel name:%s\n", name());
		if (msg == Event::MouseRelease)
		{
			if (button == MouseEvent::WheelUp) 
				wheelUpEvent(evt);
			else if (button == MouseEvent::WheelDown)
				wheelDownEvent(evt);
		}
		return;
	}

	if (msg == Event::MouseMove) 
	{
		//printf("Widget::mouseEvent mouseMove name:%s\n", name());
		mouseMoveEvent(evt);
	}

	if (msg == Event::MousePress) 
	{
		//printf("Widget::mouseEvent mouseDown name:%s\n", name());
		mousePressEvent(evt);
	}
	else if (msg == Event::MouseRelease) 
	{
		//printf("Widget::mouseEvent mouseUp name:%s\n", name());
		mouseReleaseEvent(evt);
	}
	else return;
}

/**
 * \brief Grab the mouse
 */
void Widget::grabMouse()
{
	theApp->setMouseWidget(this);
}

/**
 * \brief Release the mouse grab
 */
void Widget::releaseMouse()
{
	theApp->setMouseWidget(NULL);
}

void Widget::mousePressEvent(MouseEvent* /*evt*/)
{
	//printf("Widget::mousePressEvent name:%s button:%d x:%d y:%d\n", 
	//	name(), evt->button(), evt->x(), evt->y());
}

void Widget::mouseReleaseEvent(MouseEvent* /*evt*/)
{
	//printf("Widget::mouseReleaseEvent name:%s button:%d x:%d y:%d\n", 
	//	name(), evt->button(), evt->x(), evt->y());
}

void Widget::mouseMoveEvent(MouseEvent* /*evt*/)
{
	//printf("Widget::mouseMoveEvent name:%s x:%d y:%d\n", 
	//	name(), evt->x(), evt->y());
}

void Widget::mouseDoubleClickEvent(MouseEvent* /*evt*/)
{
	//printf("Widget::mouseDoubleClickEvent name:%s x:%d y:%d\n", 
	//	name(), evt->x(), evt->y());
}

void Widget::wheelUpEvent(MouseEvent* /*evt*/)
{
	//printf("Widget::wheelUpEvent name:%s\n", name());
}

void Widget::wheelDownEvent(MouseEvent* /*evt*/)
{
	//printf("Widget::wheelDownEvent name:%s\n", name());
}

void Widget::customEvent(CustomEvent* /*evt*/)
{
	//printf("Widget::customEvent name:%s code:%d\n", name(), code);
}

void Widget::addChild(Widget* w)
{
	assert(w != NULL);

	d->childList.push_back(w);

	//printf("Widget::addChild name:%s childName:%s\n", 
	//	name(), w->name());
}

void Widget::removeChild(Widget* w)
{
	assert (w != NULL);
	d->childList.remove(w);

	//printf("Widget::removeChild name:%s childName:%s\n", 
	//	name(), w->name());
}

Point Widget::mapToGlobal()
{
	return mapToGlobal(0, 0);
}

Point Widget::mapToGlobal(const Point& pt)
{
	return mapToGlobal(pt.x(), pt.y());
}

Point Widget::mapToGlobal(int x, int y)
{
	int posX = geometry().x() + x;
	int posY = geometry().y() + y;

	Widget* w = parent();
	while(w)
	{
		if (!w) break;
		posX += w->x();
		posY += w->y();

		w = w->parent();
	}

	Point p;
	p.setX( posX );
	p.setY( posY );

	return p;
}

Point Widget::mapFromGlobal(const Point& pt)
{
	//printf("Widget::mapFromGlobal name:%s global x:%d y:%d\n",
	//	name()?name():"NULL", pt.x(), pt.y());

	int posX = pt.x() - x();
	int posY = pt.y() - y();

	Widget* w = parent();
	while(w)
	{
		//printf("Widget::mapFromGlobal name:%s x:%d y:%d\n",
		//	w->name()?w->name():"NULL", w->x(), w->y());

		posX -= w->x();
		posY -= w->y();
		w = w->parent();
	}

	Point p;
	p.setX( posX );
	p.setY( posY );

	return p;
}

void Widget::draw3DEffect(Painter* p, bool selected/*=false*/)
{
	// 3D bevel effect
	Color color1 = palette().color(Palette::LightColor);
	Color color2 = palette().color(Palette::DarkColor);

	if (selected)
	{
		Color colorTemp = color1;
		color1 = color2;
		color2 = colorTemp;
	}

	p->setPenColor( color1 );
	p->drawHLine(0, 0, width()-1, 1); 
	p->drawVLine(0, 0, 1, height()-1);

	p->setPenColor( color2 );
	p->drawHLine(0, height()-1, width(), height()-1);
	p->drawVLine(width()-1, 1, 1, height());
}

bool Widget::handleKeyMove(KeyEvent* evt)
{
	if (evt->key() == SDLK_UP && d->keyMover.up()) 
	{
		d->keyMover.up()->setFocus();
		return true;
	}
	else if (evt->key() == SDLK_DOWN && d->keyMover.down()) 
	{
		d->keyMover.down()->setFocus();
		return true;
	}
	else if (evt->key() == SDLK_LEFT && d->keyMover.left()) 
	{
		d->keyMover.left()->setFocus();
		return true;
	}
	else if (evt->key() == SDLK_RIGHT && d->keyMover.right()) 
	{
		d->keyMover.right()->setFocus();
		return true;
	}
	return false; 
}

} //namespace PD {

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
#include "PDButton.h"
#include "PDButton_p.hpp"
#include "PDGlobal.h"

namespace PD {

/**
 * \brief 생성자
 * 
 * \param parent 부모위젯
 * \param name 이름
 */
Button::Button(Widget* parent, const char* name/*=0*/) : 
	Widget(parent, name, 0, Theme::Button)
{
	d = 0;
	d = new ButtonPrivate;
	d->initPalette(this);
	setBgMode(NoBg);
}

/**
 * \brief 생성자
 * 
 * \param parent 부모위젯
 * \param name 이름
 * \param name 텍스트
 */
Button::Button(Widget* parent, const char* name, const char* text) : 
	Widget(parent, name, 0, Theme::Button)
{
	d = 0;
	d = new ButtonPrivate;
	d->initPalette(this);
	setText(text);
	setBgMode(NoBg);
}

/**
 * \brief 소멸자
 */
Button::~Button()
{
	if (d) delete d;
}

/**
 * \brief 텍스트를 가져옴
 *
 * \return 텍스트
 * \sa setText()
 */
std::string Button::text()
{
	return d->text;
}

/**
 * \brief 텍스트를 설정
 *
 * \param text 텍스트
 * \sa text()
 */
void Button::setText(const std::string& text)
{
	d->text = text;
}
#define SETBG(TYPE, NAME) \
	void Button::set##NAME(const char* fn) \
	{\
		if ( fn == 0 ) return; \
		if ( strlen(fn) == 0 ) return; \
		if ( TYPE ) delete TYPE; \
		TYPE = new Image; \
		if (!TYPE->load(fn) ) \
		{ \
			delete TYPE; \
			TYPE = 0; \
			printf("Button::%s failed to load '%s'\n", #NAME, fn); \
			return; \
		}\
	}
SETBG(d->bgLeft, BackgroundLeft);
SETBG(d->bgRight, BackgroundRight);
SETBG(d->focusBg, FocusBg);
SETBG(d->focusBgLeft, FocusBgLeft);
SETBG(d->focusBgRight, FocusBgRight);
SETBG(d->hoverBg, HoverBg);
SETBG(d->hoverBgLeft, HoverBgLeft);
SETBG(d->hoverBgRight, HoverBgRight);
SETBG(d->disabledBg, DisabledBg);
SETBG(d->disabledBgLeft, DisabledBgLeft);
SETBG(d->disabledBgRight, DisabledBgRight);

#define BG(type, NAME) \
	Image* Button::NAME() \
	{ \
		return type; \
	}

BG(d->bgLeft, backgroundLeft);
BG(d->bgRight, backgroundRight);
BG(d->focusBg, focusBg);
BG(d->focusBgLeft, focusBgLeft);
BG(d->focusBgRight, focusBgRight);
BG(d->hoverBg, hoverBg);
BG(d->hoverBgLeft, hoverBgLeft);
BG(d->hoverBgRight, hoverBgRight);
BG(d->disabledBg, disabledBg);
BG(d->disabledBgLeft, disabledBgLeft);
BG(d->disabledBgRight, disabledBgRight);

/**
 * \brief 토글버튼인지 확인
 *
 * \return true/false
 * \sa setToggleButton()
 */
bool Button::isToggleButton() { return d->toggleButton; }

/**
 * \brief 토글버튼으로 설정
 *
 * \param f true/false
 * \sa toggleButton()
 */
void Button::setToggleButton(bool f) { d->toggleButton = f; } 	

bool Button::isOn() { return d->on; }
void Button::setOn(bool f) { d->on = f; } 

int Button::state()
{
	return d->state;
}

void Button::setState(State stat) { d->state = stat; }


int Button::alignment()
{
	return d->alignment;
}

void Button::setAlignment(int align)
{
	d->alignment = align;
}

void Button::paintEvent(PaintEvent*)
{
	//printf("Button::paintEvent name:%s\n", name());

	Painter p(this);

	if (d->focusBg && hasFocus())
	{
		d->drawImage(this, p, d->focusBgLeft, d->focusBg, d->focusBgRight);	
		p.setBrushColor(palette().color(Palette::Highlight));
	}
	else
	{
		if (d->state == Normal && background())
		{
			d->drawImage(this, p, backgroundLeft(), background(), backgroundRight());		
		}
		else if (d->state == Hover && d->hoverBg)
		{
			d->drawImage(this, p, d->hoverBgLeft, d->hoverBg, d->hoverBgRight);	
			p.setBrushColor(palette().color(Palette::Highlight));
		}
		else if (d->state == Disabled && d->disabledBg)
		{
			d->drawImage(this, p, d->disabledBgLeft, d->disabledBg, d->disabledBgRight);	
		}
		else
		{	
			// draw background
			if (d->down || isOn())
			{
				p.setBrushColor(palette().color(Palette::FocusColor));
				p.fillRect(0, 0, width(), height());
			}
			else
			{
				p.setBrushColor(palette().color(Palette::Background));
				p.fillRect(0, 0, width(), height());
			}

			bool selected = d->down;
			if (isToggleButton()) selected = isOn();
			draw3DEffect(&p, selected);
		}
	}

	// draw text
	if (hasFocus()) p.setPenColor( palette().color(Palette::HighlightText) );
	else p.setPenColor( palette().color(Palette::Text, (Palette::State)disable()) );

	p.drawText(Rect(2, 0, width()-4, height()), d->text.c_str(),
		(Alignment)alignment());
	
	//printf("Button::paintEvent name:%s hasFocus:%d\n", name(), hasFocus());

	// draw focus rect
	if (!d->focusBg && !d->hoverBg && hasFocus())
	{
		p.setPenColor(  palette().color(Palette::FocusColor));
		if (d->down || isOn())
			p.drawRect(2, 2, width()-3, height()-4);
		else
			p.drawRect(2, 2, width()-3, height()-4);
	}
	else if (d->hoverBg && isToggleButton() && isOn())
	{
		d->drawImage(this, p, d->hoverBgLeft, d->hoverBg, d->hoverBgRight);
	}
}

bool Button::focusInEvent(FocusInEvent*)
{
	if (disable()) return true;

	//printf("Button::focusInEvent name:%s\n", name());
	repaint();

	return false;
}

bool Button::focusOutEvent(FocusOutEvent*)
{
	if (disable()) return true;

	//printf("Button::focusOutEvent name:%s\n", name());
	d->state = Normal;
	d->down = false;
	repaint();

	return false;
}

void Button::mousePressEvent(MouseEvent* evt)
{
	if (disable()) return ;
	if (evt->button() != MouseEvent::Left) return;

	//printf("Button::mousePressEvent name:%s\n", name());
	d->down = true; 
	repaint();
}

void Button::mouseReleaseEvent(MouseEvent* evt)
{
	if (disable()) return;
	if (!d->down) return;

	//printf("Button::mouseReleaseEvent name:%s\n", name());
	d->down = false;

	bool doRepaint = true;
	bool doEmitSignal = false;

	if (hasContains(evt->x(), evt->y()) && isVisible()) 
	{
		if (isToggleButton()) d->on = !d->on;
		if (!hasFocus()) { setFocus(); doRepaint = false; }
		doEmitSignal = true;
	}

	if (doRepaint) repaint();
	if (doEmitSignal) clicked.emit(this);
}

void Button::enterEvent()
{
	if (d->hoverBg) 
	{
		//printf("Button::enterEvent name:%s\n", name());
		d->state = Hover;
		repaint();
	}
}

void Button::leaveEvent()
{
	if (d->hoverBg && d->state == Hover) 
	{
		//printf("Button::leaveEvent name:%s\n", name());
		d->state = Normal;
		repaint();
	}

	if (d->down)
	{
		d->down = false; 
		repaint();
	}
}

bool Button::keyPressEvent(KeyEvent* evt)
{
	if (disable()) return true;
	if (evt->key() == SDLK_RETURN) 
	{
		if (isToggleButton()) { d->on = !d->on; repaint(); }
		//printf("Button::keyPressEvent SDLK_RETURN\n");
		return true;
	}

	return Widget::keyPressEvent(evt);
}

bool Button::keyReleaseEvent(KeyEvent* evt)
{
	if (disable()) return true;

	if (evt->key() == SDLK_RETURN)
	{
		clicked.emit(this);
		return true;
	}

	return Widget::keyReleaseEvent(evt);
}

} //namespace PD {

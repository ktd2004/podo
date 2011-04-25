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
#include "PDCheckBox.h"
#include "PDCheckBox_p.hpp"
#include "PDCheckXpm.h"


namespace PD {

CheckBox::CheckBox(Widget* parent, const char* name/*=0*/) : 
	Widget(parent, name, 0 , Theme::CheckBox)
{
	d = new CheckBoxPrivate;
}

CheckBox::~CheckBox()
{
	delete d;
}

void CheckBox::setCheckFlag(bool flag)
{
	d->checkFlag = flag;	
	repaint();
}

bool CheckBox::checkFlag() { return d->checkFlag; }

void CheckBox::setCheckStyle(CheckStyle s) { d->checkStyle = s; }

void CheckBox::setText(const char* text) { d->text = text; }
std::string CheckBox::text() { return d->text; }

bool CheckBox::focusInEvent(FocusInEvent*)
{
	repaint();
	return false;
}


bool CheckBox::focusOutEvent(FocusOutEvent*)
{
	repaint();
	return false;
}

void CheckBox::mouseReleaseEvent(MouseEvent* evt)
{
	if (isVisible() && !disable())
	{
		if (!hasFocus()) setFocus();
		setCheckFlag(!checkFlag());
		changeState.emit(d->checkFlag);
		changeStateWithWidget.emit(this, d->checkFlag);
	}
}

void CheckBox::paintEvent(PaintEvent*)
{
	Painter p(this);

	p.setPenColor(palette().color(Palette::Text, (Palette::State)disable()));
	Rect r = Rect(0, 0, geometry().width(), geometry().height());

	//printf("CheckBox::paintEvent x:%d y:%d w:%d h:%d\n", r.x(), r.y(), r.width(),
	//	r.height());
	int baseX = 0;
	int baseY = 0;
	if (hasFocus()) p.setBrushColor(palette().color(Palette::Highlight,
									(Palette::State)disable()));
	else p.setBrushColor(palette().color(Palette::Background,
						(Palette::State)disable()));

	p.fillRect(r);

	p.setPenColor(palette().color(Palette::Text,(Palette::State)disable()) );
	p.drawRect(r.x()+3+baseX, r.y()+3+baseY, r.x()+r.height()-3+baseX,
		r.y()+r.height()-3);
	p.drawRect(r.x()+4+baseX, r.y()+4+baseY, r.x()+r.height()-4+baseX,
		r.y()+r.height()-4);

	if (d->checkFlag)
	{
		if (d->checkStyle == CheckV)
		{
			Rect xpmRect(r.x()+baseX, r.y()+baseY, r.height(), r.height());
			Image img;

			if (img.loadXpm(check_xpm))
			{
				p.drawImage(xpmRect.x() + ((xpmRect.width()/2)-(img.width()/2)),
						xpmRect.y() + ((xpmRect.height()/2)-(img.height()/2)),
						img);
			}
		}
		else
		{
			Rect checkRect(r.x()+8+baseX, r.y()+8+baseY, r.height()-16,
					r.height()-16);
			p.save();
			p.setBrushColor(palette().color(Palette::Text, 
											(Palette::State)disable()));
			p.fillRect(r.x()+8+baseX, r.y()+8+baseY, r.height()-16, r.height()-16);
			p.restore();
		}

	}

	Alignment a = (Alignment)(AlignLeft | AlignVCenter);

	if (hasFocus()) p.setPenColor(palette().color(Palette::HighlightText,
									(Palette::State)disable()));
	else p.setPenColor(palette().color(Palette::Text,
						(Palette::State)disable()));

	p.drawText(
		Rect(r.x()+8+baseX+r.height()-16+10, //x
		0,  // y
		r.width() - r.x()+8+baseX+r.height()-16, //width
		r.height()),  //height
		d->text.c_str(), a); // text, alignment

	if (hasFocus())
	{
		p.setPenColor(  palette().color(Palette::FocusColor,
										(Palette::State)disable()));
		p.drawRect(0, 0, width()-1, height()-1);
	}
}

bool CheckBox::keyReleaseEvent(KeyEvent* evt)
{
	if (evt->key() == SDLK_RETURN)
	{
		setCheckFlag(!checkFlag());
		changeState.emit(d->checkFlag);
		changeStateWithWidget.emit(this, d->checkFlag);
		return true;
	}
	else if (evt->key() == SDLK_UP || evt->key() == SDLK_DOWN || 
			 evt->key() == SDLK_LEFT || evt->key() == SDLK_RIGHT)
	{
		return Widget::keyReleaseEvent(evt);
	}
	//printf("Widget::keyReleaseEvent key:%d\n", evt->key());
	return false;
}



} //namespace PD

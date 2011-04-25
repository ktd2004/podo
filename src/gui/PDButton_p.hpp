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
#ifndef _PDBUTTON_P_H_
#define _PDBUTTON_P_H_

#include "PDPainter.h"
#include "PDApp.h"

namespace PD {

class ButtonPrivate
{
public:
	std::string			text;
	
	Image*				bgLeft;
	Image*				bgRight;

	Image*				focusBg;
	Image*				focusBgLeft;
	Image*				focusBgRight;

	Image*				hoverBg;
	Image*				hoverBgLeft;
	Image*				hoverBgRight;

	Image*				disabledBg;
	Image*				disabledBgLeft;
	Image*				disabledBgRight;
	
	Button::State		state;
	int 				alignment;
	bool				toggleButton;
	bool				on;
	
	bool				down;

public:
	ButtonPrivate()
	{
		state = Button::Normal;

		bgLeft = 0;
		bgRight = 0;

		focusBg = 0;
		focusBgLeft = 0;
		focusBgRight = 0;

		hoverBg = 0;
		hoverBgLeft = 0;
		hoverBgRight = 0;

		disabledBg = 0;
		disabledBgLeft = 0;
		disabledBgRight = 0;

		alignment = AlignCenter;

		toggleButton = false;
		down = false;
		on = false;
	}

	~ButtonPrivate()
	{
		if (bgLeft) delete bgLeft;	
		if (bgRight) delete bgRight;	

		if (hoverBg) delete hoverBg;	
		if (disabledBg) delete disabledBg;	
		if (focusBg) delete focusBg;	

		if (hoverBgLeft) delete hoverBgLeft;	
		if (disabledBgLeft) delete disabledBgLeft;	
		if (focusBgLeft) delete focusBgLeft;	

		if (hoverBgRight) delete hoverBgRight;	
		if (disabledBgRight) delete disabledBgRight;	
		if (focusBgRight) delete focusBgRight;	
	}

	void initPalette(Button* btn)
	{
		Theme* theme = theApp->theme();
		if (theme)
		{
			Palette* p = theme->palette(Theme::Button);
			if (p) return;
		}

		btn->palette().setColor(Palette::HighlightText, black);
		btn->palette().setColor(Palette::Text, black);
		btn->palette().setColor(Palette::Background, lightgray);
	}

	void drawImage(Button* btn, PD::Painter& p, 
			Image* left, Image* center, Image* right)
	{
		if ( center == NULL ) return;
		if ( left == NULL && right == NULL )
		{
			p.drawImage(0, 0, *center);
			return;
		}

		int centerW = 0;
		if ( left && right ) centerW = btn->width() - left->width() - right->width();
		else if ( left && !right ) centerW = btn->width() - left->width();
		else if ( !left && right ) centerW = btn->width() - right->width();

		if ( centerW < 0 ) centerW = btn->width();

		int posX = 0;
		int cnt = centerW/center->width() + 1;
		if ( left ) 
		{
			p.drawImage(posX, 0, *left);
			posX += left->width();
		}
		if ( center )
		{
			for(int i=0; i<cnt; i++)
			{
				p.drawImage(posX, 0, *center);
				posX += center->width();
			}
		}
		if ( right ) p.drawImage(btn->width()-right->width(), 0, *right);
	}
};
} //namespace PD {

#endif

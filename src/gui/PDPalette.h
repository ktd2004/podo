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
#ifndef _PDPALETTE_H_
#define _PDPALETTE_H_

#include "PDColor.h"

namespace PD {

/**
 * \brief
 * \ingroup gui
 */
class Palette
{
public:
	enum ColorRole 
	{
		Background = 0,
		Highlight,
		Text,
		HighlightText,
		FocusColor,
		LightColor,
		DarkColor,
		MaxColorRole
	};

	enum State
	{ 
		Enable=0,
		Disable,
		MaxState,
	};

private:
	Color m_palette[Palette::MaxColorRole][Palette::MaxState];

public:
	Palette();
	Palette(Palette& c);
	~Palette();

	Color color(ColorRole, State s=Enable);
	void setColor(ColorRole role, Color c, State s=Enable);

	Palette& operator=(Palette& c);
	int operator==(Palette& c);
	int operator!=(Palette& c);
};

} // namespace PD

#endif

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
#ifndef _PDDESKTOPWIDGET_P_H_
#define _PDDESKTOPWIDGET_P_H_

namespace PD {

class DesktopWidgetPrivate
{
public:
	SDL_Surface* surface;
	Color brushColor;

	DesktopWidget::WidgetList childList;

	int width;
	int height;
	Uint32 rMask;
	Uint32 gMask;
	Uint32 bMask;
	Uint32 aMask;
	Uint8 bpp;

public:
	DesktopWidgetPrivate()
	{
		surface = 0;
		brushColor = lightgray;

		rMask = 0;
		gMask = 0;
		bMask = 0;
		aMask = 0;
		bpp = 0;

		width = 0;
		height = 0;
	}

	~DesktopWidgetPrivate()
	{
		childList.clear();
	}
};


} //namespace PD 
#endif

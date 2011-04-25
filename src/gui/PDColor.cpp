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
#include "PDColor.h"
#include "PDApp.h"

namespace PD {

Color white 		= Color(0xFF,0xFF,0xFF);
Color black 		= Color(0,0,0);
Color red 		= Color(0xFF,0,0);
Color green 		= Color(0,0xFF,0);
Color blue 		= Color(0,0,0xFF);
Color yellow 		= Color(0xFF,0xFF,0);
Color cyan 		= Color(0,0xFF,0xFF);
Color magenta 	= Color(0xFF,0,0xFF);

Color gray 		= Color(0x80,0x80,0x80);
Color lightgray 	= Color(0xF0,0xF0,0xF0);
Color darkgray 	= Color(0x40,0x40,0x40);

Color::Color()
{
	r = g = b = a = 0;
}
Color::Color(unsigned char red, unsigned char green, unsigned char blue,
		unsigned alpha/*=0*/)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

int Color::operator!=(const Color& c)
{
	return !(*this == c);
}

int Color::operator==(const Color& c)
{
	if(r != c.r) return 0;
	if(g != c.g) return 0;
	if(b != c.b) return 0;
	if(a != c.a) return 0;

	return 1;
}

Color& Color::operator=(const Color& c)
{
	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;

	return *this;
}

Color::operator int()
{
	return SDL_MapRGBA(
				theApp->desktopWidget()->surface()->format,
				r, g, b, a);
}


} //namespace PD {

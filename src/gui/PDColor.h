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
#ifndef _PDColor_H_
#define _PDColor_H_

#ifdef WIN32
#undef Color
#endif

namespace PD {

class Color
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Color();
	Color(unsigned char red, unsigned char green, unsigned char blue,
		unsigned alpha=0);
	
	int operator!=(const Color& c);
	int operator==(const Color& c);
	Color& operator=(const Color& c);
	operator int();
};

extern Color white;
extern Color black;
extern Color red;
extern Color green;
extern Color blue;
extern Color yellow;
extern Color cyan;
extern Color magenta;

extern Color gray;
extern Color lightgray;
extern Color darkgray;

} //namespace PD

#endif

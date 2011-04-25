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
#ifndef _PDRECT_H_
#define _PDRECT_H_

#include "PDPoint.h"
#include "PDSize.h"

namespace PD {

/**
 * \brief
 * \ingroup gui
 */
class Rect
{
private:
	int m_x1;
	int m_x2;
	int m_y1;
	int m_y2;

public:
	Rect();
	Rect(int x, int y, int w=0, int h=0);
	Rect(int x, int y, const Size& size);
	Rect(const Point& pt, int w=0, int h=0);
	Rect(const Point& pt, const Size& size);

	int x() const;
	int y() const;
	int width() const;
	int height() const;

	int left() const;
	int right() const;
	int top() const;
	int bottom() const;

	void setX(int x);
	void setY(int y);
	void setWidth(int w);
	void setHeight(int h);

	void setPosition(int x, int y);
	void setPosition(const Point& pt);
	void setSize(int w, int h);
	void setSize(const Size& size);

	void adjust(int dx, int dy, int dx2, int dy2);

	Rect normalized();

	bool intersect(const Rect& rect);

	bool contains(const Point& pt);
	bool contains(const int x, const int y);

	void print();

	Rect& operator=(const Rect& rect);
	int operator!=(const Rect& rect);
};

} //namespace PD {

#endif

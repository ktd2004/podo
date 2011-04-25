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
#include "PDRect.h"
#include <stdio.h>
#include <algorithm>

namespace PD {

Rect::Rect()
{
	m_x1 = m_x2 = m_y1 = m_y2 = 0;
}

Rect::Rect(int x, int y, int w, int h)
{
	m_x1 = m_x2 = m_y1 = m_y2 = 0;

	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
}

Rect::Rect(int x, int y, const Size& size)
{
	m_x1 = m_x2 = m_y1 = m_y2 = 0;

	setX(x);
	setY(y);
	setWidth(size.width());
	setHeight(size.height());
}

Rect::Rect(const Point& pt, int w, int h)
{   
	m_x1 = m_x2 = m_y1 = m_y2 = 0;

	setX(pt.x());
	setY(pt.y());
	setWidth(w);
	setHeight(h);
}

Rect::Rect(const Point& pt, const Size& size)
{   
	m_x1 = m_x2 = m_y1 = m_y2 = 0;

	setX(pt.x());
	setY(pt.y());
	setWidth(size.width());
	setHeight(size.height());
}



int Rect::x() const { return m_x1; }
int Rect::y() const { return m_y1; }
int Rect::width() const { return m_x2 - m_x1 + 1; }
int Rect::height() const { return m_y2 - m_y1 + 1; }

int Rect::left() const { return m_x1; }
int Rect::right() const { return m_x2; }
int Rect::top() const { return m_y1; }
int Rect::bottom() const { return m_y2; }

void Rect::setX(int x) { m_x1 = x; }
void Rect::setY(int y) { m_y1 = y; }
void Rect::setWidth(int w) { m_x2 = (m_x1 + w - 1); }
void Rect::setHeight(int h) { m_y2 = (m_y1 + h - 1); }

void Rect::setPosition(int x, int y) { m_x1 = x; m_y1 = y; }
void Rect::setPosition(const Point& pt) { m_x1 = pt.x(); m_y1 = pt.y(); }

void Rect::setSize(int w, int h) { setWidth(w); setHeight(h); }
void Rect::setSize(const Size& size) { setWidth(size.width()); setHeight(size.height()); }

void Rect::adjust(int dx, int dy, int dx2, int dy2)
{
	m_x1 += dx;	
	m_y1 += dy;	
	m_x2 += dx2;	
	m_y2 += dy2;	
}

Rect Rect::normalized()
{
	if (width() == 0 || height() == 0) return *this;

	Rect r;

	if (m_x2 < m_x1) 
	{
		r.m_x1 = m_x2;
		r.m_x2 = m_x1;
	} else 
	{
		r.m_x1 = m_x1;
		r.m_x2 = m_x2;
	}

	if (m_y2 < m_y1) 
	{
		r.m_y1 = m_y2;
		r.m_y2 = m_y1;
	} else 
	{
		r.m_y1 = m_y1;
		r.m_y2 = m_y2;
	}

	return r;

}

bool Rect::intersect(const Rect& rect)
{
#if 0
    Rect r1 = normalized();
    Rect r2 = rect.normalized();

	int x1 = std::max(r1.m_x1, r2.m_x1);
	int x2 = std::max(r1.m_x2, r2.m_x2);
	int y1 = std::max(r1.m_y1, r2.m_y1);
	int y2 = std::max(r1.m_y2, r2.m_y2);

	printf("x1:%d x2:%d y1:%d y2:%d\n", x1, x2, y1, y2);

    return (std::max(r1.m_x1, r2.m_x1) <= std::max(r1.m_x2, r2.m_x2) &&
             std::max(r1.m_y1, r2.m_y1) <= std::max(r1.m_y2, r2.m_y2));
#else
{
	Rect r1(x(), y(), width(), height());
	Rect r2(rect);	
	Rect r3;

	// horizontal
	int r1Min = r1.x();
	int r1Max = r1Min + r1.width();	

	int r2Min = r2.x();
	int r2Max = r2Min + r2.width();

	if (r2Min > r1Min) r1Min = r2Min;
	r3.setX(r1Min);

	if (r2Max < r1Max) r1Max = r2Max;
	r3.setWidth( r1Max - r1Min > 0 ? r1Max - r1Min : 0 );
	
	// vertical
	r1Min = r1.y();
	r1Max = r1Min + r1.height();

	r2Min = r2.y();
	r2Max = r2Min + r2.height();

	if (r2Min > r1Min) r1Min = r2Min;
	r3.setY(r1Min);

	if (r2Max < r1Max) r1Max = r2Max;
	r3.setHeight( r1Max - r1Min > 0 ? r1Max - r1Min : 0 );

    return (r3.width() && r3.height());
}
#endif
}

bool Rect::contains(const Point& pt)
{
	return contains(pt.x(), pt.y());
}

bool Rect::contains(const int x, const int y)
{
	Rect r = normalized();
	bool f = (x >= r.m_x1 && x <= r.m_x2 && y >= r.m_y1 && y <= r.m_y2);
	return f;
}

void Rect::print()
{
	printf("Rect::print() x:%d y:%d w:%d h:%d\n", x(), y(), width(), height());
}

Rect& Rect::operator=(const Rect& rect)
{
	m_x1 = rect.left();	
	m_y1 = rect.top();	
	m_x2 = rect.right();	
	m_y2 = rect.bottom();	

	return *this;
}

int Rect::operator!=(const Rect& rect)
{
	return (m_x1 != rect.m_x1 || m_x2 != rect.m_x2 ||
			m_y1 != rect.m_y1 || m_y2 != rect.m_y2);
}

} //namespace PD {

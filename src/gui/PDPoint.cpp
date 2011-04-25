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
#include "PDPoint.h"

namespace PD {

Point::Point()
{
	m_x = m_y = 0;
}

Point::Point(int x, int y)
{
	m_x = x;
	m_y = y;
}

Point::Point(const Point& pt)
{
	m_x = pt.x();
	m_y = pt.y();
}

int Point::x() const { return m_x; }
int Point::y() const { return m_y; }

void Point::setX(const int x) { m_x = x; }
void Point::setY(const int y) { m_y = y; }

Point& Point::operator=(const Point& pt)
{
	m_x = pt.x();
	m_y = pt.y();

	return *this;
}

int Point::operator==(const Point& pt)
{
	if(x() != pt.x()) return 0;
	if(y() != pt.y()) return 0;

	return 1;
}
int Point::operator!=(const Point& pt)
{
	return !(*this == pt);
}




} //namespace PD {

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
#ifndef _PDPOINT_H_
#define _PDPOINT_H_

namespace PD {

/**
 * \brief
 * \ingroup gui
 */
class Point
{
private:
	int m_x;
	int m_y;

public:
	Point();
	Point(int x, int y);
	Point(const Point& pt);

	int x() const;
	int y() const;

	void setX(const int x);
	void setY(const int y);

	Point& operator=(const Point& pt);
	int operator==(const Point& pt);
	int operator!=(const Point& pt);
};

} //namespace PD {

#endif

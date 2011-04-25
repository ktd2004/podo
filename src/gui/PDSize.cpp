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
#include "PDSize.h"

namespace PD {

Size::Size()
{
	m_width = m_height = 0;
}

Size::Size(int width, int height)
{
	m_width = width;
	m_height = height;
}

Size::Size(const Size& pt)
{
	m_width = pt.width();
	m_height = pt.height();
}

int Size::width() const { return m_width; }
int Size::height() const { return m_height; }

void Size::setWidth(const int width) { m_width = width; }
void Size::setHeight(const int height) { m_height = height; }

Size& Size::operator=(const Size& pt)
{
	m_width = pt.width();
	m_height = pt.height();

	return *this;
}

int Size::operator==(const Size& pt)
{
	if (width() != pt.width()) return 0;
	if (height() != pt.height()) return 0;

	return 1;
}
int Size::operator!=(const Size& pt)
{
	return !(*this == pt);
}




} //namespace PD {

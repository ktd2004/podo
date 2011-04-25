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
#ifndef _PDSIZE_H_
#define _PDSIZE_H_

namespace PD {

/**
 * \brief 
 * \ingroup gui
 */
class Size
{
private:
	int m_width;
	int m_height;

public:
	Size();
	Size(int w, int h);
	Size(const Size& pt);

	int width() const;
	int height() const;

	void setWidth(const int width);
	void setHeight(const int height);

	Size& operator=(const Size& pt);
	int operator==(const Size& pt);
	int operator!=(const Size& pt);
};

} //namespace PD {

#endif

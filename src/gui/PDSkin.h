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
#ifndef _PDSKIN_H_
#define _PDSKIN_H_

#include "PDWidget.h"

namespace PD
{

class SkinPrivate;

/**
 * \brief
 * \ingroup gui
 */
class Skin
{
	friend class SkinPrivate;

private:
	SkinPrivate* d;

public:
	Skin(Widget* parent);
	virtual ~Skin();
	
	void setParent(Widget* parent);
	int load(const char* fileName);
	Widget* control(std::string v);
	Image* image(std::string v);
	Palette* palette(std::string v);

protected:
	virtual void initCustom(std::string /*grp*/) {};
};

}

#endif

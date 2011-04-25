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
#ifndef _PDLABEL_H_
#define _PDLABEL_H_

#include "PDWidget.h"

namespace PD {

class LabelPrivate;

/**
 * \brief
 * \ingroup gui
 */
class Label : public Widget
{
private:
	LabelPrivate* d;

public:
						Label(Widget* parent, const char* name=0);
						Label(Widget* parent, const char* name, 
							const char* text);
						~Label();

	std::string			text();
	void				setText(const std::string& text);

	bool				border();
	void 				setBorder(bool f);

	int					alignment();
	void				setAlignment(int align);

	void				setMargin(unsigned int margin);
	unsigned int		margin();

protected:
	virtual void 		paintEvent(PaintEvent*);
};

} //namespace PD {

#endif

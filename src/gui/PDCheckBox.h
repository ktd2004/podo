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
#ifndef _PDCHECKBOX_H_
#define _PDCHECKBOX_H_

#include "PDWidget.h"
#include "PDPainter.h"

namespace PD {

class CheckBoxPrivate;

/**
 * \brief checkbox
 * \ingroup gui
 */
class CheckBox : public Widget
{
public:
	enum CheckStyle { CheckV =0, CheckRect };

private:
	CheckBoxPrivate* d;

public:
	CheckBox(Widget* parent, const char* name=0);
	~CheckBox();

	void setCheckFlag(bool flag);
	bool checkFlag();

	void setCheckStyle(CheckStyle s);

	void setText(const char* text);
	std::string text();

	sigslot::signal1<bool>	changeState;	
	sigslot::signal2<CheckBox*, bool>	changeStateWithWidget;	

protected:
	void paintEvent(PaintEvent*);
	bool keyReleaseEvent(KeyEvent* evt);
	void mouseReleaseEvent(MouseEvent* evt);
	bool focusInEvent(FocusInEvent*);
	bool focusOutEvent(FocusOutEvent*);
};

} //namespace PD {

#endif

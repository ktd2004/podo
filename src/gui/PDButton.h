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
#ifndef _PDBUTTON_H_
#define _PDBUTTON_H_

#include "PDWidget.h"

namespace PD {

class ButtonPrivate;

/**
 * \brief button
 * \ingroup gui
 */
class Button : public Widget
{
public:
	enum State { Normal=0, Hover, Disabled };

private:
	ButtonPrivate* d;
	
public:
						Button(Widget* parent, const char* name=0);
						Button(Widget* parent, const char* name, 
							const char* text);
						~Button();

	std::string 		text();
	void				setText(const std::string& text);

	void				setBackgroundLeft(const char* fn);
	void				setBackgroundRight(const char* fn);

	void				setFocusBg(const char* fn);
	void				setFocusBgLeft(const char* fn);
	void				setFocusBgRight(const char* fn);

	void				setHoverBg(const char* fn);
	void				setHoverBgLeft(const char* fn);
	void				setHoverBgRight(const char* fn);

	void				setDisabledBg(const char* fn);
	void				setDisabledBgLeft(const char* fn);
	void				setDisabledBgRight(const char* fn);

	void 				setAlignment(int align);

	bool				isToggleButton();
	void				setToggleButton(bool f);

	bool				isOn();
	void				setOn(bool f);

	int 				state();
	void 				setState(State stat);
	
	Image*				backgroundLeft();
	Image*				backgroundRight();

	Image*				hoverBg();
	Image*				disabledBg();
	Image*				focusBg();

	Image*				hoverBgLeft();
	Image*				disabledBgLeft();
	Image*				focusBgLeft();

	Image*				hoverBgRight();
	Image*				disabledBgRight();
	Image*				focusBgRight();

	int					alignment();

	sigslot::signal1<Button*>	clicked;	

protected:
	virtual void 		paintEvent(PaintEvent*);

	virtual void		mousePressEvent(MouseEvent* evt);
	virtual void		mouseReleaseEvent(MouseEvent* evt);

	virtual bool		keyPressEvent(KeyEvent* evt);
	virtual bool		keyReleaseEvent(KeyEvent* evt);

	virtual bool		focusInEvent(FocusInEvent*);
	virtual bool		focusOutEvent(FocusOutEvent*);

	virtual void		enterEvent();
	virtual void		leaveEvent();
};

} //namespace PD {

#endif

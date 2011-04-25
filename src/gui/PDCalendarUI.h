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
#ifndef _PDCALENDARUI_H_
#define _PDCALENDARUI_H_

#include "PDWidget.h"
#include "../base/PDCalendar.h"
#include "PDPainter.h"

namespace PD {

class CalendarUIPrivate;

/**
 * \brief calendar ui
 * \ingroup gui
 */
class CalendarUI : public Widget
{
public:
	enum FocusOutKeyType
	{
		Up = 0,
		Down,
		Left,
		Right
	};

private:
	CalendarUIPrivate* d;
	
public:
	CalendarUI(Widget* parent, const char* name=0);
	~CalendarUI();

	Calendar& calendar();

	int selectedDay();
	void setSelectedDay(int d);

	int titleHeight();
	void setTitleHeight(int h);

	int year();
	int month();

	void setDate(int year, int month);

	void currentMonth();
	void nextMonth();
	void previousMonth(); 

	void nextYear();
	void previousYear();

	sigslot::signal1<int> clicked;
	sigslot::signal1<FocusOutKeyType> focusOut;

protected:
	virtual void clickedSignal();

	virtual void updateItem(int row, int col, bool selected=false);
	virtual void drawSelectedItem();

	virtual void drawTitle(Painter& p);
	virtual void drawItem(Painter& p, int row, int col, bool selected=false);
	virtual void paintEvent(PaintEvent*);

	virtual bool focusInEvent(FocusInEvent*); 
	virtual bool focusOutEvent(FocusOutEvent*); 

	virtual void mouseReleaseEvent(MouseEvent* evt);

	virtual bool keyReleaseEvent(KeyEvent* evt);
	int selectedDay(int x, int y);
};

} //namespace PD {

#endif

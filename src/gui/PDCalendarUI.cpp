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
#include "PDCalendarUI.h"
#include "PDCalendarUI_p.hpp"
#include "../base/PDDateTime.h"
#include "../base/PDString.h"
#include "PDApp.h"

namespace PD {

CalendarUI::CalendarUI(Widget* parent, const char* name/*=0*/) : 
	Widget(parent, name, 0, Theme::CalendarUI)
{
	d = new CalendarUIPrivate;
	d->initialize();

	palette().setColor(Palette::Background, white);
}

CalendarUI::~CalendarUI()
{
	delete d;
}

Calendar& CalendarUI::calendar() { return d->cal; }

int CalendarUI::selectedDay() { return d->selectedDay; }
void CalendarUI::setSelectedDay(int day) { d->selectedDay = day; }

int CalendarUI::titleHeight() { return d->titleHeight; }
void CalendarUI::setTitleHeight(int h) { d->titleHeight = h ; }



bool CalendarUI::focusInEvent(FocusInEvent*)
{
	//printf("CalendarUI::focusInEvent name:%s\n", name());
	//printf("CalendarUI::focusInEvent name:%s isVisible:%d\n", 
	//	name(), isVisible());
	
	if (isVisible())
	{
		if(d->selectedDay == -1) d->selectedDay = 1;

		for (int row=0; row<6; row++)
		{
			for (int col=0; col<7; col++)
			{
				int idx = row * 7 + col;
				if (d->selectedDay == d->cal.day(idx).value())
				{
					if (d->row == -1 && d->col == -1)
					{
						d->row = row;
						d->col = col;
						updateItem(row, col, true);
					}

					return true;
				}
			}
		}
	}

	return true;
}

bool CalendarUI::focusOutEvent(FocusOutEvent*)
{
	//printf("CalendarUI::focusOutEvent name:%s\n", name());
	d->selectedDay = -1;

	if (isVisible()) updateItem(d->row, d->col);

	d->row = -1;
	d->col = -1;

	return true;
}

void CalendarUI::drawTitle(Painter& p)
{
	const char* weekStr[] =
	{
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};

	p.setBrushColor(palette().color(Palette::Background));
	p.fillRect(0, 0, width(), titleHeight(),
				 palette().color(Palette::Background) );

	p.setPenColor( palette().color(Palette::Text) );

	int w = width() / 7;
	int marginX = 1;
	int marginY = 1;

	int x = marginX;
	int y = marginY;
	for (int i=0; i<7; i++)
	{
		Rect r(x, y, w, titleHeight());
		p.drawText(r, PD_TR("Common",weekStr[i]).c_str());
		x += w;
	}
}

void CalendarUI::drawItem(Painter& p, int row, int col, bool selected/*=false*/)
{
	int idx = row * 7 + col;
	if (idx > PD::Calendar::CalendarSize) return;

	int w = width() / 7;
	int h = (height()-titleHeight()) / 6;
	int x = col * w;
	int y = titleHeight() + row * h;

	//printf("CalendarUI::drawItem x:%d y:%d w:%d h:%d\n", x, y, w, h);

	// erase
	p.fillRect(x, y, w, h, palette().color(Palette::Background));

	p.setPenColor(palette().color(Palette::Text));
	//p.drawRect(x, y, x+w, y+h);
	//p.drawRect(x+1, y+1, x+w-1, y+h-1);

	if (!d->cal.day(idx).valid()) 
	{
		return;
	}

	//printf("CalendarUI::drawItem idx:%d row:%d col:%d\n",
	//	idx, row, col);

	std::string text;
	text = String::format("%2d", d->cal.day(idx).value());

	if (selected)
	{
		//printf("draw idx:%d d->selectedDay:%d x:%d y:%d w:%d h:%d\n", 
		//	idx, d->selectedDay, x, y, w, h);
		p.setPenColor( palette().color(PD::Palette::FocusColor) );
		p.fillRect(x, y, w, h);
		p.drawRect(x+1, y+1, x+w-2, y+h-2);
	}


	// current day
	if (col == 0) p.setPenColor(red); // sunday
	else if (col == 6) p.setPenColor(blue); // saturday
	else p.setPenColor(black);

	if ( d->cal.year() == d->cal.currentYear() &&
		d->cal.month() == d->cal.currentMonth() &&
			d->cal.day(idx).value() == d->cal.currentDay())
		p.setPenColor(green);

	Rect r(x, y, w, h);

	p.drawText(r, text.c_str());
}

void CalendarUI::paintEvent(PaintEvent*)
{
	//printf("CalendarUI::paintEvent name:%s\n", name());
	Painter p(this);

	drawTitle(p);

	for (int row=0; row<6; row++)
	{
		for (int col=0; col<7; col++)
		{
			int idx = row * 7 + col;
			bool selected = (d->selectedDay == d->cal.day(idx).value()); 
			#if 0
			if(selected)
			{
				d->row = row;
				d->col = col;
			}
			#endif
			drawItem(p, row, col, selected);
		}
	}
}

int CalendarUI::selectedDay(int x, int y)
{
	if (y <= titleHeight()) return -1;

	y -= titleHeight();
	Point globalPt(x, y);
	Point localPt = mapFromGlobal(globalPt);
	//printf("CalendarUI::selectedDay cell local x:%d y:%d\n", 
	//	localPt.x(), localPt.y());

	int day = -1;

	int w = width() / 7;
	int h = (height()-titleHeight()) / 6;
	//printf("CalendarUI::selectedDay total(w:%d h:%d) cell(w:%d h:%d)\n", 
	//	width(), height(), w, h);

	int row = localPt.y() / h;
	if (localPt.y() % h) row++;
	row--;

	int col = localPt.x() / w;
	if (localPt.x() % w) col++;
	col--;

	int idx = row * 7 + col;

	if (idx < 0 || idx > PD::Calendar::CalendarSize) 
	{
		return day;
	}

	if (d->cal.day(idx).valid())
	{
		day = d->cal.day(idx).value();	

		d->row = row;
		d->col = col;
		//printf("CalendarUI::selectedDay cell row:%d col:%d day:%d\n", 
		//	row, col, day);
	}

	return day;
}

void CalendarUI::drawSelectedItem()
{
	if (d->row == -1 || d->col == -1) return;

	//printf("CalendarUI::drawSelectedItem\n");	
	updateItem(d->row, d->col, true);
}

void CalendarUI::updateItem(int row, int col, bool selected/*=false*/)
{
	PD::Painter p(this);

	int w = width() / 7;
	int h = (height()-titleHeight()) / 6;

	if (row == -1 || col == -1) return;

	//printf("CalendarUI::updateItem row:%d col:%d, selected:%d\n",
	//	row, col, selected);
	int newX = col * w;
	int newY = titleHeight() + row * h;
	drawItem(p, row, col, selected);
	Rect newRect(newX, newY, w, h);
	update(newRect);
}

void CalendarUI::mouseReleaseEvent(MouseEvent* evt)
{
	//printf("CalendarUI::mouseReleaseEvent button:%d x:%d y:%d\n",
	//	evt->button(), evt->x(), evt->y());
	//printf("d->row:%d d->col:%d\n", d->row, d->col);

	if (evt->button() != MouseEvent::Left) return;

	// erase old
	updateItem(d->row, d->col);

	int day = selectedDay(evt->x(), evt->y());
	if (day == -1) 
	{
		updateItem(d->row, d->col);
		return;
	}

	setFocus();
	d->selectedDay = day;	

	// draw new
	updateItem(d->row, d->col, true);

	clickedSignal();
}

void CalendarUI::clickedSignal()
{
	clicked.emit(d->selectedDay);
}

bool CalendarUI::keyReleaseEvent(KeyEvent* evt)
{
	int key = evt->key();
	//printf("CalendarUI::keyReleaseEvent key:%d\n", evt->key());

	if (d->selectedDay == -1) return false;

	int oldRow = d->row;
	int oldCol = d->col;

	if (key == SDLK_LEFT)
	{
		if (d->selectedDay-1 <= 0) 
		{
			if (keyMover().left()) keyMover().left()->setFocus();
			else focusOut.emit(Left);
			return true;
		}

		d->selectedDay--;
		d->col--;
		if (d->col < 0) { d->col = 6; d->row--; }
	}
	else if (key == SDLK_RIGHT)
	{
		DateTime dateTime(year(), month(), 1, 0, 0, 0);
		if (d->selectedDay+1 > dateTime.daysInMonth()) 
		{
			if (keyMover().right()) keyMover().right()->setFocus();
			else focusOut.emit(Right);
			return true;
		}

		d->selectedDay++;
		d->col++;
		if (d->col > 6) { d->col = 0; d->row++; }
	}
	else if (key == SDLK_UP)
	{
		if (d->selectedDay-7 <= 0) 
		{
			if (keyMover().up()) keyMover().up()->setFocus();
			else focusOut.emit(Up);
			return true;
		}

		d->selectedDay -= 7;
		d->row--;
		if (d->row < 0) d->row = 0;
	}
	else if (key == SDLK_DOWN)
	{
		DateTime dateTime(year(), month(), 1, 0, 0, 0);
		if (d->selectedDay+7 > dateTime.daysInMonth())
		{
			if (keyMover().down()) keyMover().down()->setFocus();
			else focusOut.emit(Down);
			return true;
		}

		d->selectedDay += 7;
		d->row++;
		if (d->row > 5) d->row = 5;
	}
	else if (key == SDLK_RETURN)
	{
		clickedSignal();
		return true;
	}
	else if(key == SDLK_ESCAPE)
	{
		return false;
	}

	//printf("CalendarUI::keyReleaseEvent d->selecteDay:%d\n", d->selectedDay);

	updateItem(oldRow, oldCol);
	updateItem(d->row, d->col, true);

	return true;
}

int CalendarUI::year()
{
	return d->cal.year();
}

int CalendarUI::month()
{
	return d->cal.month();
}

void CalendarUI::setDate(int year, int month)
{
	d->cal.calendar(year, month);
	d->initialize();
}

void CalendarUI::nextMonth()
{	
	d->cal.nextMonth();
	d->initialize();
}

void CalendarUI::previousMonth()
{
	d->cal.previousMonth();
	d->initialize();
}

void CalendarUI::nextYear()
{
	d->cal.nextYear();
	d->initialize();
}

void CalendarUI::previousYear()
{
	d->cal.previousYear();
	d->initialize();
}

void CalendarUI::currentMonth()
{
	d->cal.currentMonth();
	d->initialize();
}

} //namespace PD {

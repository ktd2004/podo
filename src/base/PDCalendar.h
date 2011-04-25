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
#ifndef _PDCALENDAR_H_
#define _PDCALENDAR_H_

#include <stdio.h>

namespace PD {

/**
 * \brief 
 * \ingroup base
 */
class CalendarDayValue
{
private:
	bool m_valid;
	int m_dayValue;

public:
	void setValid(bool v) { m_valid = v; };
	bool valid() { return m_valid; };

	void setValue(int v) { m_dayValue = v; };
	int value() { return m_dayValue; };
};

class CalendarPrivate;

/**
 * \defgroup base
 */

/**
 * \brief 
 * \ingroup base
 */
class Calendar
{
public:
	enum {
		January = 1,
		December = 12,
		CalendarSize = 42,
		StartYear = 1970,
		EndYear = 2030
	};
	
private:
	CalendarPrivate* d;

public:
	Calendar();
	~Calendar();

	CalendarDayValue& day(int d);

	int year();
	int month();

	int currentYear();
	int currentMonth();
	int currentDay();

	void todayMonth();
	void nextMonth();
	void previousMonth();

	void nextYear();
	void previousYear();
	
	void calendar(int year, int month);
	void print();
};

}
#endif


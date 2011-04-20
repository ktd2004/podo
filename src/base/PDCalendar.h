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


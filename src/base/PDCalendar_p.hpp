#ifndef _PDCALENDAR_P_H_
#define _PDCALENDAR_P_H_

#include "PDDateTime.h"

namespace PD {

class CalendarPrivate
{
public:
	CalendarDayValue day[Calendar::CalendarSize];
	DateTime dateTime;
	int curYear;
	int curMonth;
	int curDay;
	int tempYear;
	int tempMonth;

	CalendarPrivate()
	{
		curYear = dateTime.year();
		curMonth = dateTime.month();
		curDay = dateTime.day();
		tempMonth = 0; 
		tempYear = 0;
	}
};

} //namespace PD {
#endif

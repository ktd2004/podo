#ifndef _PDCALENDARUI_P_H_
#define _PDCALENDARUI_P_H_

namespace PD {

class CalendarUIPrivate
{
public:
	int selectedDay;
	int row;
	int col;

	int titleHeight;
	Calendar cal;

public:
	CalendarUIPrivate()
	{
		titleHeight = 25;
	}

	void initialize()
	{
		selectedDay = -1;
		row = -1;
		col = -1;
	}
};
} //namespace PD {

#endif

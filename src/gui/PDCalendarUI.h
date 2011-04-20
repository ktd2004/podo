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

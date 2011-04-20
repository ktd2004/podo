#ifndef _INDICATOR_H_
#define _INDICATOR_H_

#include <gui/PDWidget.h>

class Indicator : public PD::Widget
{
private:
	PD::Image* m_bgImg;

	PD::Image* m_signalImg;
	PD::Image* m_batteryImg;

public:	
	Indicator(Widget* parent);
	~Indicator();

protected:
	void paintEvent(PD::PaintEvent*);
};

#endif //#define _INDICATOR_H_

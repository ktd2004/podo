#ifndef _IDLE_H_
#define _IDLE_H_

#include <gui/PDWidget.h>
#include <gui/PDTimer.h>

class Idle : public PD::Widget
{
private:
	PD::Timer m_timer;

public:	
	Idle(Widget* parent);
	~Idle();

protected:
	void paintEvent(PD::PaintEvent*);

	bool keyPressEvent(PD::KeyEvent* key);

private:
	void timeout();
};

#endif //#define _IDLE_H_

#ifndef _MAINFRM_H_
#define _MAINFRM_H_

#include <gui/PDWidget.h>
#include "Indicator.h"
#include "Idle.h"

class MainFrm : public PD::Widget
{
private:
	Indicator* m_indicator;
	Idle* m_idle;

public:
	MainFrm(PD::Widget* parent);
	~MainFrm();

protected:
	bool keyPressDownEvent(int key);
};

#endif //#define _MAINFRM_H_

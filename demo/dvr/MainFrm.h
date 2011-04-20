#ifndef _MAINFRM_H_
#define _MAINFRM_H_

#include <gui/PDWidget.h>
#include "Screen.h"
#include "StatusBar.h"

class MainFrm : public PD::Widget
{
private:
	Screen* m_screen;
	StatusBar* m_statusBar;

public:
	MainFrm(PD::Widget* parent);
	~MainFrm();

protected:
	void showEvent();
	bool keyPressEvent(PD::KeyEvent* evt);

private:
	void clickedMenu(PD::Button*);
	void clickedLayout1x1(PD::Button*);
	void clickedLayout2x2(PD::Button*);
	void clickedLayout3x3(PD::Button*);
	void clickedLayout4x4(PD::Button*);
};

#endif //#define _MAINFRM_H_

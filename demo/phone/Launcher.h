#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_

#include <gui/PDWidget.h>

class Launcher : public PD::Widget
{
private:
	PD::Image* m_bgImg;

public:	
	Launcher(Widget* parent);
	~Launcher();
};

#endif //#define _LAUNCHER_H_

#include "MainFrm.h"

MainFrm::MainFrm(Widget* parent) : Widget(parent) 
{
	m_indicator = new Indicator(this);
	m_indicator->setGeometry(0, 0, 176, 24);
	m_indicator->show();

	m_idle = new Idle(this);
	m_idle->setGeometry(0, 24, 176, 196);
	m_idle->show();
}

MainFrm::~MainFrm()
{
	if (m_indicator) delete m_indicator;
	if (m_idle) delete m_idle;
}

bool MainFrm::keyPressDownEvent(int key)
{
	if (key == SDLK_m)
	{
		printf("MainFrm::keyPressDownEvent 'M'\n"); fflush(stdout);
		return true;	
	}

	return false;
}

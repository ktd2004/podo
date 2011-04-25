/* 
   Copyright 2011 PODO. 
   This file is part of PODO. 
   
   PODO is free software: you can redistribute it and/or modify 
   it under the terms of the GNU Lesser General Public License as  
   published by the Free Software Foundation, either version 3 of  
   the License, or (at your option) any later version. 
   
   PODO is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of 
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU Lesser General Public License for more details. 
   
   You should have received a copy of the GNU Lesser General Public  
   License along with PODO. If not, see <http://www.gnu.org/licenses/>. 
 */
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

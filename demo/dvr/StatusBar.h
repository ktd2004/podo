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
#ifndef _STATUSBAR_H_
#define _STATUSBAR_H_

#include <gui/PDWidget.h>
#include <gui/PDButton.h>
#include <gui/PDLabel.h>
#include <gui/PDTimer.h>

class StatusBar : public PD::Widget
{
private:
	PD::Button* m_menuBtn;

	PD::Button* m_layout1x1Btn;
	PD::Button* m_layout2x2Btn;
	PD::Button* m_layout3x3Btn;
	PD::Button* m_layout4x4Btn;

	PD::Label* m_timeLabel;

	PD::Timer* m_timer;

public:
	StatusBar(PD::Widget* parent);
	~StatusBar();

	PD::Button* menuBtn() { return m_menuBtn; }

	PD::Button* layout1x1Btn() { return m_layout1x1Btn; }
	PD::Button* layout2x2Btn() { return m_layout2x2Btn; }
	PD::Button* layout3x3Btn() { return m_layout3x3Btn; }
	PD::Button* layout4x4Btn() { return m_layout4x4Btn; }

private:
	void timeout();
};

#endif

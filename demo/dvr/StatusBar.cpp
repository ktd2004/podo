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
#include "StatusBar.h"
#include <base/PDDateTime.h>
#include <base/PDString.h>

StatusBar::StatusBar(PD::Widget* parent) : PD::Widget(parent, "StatusBar")
{
	palette().setColor(PD::Palette::Background, PD::Color(16, 16, 104));

	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	int wMargin = 10;

	x = 5; y = 5; w = 115; h = 30;
	m_menuBtn = new PD::Button(this, "MenuBtn");
	m_menuBtn->setBackground("./images/menu_n.png");
	m_menuBtn->setHoverBg("./images/menu_s.png");
	m_menuBtn->setGeometry(x, y, w, h);
	m_menuBtn->show();
	x += w+wMargin;


	x += 40;
	w = 40;
	m_layout1x1Btn = new PD::Button(this, "Layout1x1Btn", "1x1");
	m_layout1x1Btn->setGeometry(x, y, w, h);
	m_layout1x1Btn->show();
	x += w+wMargin;

	m_layout2x2Btn = new PD::Button(this, "Layout2x2Btn", "2x2");
	m_layout2x2Btn->setGeometry(x, y, w, h);
	m_layout2x2Btn->show();
	x += w+wMargin;
	
	m_layout3x3Btn = new PD::Button(this, "Layout3x3Btn", "3x3");
	m_layout3x3Btn->setGeometry(x, y, w, h);
	m_layout3x3Btn->show();
	x += w+wMargin;

	m_layout4x4Btn = new PD::Button(this, "Layout4x4Btn", "4x4");
	m_layout4x4Btn->setGeometry(x, y, w, h);
	m_layout4x4Btn->show();
	x += w+wMargin;

	x += 60;
	y = 10;
	w = 160;
	m_timeLabel = new PD::Label(this, "TimeLabelBtn");
	m_timeLabel->palette().setColor(
		PD::Palette::Background, palette().color(PD::Palette::Background) );
	m_timeLabel->palette().setColor(
		PD::Palette::Text, PD::white);
	m_timeLabel->setGeometry(x, y, w, h);
	m_timeLabel->show();

	m_timer = new PD::Timer;
	m_timer->timeout.connect(this, &StatusBar::timeout);
	timeout();
	m_timer->start(1000);
}

StatusBar::~StatusBar()
{
	if (m_timer) { m_timer->stop(); delete m_timer; }

	if (m_menuBtn) delete m_menuBtn;

	if (m_layout1x1Btn) delete m_layout1x1Btn;
	if (m_layout2x2Btn) delete m_layout2x2Btn;
	if (m_layout3x3Btn) delete m_layout3x3Btn;
	if (m_layout4x4Btn) delete m_layout4x4Btn;
}

void StatusBar::timeout()
{
	PD::DateTime current;
	std::string text = PD::String::format("%04d-%02d-%02d %02d:%02d:%02d",
		current.year(), current.month(), current.day(),
		current.hour(), current.minute(), current.second());
	m_timeLabel->setText(text);
	m_timeLabel->repaint();
}

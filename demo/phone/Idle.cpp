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
#include "Idle.h"
#include <gui/PDApp.h>
#include <gui/PDPainter.h>
#include <base/PDDateTime.h>
#include <base/PDString.h>

Idle::Idle(Widget* parent) : Widget(parent) 
{
	setBackground("./images/bg.png");

	m_timer.timeout.connect(this, &Idle::timeout);
	m_timer.start(1000);
}

Idle::~Idle()
{
}

void Idle::timeout()
{
	repaint();
}

void Idle::paintEvent(PD::PaintEvent*)
{
	PD::Painter p(this);

	PD::DateTime dateTime;
	std::string text = PD::String::format("%02d:%02d:%02d",
		dateTime.hour(), dateTime.minute(), dateTime.second());
	p.setPenColor(PD::white);
	p.drawText(100, 20, text.c_str());

	p.fillRect(0, 170, width(), height()-170, PD::white);
	p.setPenColor(PD::black);
	p.drawText(10, 175, "Menu");

	p.drawText(140, 175, "Tel");
}

bool Idle::keyPressEvent(PD::KeyEvent* key)
{
	// TOOD:	
	//printf("Idle::keyPressEvent\n");
	return true;
}

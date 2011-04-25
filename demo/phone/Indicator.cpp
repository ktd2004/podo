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
#include "Indicator.h"
#include <gui/PDPainter.h>

Indicator::Indicator(Widget* parent) : Widget(parent) 
{
	m_bgImg = new PD::Image("./images/indicator_bg.png");

	m_signalImg = new PD::Image("./images/signal.png");
	m_batteryImg = new PD::Image("./images/battery.png");
}

Indicator::~Indicator()
{
	if (m_bgImg) delete m_bgImg;

	if (m_signalImg) delete m_signalImg;
	if (m_batteryImg) delete m_batteryImg;
}

void Indicator::paintEvent(PD::PaintEvent*)
{
	PD::Painter p(this);

	p.fillRect(0, 0, width(), height(), PD::black);

	int x = 0;
	int y = 2;
	int w = 21;
	int wMargin = 5;

	p.drawImage(x, y, *m_bgImg);

	p.drawImage(x, y, *m_signalImg); x += w + wMargin;

	p.setPenColor(PD::white);
	p.drawText(x+10, y+3, "PODO");

	p.drawImage(x+110, y, *m_batteryImg);
}


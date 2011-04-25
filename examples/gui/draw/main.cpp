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
#include <gui/PDApp.h>
#include <gui/PDWidget.h>
#include <gui/PDPainter.h>

class MainFrm : public PD::Widget
{
public:	
	MainFrm() : Widget() 
	{
	}

protected:
	void paintEvent(PD::PaintEvent*)
	{
		PD::Painter p(this);
		p.fillRect(0, 0, width(), height());
		p.drawRect(0, 0, width(), height());
		p.drawHLine(10, 10, width()-10, 10);
		p.drawVLine(10, 15, 10, height()-30);
		p.drawRect(5, 5, width()-5, height()-5);
	}

protected:
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(400, 200);

	MainFrm m;
	m.setGeometry(0, 0, 400, 200);
	m.show();

	return app.exec();
}

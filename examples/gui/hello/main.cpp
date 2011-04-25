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

class hello : public PD::Widget
{
public:

public:	
	hello(Widget* parent) : Widget(parent) 
	{
	}

protected:
	void paintEvent(PD::PaintEvent*)
	{
		PD::Painter p(this);
		p.fillRect(0, 0, width(), height(), PD::blue );
		p.fillRect(10, 10, 280, 60);

		p.drawText(10, 10, "Hello PODO");
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(300, 80);

	hello h(NULL);
	h.setGeometry(0, 0, 300, 80);
	h.show();

	return app.exec();
}

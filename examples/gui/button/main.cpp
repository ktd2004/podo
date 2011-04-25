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
#include <gui/PDButton.h>
#include <gui/PDPainter.h>


class MainFrm : public PD::Widget
{
private:
	PD::Button* m_button1;
	PD::Button* m_button2;
	PD::Button* m_button3;
	PD::Button* m_button4;
	PD::Button* m_button5;
	PD::Button* m_button6;

public:	
	MainFrm(Widget* parent, const char* name, 
		Uint32 style=PD::Style_NoTitle) : Widget(parent, name, style) 
	{
		palette().setColor(PD::Palette::Background, PD::blue);

		int x = 20;
		int y = 10;
		int w = 212;
		int h = 46;
		int hMargin = 10;

		m_button1 = new PD::Button(this, "Btn1", "Btn1");
		m_button1->clicked.connect(this, &MainFrm::button1Clicked);
		m_button1->setGeometry(x,y,w,h);
		m_button1->show();

		y += hMargin + h;
		m_button2 = new PD::Button(this, "Btn2", "Btn2");
		m_button2->setGeometry(x,y,w,h);
		m_button2->show();

		y += hMargin + h;
		m_button3 = new PD::Button(this, "Btn4 Show/Hide", "Btn3ShowHide");
		m_button3->clicked.connect(this, &MainFrm::button3Clicked);
		m_button3->setGeometry(x,y,w,h);
		m_button3->show();

		y += hMargin + h;
		m_button4 = new PD::Button(this, "Btn4", "Btn4");
		m_button4->setGeometry(x,y,w,h);
		m_button4->show();

		y += hMargin + h;
		m_button5 = new PD::Button(this, "Toggle", "Toggle");
		m_button5->setToggleButton(true);
		m_button5->setGeometry(x,y,w,h);
		m_button5->show();

		y += hMargin + h;
		m_button6 = new PD::Button(this, "Image");
		m_button6->setBackground("./images/normal.png");
		m_button6->setHoverBg("./images/press.png");
		m_button6->setGeometry(x,y,w,h);
		m_button6->show();

	}
	~MainFrm()
	{
		if (m_button1) delete m_button1;
		if (m_button2) delete m_button2;
		if (m_button3) delete m_button3;
		if (m_button4) delete m_button4;
		if (m_button5) delete m_button5;
	}


protected:
	void button1Clicked(PD::Button*)
	{
		printf("MainFrm::button1Clicked\n");
	}

	void button3Clicked(PD::Button*)
	{
		if (m_button4->isVisible()) m_button4->hide();
		else m_button4->show();
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(250, 350);

	MainFrm m(NULL, "MainFrm");
	m.setGeometry(0, 0, 250, 350);
	m.show();

	return app.exec();
}

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
#include <gui/PDLabel.h>
#include <gui/PDPainter.h>

class MainFrm : public PD::Widget
{
private:
	PD::Label* m_label1;
	PD::Label* m_label2;
	PD::Label* m_label3;

public:	
	MainFrm(Widget* parent) : Widget(parent) 
	{
		//palette().setColor(PD::Palette::Background, PD::green);

		m_label1 = new PD::Label(this, "Label1", "Label1-FillBg");
		m_label1->palette().setColor(PD::Palette::Text, PD::white);
		m_label1->palette().setColor(PD::Palette::Background, PD::blue);
		m_label1->setAlignment(PD::AlignRight);
		m_label1->setGeometry(10,10,280,30);
		m_label1->show();

		m_label2 = new PD::Label(this, "Label2", "Label2-NoBg");
		m_label2->palette().setColor(PD::Palette::Text, PD::white);
		m_label2->palette().setColor(PD::Palette::Background, PD::blue);
		m_label2->setAlignment( PD::AlignLeft);
		m_label2->setBgMode(PD::NoBg);
		m_label2->setGeometry(10,50,280,30);
		m_label2->show();

		m_label3 = new PD::Label(this, "Label3", "Label-ParentBg-1");
		m_label3->setAlignment(PD::AlignCenter);
		m_label3->setBgMode(PD::ParentBg);
		m_label3->setGeometry(10,90,280,30);
		m_label3->show();

	}	
	~MainFrm()
	{
		delete m_label1;
		delete m_label2;
		delete m_label3;
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(400, 300);

	MainFrm m(NULL);
	m.setGeometry(0, 0, 400, 300);
	m.show();

	return app.exec();
}

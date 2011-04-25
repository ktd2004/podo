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
#include <gui/PDCheckBox.h>
#include <gui/PDPainter.h>

class MainFrm : public PD::Widget
{
private:
	PD::CheckBox* m_checkBox1;
	PD::CheckBox* m_checkBox2;
	PD::CheckBox* m_checkBox3;
	PD::CheckBox* m_checkBox4;

public:	
	MainFrm(Widget* parent, const char* name) : Widget(parent, name, PD::Style_NoTitle) 
	{
		m_checkBox1 = new PD::CheckBox(this, "CheckBox");
		m_checkBox1->setGeometry(10, 10, 220, 25);
		m_checkBox1->setCheckFlag(true);
		m_checkBox1->setText("CheckBox1(V)");
		m_checkBox1->show();

		m_checkBox2 = new PD::CheckBox(this, "CheckBox2");
		m_checkBox2->setGeometry(10, 50, 220, 25);
		m_checkBox2->setCheckFlag(true);
		m_checkBox2->setText("CheckBox2(Rect)");
		m_checkBox2->setCheckStyle(PD::CheckBox::CheckRect);
		m_checkBox2->show();
		
		m_checkBox3 = new PD::CheckBox(this, "CheckBox3");
		m_checkBox3->setGeometry(10, 90, 220, 25);
		m_checkBox3->setCheckFlag(true);
		m_checkBox3->setText("CheckBox3");
		m_checkBox3->show();

		m_checkBox4 = new PD::CheckBox(this, "CheckBox4");
		m_checkBox4->setGeometry(10, 130, 220, 25);
		m_checkBox4->setCheckFlag(true);
		m_checkBox4->setText("CheckBox4");
		m_checkBox4->show();


		m_checkBox1->setFocus();
		m_checkBox1->keyMover().setDown(m_checkBox2);

		m_checkBox2->keyMover().setUp(m_checkBox1);

		m_checkBox2->keyMover().setDown(m_checkBox3);
		m_checkBox3->keyMover().setUp(m_checkBox2);

		m_checkBox3->keyMover().setDown(m_checkBox4);
		m_checkBox4->keyMover().setUp(m_checkBox3);

	}	
	~MainFrm()
	{
		delete m_checkBox1;
		delete m_checkBox2;
		delete m_checkBox3;
		delete m_checkBox4;
	}

};


int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(400, 300);

	MainFrm m(NULL, "MainFrm");
	m.setGeometry(0, 0, 400, 300);
	m.show();

	return app.exec();
}



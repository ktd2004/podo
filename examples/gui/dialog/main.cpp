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
#include <gui/PDButton.h>
#include <base/PDString.h>
#include <gui/PDTimer.h>

class DialogSubFrm :  public PD::Widget
{
private:
	PD::Button* m_button;

public:

	DialogSubFrm(Widget* parent) : Widget(parent, "DialogSubFrm")
	{
		palette().setColor(PD::Palette::Background, PD::green);

		m_button = new PD::Button(this, "CloseBtn", "Close");
		m_button->setGeometry(200, 50, 80, 30);
		m_button->clicked.connect(this, &DialogSubFrm::clicked);
		m_button->show();
	}

	void clicked(PD::Button* /*w*/)
	{
		close();
	}
	~DialogSubFrm()
	{
		delete m_button;
	}
};


class DialogFrm :  public PD::Widget
{
private:
	PD::Button* m_newDlgBtn;
	PD::Button* m_button;

public:

	DialogFrm(Widget* parent) : Widget(parent, "DialogFrm")
	{
		palette().setColor(PD::Palette::Background, PD::blue);
		m_newDlgBtn = new PD::Button(this, "OkBtn", "OK");
		m_newDlgBtn->setGeometry(200, 150, 80, 30);
		m_newDlgBtn->clicked.connect(this, &DialogFrm::newDlg);
		m_newDlgBtn->show();

		m_button = new PD::Button(this, "CancelBtn", "Cancel");
		m_button->setGeometry(300, 150, 80, 30);
		m_button->clicked.connect(this, &DialogFrm::clicked);
		m_button->show();
	}

	void newDlg(PD::Button* /*w*/)
	{
		DialogSubFrm frm(this);
		frm.setGeometry(10, 10, 300, 100);
		frm.exec();
	}

	void clicked(PD::Button* /*w*/)
	{
		printf("DialogFrm::clicked!!\n");
		close();
	}
	~DialogFrm()
	{
		delete m_newDlgBtn;
		delete m_button;
	}
};

class MainFrm : public PD::Widget
{
public:

private:
	PD::Button* m_btn1;

public:	
	MainFrm(Widget* parent) : Widget(parent, "MainFrm") 
	{
		m_btn1 = new PD::Button(this, "Btn1", "Show Dialog");
		m_btn1->clicked.connect(this, &MainFrm::clickedBtn1);
		m_btn1->show();
	}

	~MainFrm()
	{
		if (m_btn1) delete m_btn1;
	}

protected:
	void showEvent()
	{
		m_btn1->setGeometry(10, 10, 100, 30);
		m_btn1->show();
	}

	void clickedBtn1(PD::Button* /*w*/)
	{
		DialogFrm dialog(this);
		dialog.setGeometry(20, 20, 400, 200);
		dialog.exec();
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(500, 300);

	MainFrm mainFrm(NULL);
	mainFrm.setGeometry(0, 0, 500, 300);
	mainFrm.show();

	return app.exec();
}

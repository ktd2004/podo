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
#include <gui/PDLabel.h>
#include <gui/PDPainter.h>

class MainFrm : public PD::Widget
{
private:
	PD::Label* m_label;
	PD::Button* m_button[20];

public:	
	MainFrm(Widget* parent, const char* name, 
		Uint32 style=PD::Style_NoTitle) : Widget(parent, name, style) 
	{
		m_label = new PD::Label(this);
		m_label->show();

		const char* calcLabel[] =
		{
			"Bksp", "CE", "Clr", "+-",
			"7", "8", "9", "/",
			"4", "5", "6", "X",
			"1", "2", "3", "-",
			"0", ".", "=", "+"
		};
		for (int i=0; i<20; i++)
		{
			m_button[i] = new PD::Button(this, calcLabel[i]);
			m_button[i]->setText(calcLabel[i]);
			m_button[i]->clicked.connect(this, &MainFrm::buttonClicked);
			m_button[i]->show();
			//printf("MainFrm::MainFrm m_button%d:%X\n", i, m_button[i]);
		}

		PD::Button* NUM_1 = m_button[12];
		PD::Button* NUM_2 = m_button[13];
		PD::Button* NUM_3 = m_button[14];
		PD::Button* CHAR_MINUS = m_button[15];

		PD::Button* NUM_0 = m_button[16];
		PD::Button* CHAR_DOT = m_button[17];
		PD::Button* CHAR_EQ = m_button[18];
		PD::Button* CHAR_PLUS = m_button[19];

		NUM_0->setWidgetKeyMover( 
			PD::WidgetKeyMover(NUM_1, 0, CHAR_PLUS, CHAR_DOT) );
		CHAR_DOT->setWidgetKeyMover( 
			PD::WidgetKeyMover(NUM_2, 0, NUM_0, CHAR_EQ) );
		CHAR_EQ->setWidgetKeyMover( 
			PD::WidgetKeyMover(NUM_3, 0, CHAR_DOT, CHAR_PLUS) );
		CHAR_PLUS->setWidgetKeyMover( 
			PD::WidgetKeyMover(CHAR_MINUS, 0, CHAR_EQ, NUM_0) );

	}
	~MainFrm()
	{
		delete m_label;
		for (int i=0; i<20; i++) delete m_button[i];
	}
protected:
	void showEvent()
	{
		int startX = 5;
		int startY = 5;

		m_label->setGeometry(startX, startY, width()-10, 40);
		m_label->setText("0");
		m_label->setAlignment( 
			(PD::Alignment) (PD::AlignRight | PD::AlignVCenter));

		startY = 55;
		int x = 0;
		int y = 0;
		int w = 60;
		int h = 40;
		int horzSpace = 5;
		int vertSpace = 5;

		for (int row=0; row<5; row++)
		{
			for (int col=0; col<4; col++)
			{
				int idx = row * 4 + col;
				x = startX + col * (w + horzSpace); 
				y = startY + row * (h + vertSpace);
				m_button[idx]->setGeometry(x, y, w, h);
			}
		}
	}

	void buttonClicked(PD::Button* w)
	{
		std::string text = m_label->text();

		if (w->text() == "Bksp")
		{
			if (text.size() > 0) 
			{
				text.erase(text.size()-1);	
				if (text.size() == 0) text = "0";
			}
		}
		else if (w->text() == "CE" || w->text() == "Clr")
		{
			text = "0";
		}
		else if (w->text() == "+-")
		{
			// TODO
		}
		else if (w->text() == "=")
		{
			// TODO
			text = "0";
		}
		else
		{
			if (text == "0") text = w->text();
			else text.append(w->text());
		}

		m_label->setText(text);
		m_label->repaint();
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(270, 300);

	MainFrm m(NULL, "MainFrm");
	m.setGeometry(0, 0, 270, 300);
	m.show();

	return app.exec();
}

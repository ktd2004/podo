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
#include <gui/PDCalendarUI.h>
#include <gui/PDLabel.h>
#include <gui/PDButton.h>
#include <base/PDDateTime.h>
#include <base/PDString.h>
#include <gui/PDPalette.h>

class MainFrm : public PD::Widget
{
private:
	PD::CalendarUI* m_calendar;
	PD::Label* m_year;
	PD::Label* m_month;

	PD::Button* m_yearUp;
	PD::Button* m_yearDown;

	PD::Button* m_monthUp;
	PD::Button* m_monthDown;

	PD::Button* m_current;

public:	
	MainFrm(Widget* parent, const char* name) : Widget(parent, name) 
	{
		m_calendar = new PD::CalendarUI(this, "Calendar");
		m_calendar->clicked.connect(this, &MainFrm::clickedDay);
		m_calendar->setGeometry(0, 50, 400, 250);
		m_calendar->show();

		PD::DateTime cur;
		std::string text;
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;

		// year
		m_yearDown = new PD::Button(this, "YearDown");
		m_yearDown->clicked.connect(this, &MainFrm::clickedYear);
		x = 10; y = 10; w = 30; h = 30;
		m_yearDown->setGeometry(x, y, w, h);
		m_yearDown->setText("<");
		m_yearDown->show();

		m_year = new PD::Label(this, "Year");
		x += w + 10; w = 60;
		m_year->setGeometry(x+10, y+5 ,w, h);
		text = PD::String::format("%4d", cur.year());
		m_year->setText(text.c_str());
		m_year->show();

		m_yearUp = new PD::Button(this, "YearUp");
		m_yearUp->clicked.connect(this, &MainFrm::clickedYear);
		x += w + 10; w = 30;
		m_yearUp->setGeometry(x, y , w, h);
		m_yearUp->setText(">");
		m_yearUp->show();


		// month
		m_monthDown = new PD::Button(this, "MonthDown");
		m_monthDown->clicked.connect(this, &MainFrm::clickedMonth);
		x += w + 20;
		m_monthDown->setGeometry(x, y ,w , h);
		m_monthDown->setText("<");
		m_monthDown->show();

		m_month = new PD::Label(this, "Month");
		x += w + 10;
		m_month->setGeometry(x+5, y+5, w, h);
		text = PD::String::format("%2d", cur.month());
		m_month->setText(text.c_str());
		m_month->show();

		m_monthUp = new PD::Button(this, "MonthUp");
		m_monthUp->clicked.connect(this, &MainFrm::clickedMonth);
		x += w + 10;
		m_monthUp->setGeometry(x, y, w, h);
		m_monthUp->setText(">");
		m_monthUp->show();

		m_current = new PD::Button(this, "Current");
		m_current->clicked.connect(this, &MainFrm::clickedCurrent);
		x += w + 10; w = 80; 
		m_current->setGeometry(x, y, w, h);
		m_current->setText("TODAY");
		m_current->show();
	}

	~MainFrm()
	{
		delete m_calendar;

		delete m_year;
		delete m_month;

		delete m_yearUp;
		delete m_yearDown;
		delete m_monthUp;
		delete m_monthDown;
		delete m_current;
	}

protected:
	void updateDate()
	{
		//printf("MainFrm::updateDate year:%d month:%d\n",
		//	m_calendar->year(), m_calendar->month());
		std::string text;

		text = PD::String::format("%4d", m_calendar->year());
		m_year->setText(text.c_str());
		m_year->repaint();

		text = PD::String::format("%2d", m_calendar->month());
		m_month->setText(text.c_str());
		m_month->repaint();

		m_calendar->repaint();
	}

	void clickedDay(int day)
	{
		printf("MainFrm::clickedDay day:%d\n", day);
	}

	void clickedYear(PD::Button* w)
	{
		if (w == m_yearUp)
			m_calendar->nextYear();
		else
			m_calendar->previousYear();

		updateDate();
	}

	void clickedMonth(PD::Button* w)
	{
		if (w == m_monthUp)
			m_calendar->nextMonth();
		else
			m_calendar->previousMonth();

		updateDate();
	}

	void clickedCurrent(PD::Button* /*w*/)
	{
		m_calendar->currentMonth();
		updateDate();
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

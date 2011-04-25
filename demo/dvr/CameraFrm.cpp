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
#include "CameraFrm.h"
#include <gui/PDButton.h>
#include <gui/PDLabel.h>
#include <gui/PDTableWidgetItem.h>
#include <base/PDString.h>

CameraFrm::CameraFrm(PD::Widget* parent) : PD::Widget(parent, "CameraFrm")
{
	PD::Color bgColor(16, 64, 104);
	palette().setColor(PD::Palette::Background, bgColor);

	initTitle();

	initTable();

	initOkCancel();
}

CameraFrm::~CameraFrm()
{
	if (m_titleLabel) delete m_titleLabel;

	if (m_table) delete m_table;

	if (m_okBtn) delete m_okBtn;
	if (m_cancelBtn) delete m_cancelBtn;
}

void CameraFrm::initTitle()
{
	m_titleLabel = new PD::Label(this, "TitleLabel", "Camera");
	m_titleLabel->palette().setColor(PD::Palette::Background, 
		PD::Color(32, 128, 208));
	m_titleLabel->palette().setColor(PD::Palette::Text, 
		PD::white);
	m_titleLabel->setFontSize(20);
	m_titleLabel->setGeometry(0, 0, 800, 30);
	m_titleLabel->show();
}

void CameraFrm::initTable()
{
	int maxRow = 17;
	int maxColumn = 5;
	m_table = new PD::TableWidget(this, "TableWidget", maxRow, maxColumn);
	m_table->setGeometry(10, 60, 800-20, 480);

	m_table->setMarginX(0);
	m_table->setMarginY(0);

	m_table->setColumnWidth(0, 80);
	m_table->setColumnWidth(1, 100);
	m_table->setColumnWidth(2, 200);
	m_table->setColumnWidth(3, 200);
	m_table->setColumnWidth(4, 200);

	// header
	std::string headers[maxColumn];
	headers[0] = "No";
	headers[1] = "Enable";
	headers[2] = "Name";
	headers[3] = "Resolution";
	headers[4] = "Framerate";
	m_table->setRowHeight(0, 40);
	for (int col=0; col<maxColumn; col++)
	{
		PD::TableWidgetTextItem* item = new PD::TableWidgetTextItem(m_table, 0, col);
		item->setSelectable(false);
		item->setText(headers[col]);
		m_table->setItem(0, col, item);
	}


	// body
	std::string tmpString;
	for (int row=1; row<maxRow; row++)
	{
		m_table->setRowHeight(row, 20);

		// No
		tmpString = PD::String::format("%d", row);
		PD::TableWidgetTextItem* item1 = new PD::TableWidgetTextItem(m_table, row, 0);
		item1->setSelectable(false);
		item1->setText(tmpString);
		m_table->setItem(row, 0, item1);

		// Enable
		tmpString = PD::String::format("ON");
		PD::TableWidgetTextItem* item2 = new PD::TableWidgetTextItem(m_table, row, 1);
		item2->setText(tmpString);
		item2->setAlignment(PD::AlignCenter);
		m_table->setItem(row, 1, item2);

		// Enable
		tmpString = PD::String::format("CAMERA-%d", row);
		PD::TableWidgetTextItem* item3 = new PD::TableWidgetTextItem(m_table, row, 2);
		item3->setText(tmpString);
		item3->setAlignment(PD::AlignLeft | PD::AlignVCenter);
		m_table->setItem(row, 2, item3);

		// Resolution
		PD::TableWidgetTextItem* item4 = new PD::TableWidgetTextItem(m_table, row, 3);
		item4->setText("704x480");
		m_table->setItem(row, 3, item4);

		// Framelate
		PD::TableWidgetTextItem* item5 = new PD::TableWidgetTextItem(m_table, row, 4);
		item5->setText("30");
		m_table->setItem(row, 4, item5);




	}

	m_table->show();
}

void CameraFrm::initOkCancel()
{
	m_okBtn = new PD::Button(this, "OkBtn", "OK");
	m_okBtn->clicked.connect(this, &CameraFrm::clickedOk);
	m_okBtn->setGeometry(610, 550, 80, 30);
	m_okBtn->show();

	m_cancelBtn = new PD::Button(this, "CancelBtn", "Cancel");
	m_cancelBtn->clicked.connect(this, &CameraFrm::clickedCancel);
	m_cancelBtn->setGeometry(710, 550, 80, 30);
	m_cancelBtn->show();
}

void CameraFrm::clickedOk(PD::Button*)
{
	close(0);
}

void CameraFrm::clickedCancel(PD::Button*)
{
	close(-1);
}

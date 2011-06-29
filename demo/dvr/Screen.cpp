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
#include "Screen.h"
#include <base/PDString.h>
#include <gui/PDApp.h>
#include <gui/PDPainter.h>

Screen::Screen(PD::Widget* parent) : PD::Widget(parent, "Screen")
{
	setBgMode(PD::NoBg);

	m_hasBorderLine = true;
	m_isVisibleCameraName = true;
	m_isVisibleOSD = true;

	m_selectedColor = PD::red;
	m_selectedIndex = -1;
	m_oldRow = -1;
	m_oldColumn = -1;

	m_layout = Layout_4x4;
	m_baseChannel = 0;

	m_oldLayout = Layout_4x4;
	m_oldBaseChannel = 0;

	m_maxChannel = m_layout * m_layout;

	for (int i=0; i<m_maxChannel; i++)
	{
		m_cameraName[i] = PD::String::format("CAM%02d", i+1);
		m_showLogo[i] = false;
	}

	m_logoImage[0].load("./images/logo1.png");
	m_logoImage[1].load("./images/logo2.png");
	m_logoImage[2].load("./images/logo3.png");
	m_logoImage[3].load("./images/logo4.png");

	palette().setColor(PD::Palette::Background, PD::blue);

    m_panic = false;

	m_popupMenu = new PD::PopupMenu(0, "PopupMenu");
	m_popupMenu->clicked.connect(this, &Screen::clickedPopupMenu);

	m_popupMenu->addItem( PD::PopupMenuItem("1x1") );
	m_popupMenu->addItem( PD::PopupMenuItem("2x2") );
	m_popupMenu->addItem( PD::PopupMenuItem("3x3") );
	m_popupMenu->addItem( PD::PopupMenuItem("4x4") );

	m_popupMenu->hide();
}

Screen::~Screen()
{
	delete m_popupMenu;
}

PD::Color Screen::selectedColor()
{
	return m_selectedColor;
}

void Screen::setSelectedColor(const PD::Color& color)
{
	m_selectedColor = color;
}

int Screen::selectedIndex()
{
	return m_selectedIndex;
}

void Screen::selectIndex(int idx)
{
	m_selectedIndex = idx;
	repaint();
}

int Screen::baseChannel()
{
	return m_baseChannel;
}

void Screen::setBaseChannel(int c)
{
	m_baseChannel = c;
}

int Screen::maxChannel()
{
	return m_maxChannel;
}

void Screen::setMaxChannel(int c)
{
	m_maxChannel = c;
}

Screen::Layout Screen::layout()
{
	return m_layout;
}

void Screen::setLayout(Layout l, int baseChannel/*=0*/)
{
	if (m_layout == l)
	{
		m_baseChannel += (m_layout*m_layout);
		if (m_baseChannel > m_maxChannel-1) m_baseChannel = 0;
	}
	else
	{
		m_baseChannel = baseChannel;
	}
	m_layout = l;
	repaint();
}

const std::string& Screen::cameraName(int idx)
{
	return m_cameraName[idx];
}

void Screen::setCameraName(int idx, const std::string& name)
{
	m_cameraName[idx] = name;
}

void Screen::setShowLogo(int idx, bool f)
{
	m_showLogo[idx] = f;
}

bool Screen::isVisibleCameraName()
{
	return m_isVisibleCameraName;
}

void Screen::showCameraName(bool f)
{
	m_isVisibleCameraName = f;
}

bool Screen::hasBorderLine()
{
	return m_hasBorderLine;
}

void Screen::setBorderLine(bool f)
{
	m_hasBorderLine = f;
}

bool Screen::isVisibleOSD()
{
	return m_isVisibleOSD;
}

void Screen::showOSD(bool f)
{
	m_isVisibleOSD = f;
}

void Screen::drawChannelArea(int idx, const PD::Rect& rect, PD::Painter* p)
{
	if (!m_showLogo[idx]) p->fillRect(rect, PD::blue);
	else
	{
		if (m_layout == Layout_1x1)
			p->drawImage(rect, m_logoImage[0]);
		else if (m_layout == Layout_2x2)
			p->drawImage(rect, m_logoImage[1]);
		else if (m_layout == Layout_3x3)
			p->drawImage(rect, m_logoImage[2]);
		else if (m_layout == Layout_4x4)
			p->drawImage(rect, m_logoImage[3]);
	}


	if (m_hasBorderLine)
	{
		PD::Rect borderRect(rect);
		p->save();
		p->setPenColor(PD::white);
		p->drawRect(borderRect);
		p->restore();
	}

	if (m_selectedIndex == idx)
	{
		//printf("Screen::drawChannelArea selectedIndex:%d\n", idx);
		p->save();
		p->setPenColor( m_selectedColor );
		PD::Rect borderRect(rect);
		p->drawRect(borderRect);
		p->restore();
	}

	PD::Rect textRect( rect.left()+5, rect.top()+5, 80, 20 );
	PD::Rect textRect2;

	p->setPenColor(PD::white);
	int margin = 1;

	// up left
	textRect2 = PD::Rect(textRect.left()-margin, textRect.top()-margin, 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// up
	textRect2 = PD::Rect(textRect.left(), textRect.top()-margin, 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// up right
	textRect2 = PD::Rect(textRect.left()+margin, textRect.top()-margin, 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// center left
	textRect2 = PD::Rect(textRect.left()-margin, textRect.top(), 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// center right
	textRect2 = PD::Rect(textRect.left()+margin, textRect.top(), 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// down left
	textRect2 = PD::Rect(textRect.left()-margin, textRect.top()+margin, 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// down
	textRect2 = PD::Rect(textRect.left(), textRect.top()+margin, 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// down right
	textRect2 = PD::Rect(textRect.left()+margin, textRect.top()+margin, 80, 20);
	p->drawText(textRect2, m_cameraName[idx].c_str(), PD::AlignVCenter);

	// center
	p->setPenColor(PD::black);
	p->drawText(textRect, m_cameraName[idx].c_str(), PD::AlignVCenter);

	p->save();
	p->setPenColor(PD::white);
	p->setBrushColor(PD::blue);
    p->drawText(rect, "NO SIGNAL", PD::AlignCenter);
	p->restore();

    if (m_panic)
    {
        p->fillRect(rect.right()-30,rect.top()+10,20,20,
                    PD::Color(255,0,0));
    }
}

void Screen::paintEvent(PD::PaintEvent* evt)
{
	//printf("Screen::paintEvent name:%s\n", name());

	if (evt->rect().width() != width() ||
		evt->rect().height() != height())
	{
		return;
	}

	PD::Painter p(this);

	int x = 0;
	int y = 0;
	int w = width() / m_layout;
	int h = height() / m_layout;

	int idx = m_baseChannel;

	for (int r=0; r<m_layout; r++)
	{
		for (int c=0; c<m_layout; c++)
		{
			if (idx > maxChannel()-1) break;
			PD::Rect rect(x, y, w, h);
			if (rect.intersect(evt->rect())) 
			{
				//printf("Screen::paintEvent ch:%d\n", idx);
				drawChannelArea(idx, rect, &p);
			}
			idx++;
			x += w;
		}
		x = 0;
		y += h;
	}
}

void Screen::mousePressEvent(PD::MouseEvent* evt)
{
	//printf("Screen::mousePressEvent\n");

	if (evt->button() == PD::MouseEvent::Left)
	{
		if (m_popupMenu->isVisible()) 
		{ 
			m_popupMenu->hide(); 
		}

		int w = width() / m_layout;
		int h = height() / m_layout;

		int column = evt->x() / w;
		int row = evt->y() / h;
		//printf("Screen::mousePressEvent Left row:%d column:%d\n", row, column);

		int idx = m_baseChannel + (row * m_layout) + column;
		if (idx == m_selectedIndex) m_selectedIndex = -1;
		else m_selectedIndex = idx;

		if (m_oldRow != -1 && m_oldColumn != -1)
		{
			repaint(PD::Rect(m_oldColumn*w, m_oldRow*h, w, h));
		}

		repaint(PD::Rect(column*w, row*h, w, h));
		m_oldRow = row;
		m_oldColumn = column;

		if (!hasFocus())
		{
			setFocus();
		}
	}
	else if (evt->button() == PD::MouseEvent::Right) // popup menu
	{
		//printf("Screen::mousePressEvent Right\n");

		int itemCount = m_popupMenu->itemList().size();
		int h = 24 * itemCount;

		PD::Point pt = PD::theApp->mousePosition();
		int posX=pt.x();
		int posY=pt.y();
		if( (posY - this->y())+h >= height() )
			posY -= h;
		if( (posX - this->x())+160 >= width() )
			posX -= 160;

		//printf("Screen::mousePressEvent m_popupMenu(%d, %d, %d, %d)\n",
		//	posX, posY, 160, h);
		m_popupMenu->setGeometry(posX, posY, 160, h);
		m_popupMenu->show();
	}
}

void Screen::clickedPopupMenu(int idx)
{
	//printf("Screen::clickedPopupMenu idx:%d\n", idx);
	m_popupMenu->hide();	
	int layout = idx + 1;
	setLayout((Layout)layout);
}

bool Screen::keyPressEvent(PD::KeyEvent* evt)
{
	printf("Screen::keyPressEvent\n");
	if (evt->key() == SDLK_UP) setLayout(Layout_1x1);	
	else if (evt->key() == SDLK_RIGHT) setLayout(Layout_2x2);
	else if (evt->key() == SDLK_DOWN) setLayout(Layout_3x3);
	else if (evt->key() == SDLK_LEFT) setLayout(Layout_4x4);
	else return false;

	return true;
}

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
#include "PDPopupMenu.h"
#include "../base/PDString.h"
#include <assert.h>
#include "PDPopupMenu_p.hpp"

namespace PD {

PopupMenuItem::PopupMenuItem()
{
	m_no = 0;
	m_enable = true;
}

PopupMenuItem::PopupMenuItem(const char* text, bool enable/*=true*/)
{
	m_no = 0;
	m_text = text;
	m_enable = enable;
}

size_t PopupMenuItem::no() { return m_no; }
void PopupMenuItem::setNo(size_t n) { m_no = n; }

const char* PopupMenuItem::text() { return m_text.c_str(); }
void PopupMenuItem::setText(const char* t) { m_text = t; }

bool PopupMenuItem::enable() const { return m_enable; }
void PopupMenuItem::setEnable(bool f) { m_enable = f; }

PopupMenuItem& PopupMenuItem::operator=(PopupMenuItem& item)
{
	m_no = item.no();
	m_text = item.text();
	m_enable = item.enable();

	return *this;
}

PopupMenu::PopupMenu(Widget* parent/*=NULL*/, 
	const char* name/*=0*/,
	uint style/*=Style_NoTitle*/): 
	Widget(parent, name, style, Theme::PopupMenu)
{
	d = new PopupMenuPrivate;
	setBgMode(NoBg);
}

PopupMenu::~PopupMenu()
{
	delete d;
}

PopupMenu::ItemList& PopupMenu::itemList() { return  d->itemList; }

int PopupMenu::selectedItem() { return d->select; }
void PopupMenu::setSelectItem(int idx) { d->select = idx; }

void PopupMenu::addItem(const PopupMenuItem& item)
{
	d->itemList.push_back(item);

	bool enable = item.enable();
	size_t addedNo = d->itemList.size()-1;
	d->itemList[addedNo].setNo(addedNo);

	if (d->select == -1 && enable) d->select = addedNo;
}

PopupMenuItem* PopupMenu::item(int idx)
{
	if (idx > (int)(d->itemList.size()-1) ) return NULL;

	return &d->itemList[idx];
}

void PopupMenu::paintEvent(PaintEvent*)
{
	//printf("PopupMenu::paintEvent name:%s\n", name());
	Painter p(this);

	int topH = 0;
	
	int textY = topH;
	int textH = height() / d->itemList.size();
	for (size_t i=0; i<d->itemList.size(); i++)
	{
		PopupMenuItem& item = d->itemList[i];

		if (d->select == (int)i)
		{
			p.fillRect(0, textY, width(), textH, 
					palette().color(Palette::FocusColor) );
			p.setBrushColor( palette().color(Palette::FocusColor) );

			p.setPenColor( palette().color(Palette:: HighlightText,
				(Palette::State)!item.enable()) ) ;
		}
		else
		{
			p.fillRect(0, textY, width(), textH, 
				palette().color(Palette::Background) );
			p.setBrushColor( palette().color(Palette::Background) );

			p.setPenColor( palette().color(Palette::Text, 
				(Palette::State)!item.enable()) ) ;
		}

		p.drawText(4, textY + 4, item.text());
		p.drawHLine(0, textY + textH, width(), textH);

		textY += textH;
	}
	p.drawRect(0, 0, width(), height());
}

void PopupMenu::mouseEvent(MouseEvent* evt)
{
	if (disable()) return;

	MouseEvent::Msg msg = evt->msg();
	MouseEvent::Button button = evt->button();
	int x = evt->x();
	int y = evt->y();

	//printf("PopupMenu::mouseEvent button:%d x:%d y:%d\n",
	//button, x, y);

	if (msg == Event::MouseRelease && button == MouseEvent::Left)
	{
		Point globalPt = mapToGlobal();
		Rect globalRect(globalPt.x(), globalPt.y(), width(), height());
		if (!globalRect.contains(x, y))
		{
			clicked.emit(-1);
		}
		else
		{
			int idx = selectedItem(x, y);
			d->select = idx;
			clicked.emit(d->select);
		}
	}
	else if (msg == Event::MouseMove)
	{
		int idx = selectedItem(evt->x(), evt->y());
		if (idx == -1) return;
		d->select = idx;
		repaint();
	}
}

void PopupMenu::mouseReleaseEvent(MouseEvent* evt)
{
	if (evt->button() == MouseEvent::Left)
	{
		int idx = selectedItem(evt->x(), evt->y());
		if (idx == -1) return;
		d->select = idx;

		clicked.emit(d->select);
	}
}

int PopupMenu::selectedItem(int x, int y)
{
	int topH = 0;	
	int itemH = height() / d->itemList.size();

	Point pt(x, y);
	Point localPt = mapFromGlobal(pt);

	int tempY = localPt.y() - topH;
	int idx = tempY / itemH;

	//printf("PopupMenu::selectedItem global(%d,%d) local(%d,%d)\n", 
	//	x, y, localPt.x(), localPt.y());
	//printf("PopupMenu::selectedItem selected:%d\n", idx);
	if (idx == -1 || idx > (int)(d->itemList.size()-1)) 
	{
		//printf("PopupMenu::selectedItem invalid idx:%d\n", idx);
		return -1;
	}

	// check enabled item
	if (!d->itemList[idx].enable())
	{
		//printf("PopupMenu::selectedItem disabled selected idx:%d\n", idx);
		return -1;
	}

	//printf("PopupMenu::selectedItem selected idx:%d\n", idx);

	return idx;
}

int PopupMenu::nextItem(int current, bool down/*=true*/)
{
	bool found = false;
	int idx = current;
	while(1)
	{
		if (down)
		{
			idx++;
			if (idx > (int)(d->itemList.size()-1) ) break;
		}
		else
		{
			idx--;
			if (idx < 0) break;
		}

		// check enabled item
		if (d->itemList[idx].enable())
		{
			found = true;	
			break;
		}

	}
	if (!found) return -1;

	return idx;
}

bool PopupMenu::keyReleaseEvent(KeyEvent* evt)
{
	int key = evt->key();
	//printf("PopupMenu::keyReleaseEvent key:%d\n", key);

	if (key == SDLK_UP || key == SDLK_LEFT)
	{
		int n = nextItem(d->select, false);
		if (n == -1) return true;

		d->select = n;
		repaint();
	}
	else if (key == SDLK_RIGHT || key == SDLK_DOWN)
	{
		int n = nextItem(d->select);
		if (n == -1) return true;

		d->select = n;
		repaint();
	}
	else if (key == SDLK_RETURN)
	{
		if (d->select == -1) return true;
		//printf("PopupMenu::keyReleaseEvent select:%d\n", d->select);
		clicked.emit(d->select);
	}
	else if (key == SDLK_ESCAPE)
	{
		close();
		clicked.emit(-1);
		return true;
	}

	return true;
}

} //namespace PD {

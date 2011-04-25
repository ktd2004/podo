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
#ifndef _PDEVENT_H_
#define _PDEVENT_H_

#include <SDL.h>
#include <base/PDObject.h>
#include "PDRect.h"

namespace PD {

class Widget;

class Event
{
public:
	enum Msg
	{
		MsgNone=0,

		Show=1,
		Hide=2,
		Paint=3,
		Close=4,
		Move=5,
		Resize=6,

		FocusIn=7,
		FocusOut=8,

		Enter=9,
		Leave=10,

		Timer=11,
		
		KeyPress=12,
		KeyRelease=13,

		MousePress=14,
		MouseRelease=15,
		MouseMove=16,

		Custom=17
	};
private:
	Widget* m_widget;
	Msg m_msg;

public:
	Event();
	Event(Msg msg);

	void setWidget(Widget* w) { m_widget = w; }
	Widget* widget() { return m_widget; }
	Msg msg() { return m_msg; }
};

class MoveEvent : public Event
{
private:
	Point m_oldPoint;	
	Point m_newPoint;	

public:
	MoveEvent(const Point& oldPoint, const Point& newPoint) : Event(Move) 
	{ 
		m_oldPoint = oldPoint; 
		m_newPoint = newPoint; 
	}

	const Point& oldPoint() { return m_oldPoint; }
	const Point& newPoint() { return m_newPoint; }
};



class ResizeEvent : public Event
{
private:
	Rect m_oldRect;	
	Rect m_newRect;	

public:
	ResizeEvent(const Rect& oldRect, const Rect& newRect) : Event(Resize) 
	{ 
		m_oldRect = oldRect; 
		m_newRect = newRect; 
	}

	const Rect& oldRect() { return m_oldRect; }
	const Rect& newRect() { return m_newRect; }
};

class PaintEvent : public Event
{
private:
	Rect m_rect;	

public:
	PaintEvent(const Rect& rect) : Event(Paint) 
	{ m_rect = rect; }

	const Rect& rect() { return m_rect; }
};

class FocusInEvent : public Event
{
public:
	FocusInEvent() : Event(FocusIn) { }
};

class FocusOutEvent : public Event
{
public:
	FocusOutEvent() : Event(FocusOut) { }
};



class KeyEvent : public Event
{
private:
	int m_key;	

public:
	KeyEvent(Msg msg, int key) : Event(msg)
	{		
		m_key = key;
	}

	int key() { return m_key; }
};

class MouseEvent : public Event
{
public:
	enum Button { None, Left, Middle, Right, WheelUp, WheelDown };

private:
	Button m_button;
	int m_x;
	int m_y;

public:
	MouseEvent(Msg msg, Button button, int x, int y) : Event(msg)
	{
		m_button = button;
		m_x = x;
		m_y = y;
	}

	void setButton(Button btn) { m_button = btn; }

	Button button() { return m_button; }
	int x() { return m_x; }
	int y() { return m_y; }
};


class CustomEvent : public Event
{
private:
	int m_no;

public:
	CustomEvent(int no) : Event(Custom)
	{
		m_no = no;
	}

	void setNo(int no) { m_no = no; }
	int no() { return m_no; }
};

class EventFilter : public Object
{
private:
	Widget* m_parent;

public:
	EventFilter(Widget* parent) { m_parent = parent; }
	virtual ~EventFilter() {}

	Widget* parent() { return m_parent; }

	virtual bool filter(Event* evt) = 0;
};

} //namespace PD {

#endif

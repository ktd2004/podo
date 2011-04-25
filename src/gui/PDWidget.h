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
#ifndef _PDWIDGET_H_
#define _PDWIDGET_H_

#include <SDL.h>
#include "PDGlobal.h"
#include <base/PDObject.h>
#include "PDImage.h"
#include "PDRect.h"
#include "PDFont.h"
#include "PDEvent.h"
#include "PDPalette.h"
#include "PDTheme.h"
#include <list>

namespace PD {

class Button;
class Painter;
class Widget;

/**
 * \brief
 * \ingroup gui
 */
class WidgetKeyMover
{
private:
	Widget *m_up, *m_down, *m_left, *m_right;

public:
	WidgetKeyMover();
	WidgetKeyMover(Widget* _up, Widget* _down, Widget* _left,
			Widget* _right);

	void setUp(Widget* _up);
	Widget* up() const;

	void setDown(Widget* _down);
	Widget* down() const;

	void setLeft(Widget* _left);
	Widget* left() const;

	void setRight(Widget* _right);
	Widget* right() const;

	WidgetKeyMover& operator=(const WidgetKeyMover& ctrl);
};


class WidgetPrivate;
/**
 * \brief
 * \ingroup gui
 */
class Widget : public Object
{
public:

public:
	friend class App;
	friend class AppPrivate;
	friend class DesktopWidget;
	friend class Painter;

	typedef std::list<Widget*> 		WidgetList;
	typedef WidgetList::iterator 	WidgetListIt;
	typedef WidgetList::reverse_iterator WidgetListReverseIt;
	
	friend class Button;

private:
	WidgetPrivate* d;

public:
	Widget(Widget* parent=0, const char* name=0, Uint32 style=0,
		Theme::Control themeControl=Theme::Widget);
	virtual ~Widget();

	void setName(const char* name);
	const char* name();

	void setBgMode(BgMode mode);
	BgMode bgMode(); 

	void setParent(Widget* p);

	void setDisable(bool disable);
	bool disable();

	Widget* findChild(Widget* w);

	WidgetList& childList();

	int x();
	int y();
	int width();
	int height();
	Rect geometry();
	void setGeometry(int x, int y, int w, int h);
	void resize(int w, int h);

	void center(int w, int h);
	void center();

	int result();

	bool isClosed();
	bool isClosing();

	void setPopup(bool f);
	bool isPopup();

	void setModal(bool f);
	bool isModal();

	Image* background();

	FocusPolicy	focusPolicy();
	void setFocusPolicy(FocusPolicy f);

	bool hasFocus();
	virtual void setFocus(bool f=true);

	bool isVisible();
	void setVisible(bool f=true);

	void setBackground(const char* fn);

	Widget* topParent();
	Widget* parent();

	Font* font();
	Font* setFont(const char* name, int size);
	void setFontSize(int size);

	SDL_Surface* surface();

	virtual void show();
	virtual void hide();

	int exec();
	void close(int ret);
	void close();

	void repaint(const Rect& rect);
	void repaint();

	void update();
	void update(const Rect& rect);

	Point mapToGlobal();
	Point mapToGlobal(const Point& pt);
	Point mapToGlobal(int x, int y);
	Point mapFromGlobal(const Point& pt);

	bool hasContains(int x, int y);

	void setWidgetKeyMover(WidgetKeyMover a);
	WidgetKeyMover& keyMover();
	Palette& palette();
	void setPalette(Palette p);

	void grabMouse();
	void releaseMouse();

	void setMaskClear();
	void setMaskColor(const Color& rgb);
	Color maskColor();

protected:
	virtual bool create();
	virtual bool create(SDL_Surface** s, int w, int h);

	virtual void event(Event* evt);
	virtual void showEvent();
	virtual void showFinishedEvent();
	virtual void hideEvent();

	void paintBg(const Rect& r);
	void paintBg();
	void paintChild(const Rect& r);
	void paintChild();
	void paint(PaintEvent* evt);
	void paint(const Rect& r);
	void paint();

	virtual void paintEvent(PaintEvent*);

	virtual void resizeEvent(ResizeEvent*);
	
	virtual bool focusInEvent(FocusInEvent*);
	virtual bool focusOutEvent(FocusOutEvent*);

	virtual void enterEvent();
	virtual void leaveEvent();

	void timerEvent();

	virtual bool keyPressEvent(KeyEvent* evt);
	virtual bool keyReleaseEvent(KeyEvent* evt);

	virtual void mouseEvent(MouseEvent* evt);
	virtual void mousePressEvent(MouseEvent* evt);
	virtual void mouseReleaseEvent(MouseEvent* evt);
	virtual void mouseMoveEvent(MouseEvent* evt);
	virtual void mouseDoubleClickEvent(MouseEvent* evt);
	virtual void wheelUpEvent(MouseEvent* evt);
	virtual void wheelDownEvent(MouseEvent* evt);

	virtual void customEvent(CustomEvent* evt);

	void draw3DEffect(Painter* p, bool selected=false);

private:
	void setResult(int r);
	bool handleKeyMove(KeyEvent* key);

	void repaint(PaintEvent* evt);
	bool keyEvent(KeyEvent* evt);

	Widget* findMouseWidget(const Point& pt);

	void addChild(Widget* w);
	void removeChild(Widget* w);

	void killFocus();
	Widget* focusWidget();
};

} //namespace PD {

#endif

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
#ifndef _PDAPP_H_
#define _PDAPP_H_

#include <SDL.h>
#include "PDDesktopWidget.h"
#include "PDWidget.h"
#include "PDEvent.h"
#include "PDFontDB.h"
#include "PDTheme.h"
#include "PDLang.h"
#include "../base/PDMutex.h"
#include <list>
#include <string>

namespace PD {

#define PD_TR(GROUP, KEY) PD::theApp->tr(GROUP, KEY)

class AppPrivate;

/**
 * \defgroup gui
 */

/**
 * \brief 
 * \ingroup gui
 */
class App
{
public:
	typedef std::list<Event*> EventList;
	typedef std::list<Event*>::iterator EventListIt;

private:
	AppPrivate* d;
	
public:
	friend class AppPrivate;
	friend class DesktopWidget;
	friend class Widget;

	App(int w=0, int h=0, int bpp=0);	
	~App();	

	bool isFullScreen();
	void setFullScreen(bool f);

	void setShowCursor(bool f);


	void setFontDir(const char* dir);
	std::string fontDir();
	
	void setFontName(const char* name);
	std::string fontName();

	void setFontSize(int size);
	int fontSize();
	
	bool setPalette(const char* fn, size_t size);
	void printPalette(SDL_Surface* surface);

	Theme* theme();
	void setTheme(Theme* s);

	FontDB& fontDB();

	static Point mousePosition();

	int exec();

	void exit(int retCode=0);

	DesktopWidget* desktopWidget();

	Widget* mainWidget();
	void setMainWidget(Widget* w);

	Widget* mouseWidget();
	void setMouseWidget(Widget* w);

	Widget* focusWidget();
	void setFocusWidget(Widget* w);

	Widget* popupWidget();
	void setPopupWidget(Widget* w);

	Widget* modalWidget();
	void setModalWidget(Widget* w);

	EventFilter* eventFilter();
	void setEventFilter(EventFilter* w);

	void postEvent(Widget* w, Event* evt);
	bool sendEvent(Widget* w, Event* evt);
	static bool pollEvent();
	static void processEvent();
	void flushEvent();


	std::string tr(const std::string& group, const std::string& key);
	Lang* language();
	void setLanguage(Lang* l);

protected:
	Mutex& eventListMutex();
	EventList& eventList();

	bool deleteAfterMouseUp();
	void setDeleteAfterMouseUp(bool f);

	int screenWidth();
	int screenHeight();
	int screenBpp();

private:
	static void removeEvent(Widget* widget);
	void setScreen(int w, int h, int bpp);
};

extern App* theApp;

} //namespace PD {

#endif

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
#ifndef _PDAPP_P_H_
#define _PDAPP_P_H_

#include <assert.h>
#include "../base/PDMutexLocker.h"

namespace PD {

class AppPrivate
{
public:
	std::string 		fontDir;
	std::string 		fontName;
	int 				fontSize;
	
	bool fullScreen;

	int screenWidth;
	int screenHeight;
	int screenBpp;

	bool exitFlag;

	EventFilter* eventFilter;

	Widget* mainWidget;
	Widget* popupWidget;
	Widget* modalWidget;
	Widget* mouseWidget;
	Widget* focusWidget;
	DesktopWidget desktopWidget;	

	Mutex eventListMutex;
	App::EventList eventList;

	int retCode;

	bool deleteAfterMouseUp;

	FontDB fontDB;

	Theme* theme;

	Lang *language;

public:
	AppPrivate()
	{
		exitFlag = false;
		eventFilter = 0;

		theme = 0;

		retCode = 0;

		fullScreen = false;

		screenWidth = 0;
		screenHeight = 0;
		screenBpp = 0;

		mainWidget = NULL;
		popupWidget = NULL;
		modalWidget = NULL;
		mouseWidget = NULL;
		focusWidget = NULL;

		fontName = "Vera.ttf";
		fontSize = 12;

		deleteAfterMouseUp = false;

		language = NULL;
	}

	int initialize()
	{
		std::string errMsg;

		const char* pdDir = getenv("PD_DIR");
		if (pdDir == 0)
		{
			errMsg = "PD_DIR env not set";
			goto APP_END;
		}

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE) == -1)
		{
			errMsg = "Failed to SDL_Init";
			goto APP_END;
		}

		if (SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, 
					SDL_DEFAULT_REPEAT_INTERVAL) == -1)
		{
			errMsg = "Failed to SDL_EnableKeyRepeat";
			goto APP_END;
		}

		if (TTF_Init() == -1)
		{
			errMsg = "Failed to TTF_Init";
			goto APP_END;
		}

		fontDir = pdDir;
		fontDir += "/lib/fonts";

		//printf("App::initialize ok\n");

		return 0;

APP_END:
		#ifdef WIN32
		MessageBoxA(NULL, errMsg.c_str(), "PD", MB_OK);
		ExitProcess(0);
		#else	
		printf("App::initialize %s(%s)\n", errMsg.c_str(), SDL_GetError());
		exit(0);
		#endif

		return 0;
	}

	static Event* convertSDLEvent(SDL_Event& sdlEvt)
	{
		Event* evt = 0;

		if (sdlEvt.type == SDL_ACTIVEEVENT)
		{
			//printf("App::convertSDLEvent SDL_ACTIVEEVENT\n");
		}
		else if (sdlEvt.type == SDL_QUIT)
		{
			//printf("App::convertSDLEvent SDL_QUIT\n");
			theApp->exit(0);
		}
		else if (sdlEvt.type == SDL_KEYDOWN || sdlEvt.type == SDL_KEYUP)
		{
			Event::Msg msg = Event::MsgNone;
			if (sdlEvt.type == SDL_KEYDOWN) msg = Event::KeyPress;
			else if (sdlEvt.type == SDL_KEYUP) msg = Event::KeyRelease;

			//printf("App::convertSDLEvent SDL_KEYDOWN or SDL_KEYUP\n");

			if (theApp->focusWidget() && 
				!theApp->focusWidget()->isClosing()) 
			{
				evt = new KeyEvent(msg, (int)sdlEvt.key.keysym.sym);
				evt->setWidget(theApp->focusWidget());
				//printf("App::convertSDLEvent focusWidget:%s msg:%d key:%d\n", 
				//	theApp->focusWidget()->name(), msg, sdlEvt.key.keysym.sym);
			}
		}
		else if (sdlEvt.type == SDL_MOUSEBUTTONDOWN ||
				sdlEvt.type == SDL_MOUSEBUTTONUP ||
				sdlEvt.type == SDL_MOUSEMOTION)
		{
			Event::Msg msg = Event::MsgNone;
			if (sdlEvt.type == SDL_MOUSEBUTTONDOWN) msg = Event::MousePress;
			else if (sdlEvt.type == SDL_MOUSEBUTTONUP) msg = Event::MouseRelease;
			else if (sdlEvt.type == SDL_MOUSEMOTION) msg = Event::MouseMove;

			MouseEvent::Button button;
			if (sdlEvt.button.button == SDL_BUTTON_LEFT)
				button = MouseEvent::Left;
			else if (sdlEvt.button.button == SDL_BUTTON_RIGHT)
				button = MouseEvent::Right;
			else if (sdlEvt.button.button == SDL_BUTTON_MIDDLE)
				button = MouseEvent::Middle;

			else if (sdlEvt.button.button == SDL_BUTTON_WHEELUP)
				button = MouseEvent::WheelUp;
			else if (sdlEvt.button.button == SDL_BUTTON_WHEELDOWN)
				button = MouseEvent::WheelDown;
			else
				button = MouseEvent::None;

			Widget* w = 0;
			if (theApp->modalWidget()) 
			{
				w = theApp->modalWidget()->findMouseWidget(
						Point(sdlEvt.button.x, sdlEvt.button.y));
			}
			else
			{
				w = theApp->desktopWidget()->findMouseWidget(
						Point(sdlEvt.button.x, sdlEvt.button.y));	
			}
			//assert(w != 0);
			if (w == 0) return 0;

			if (!w->isClosing())
			{
				evt = new MouseEvent(msg, button, 
					sdlEvt.button.x, sdlEvt.button.y);
				evt->setWidget(w);
			}
		}
		else
		{
			printf("App::convertSDLEvent unknown type:%d\n", sdlEvt.type);
		}

		if (evt)
		{
			MutexLocker ml(&theApp->eventListMutex());
			theApp->eventList().push_back(evt);
			//printf("App::convertSDLEvent name:%s msg:%d\n",
			//	evt->widget()->name(), evt->msg());
		}

		return evt;
	}
};

} //namespace PD {

#endif

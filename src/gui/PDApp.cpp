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
#include "PDApp.h"
#include "PDApp_p.hpp"
#include <stdio.h>
#include "PDPainter.h"
#include "../base/PDFile.h"
#include "../base/PDString.h"

namespace PD {

App* 			theApp = 0;

/**
 * \brief 생성자
 *
 * 프로그램 시작시 width, height, bpp를 지정하지 않으면 시스템이 지원하는
 * 전체해상도를 기준으로 전체 윈도우를 생성한다.\n
 * 다음과 같이 환경변수 PD_SCREEN_RESOLUTON을 지정하면 기본인자를 무시한다.\n
 * 예) export PD_SCREEN_RESOLUTION=1024x768x32
 *
 * \param w width
 * \param h height
 * \param bpp bit per pixel
 */
App::App(int w/*=0*/, int h/*=0*/, int bpp/*=0*/)
{
	theApp = this;
	d = new AppPrivate;

	const char* resolution = getenv("PD_SCREEN_RESOLUTION");
	if (resolution != 0)
	{
		String::StringList list = String::split(resolution, "x");
		if (list.size() == 3)
		{
			w = atoi(list[0].c_str());
			h = atoi(list[1].c_str());
			bpp = atoi(list[2].c_str());

			//printf("App::App resolution(w:%d h:%d bpp:%d)\n", w, h, bpp);
		}
	}

	setScreen(w, h, bpp);
	d->initialize();
}

/**
 * \brief 소멸자
 */
App::~App()
{
	SDL_Quit();

	delete d;
}

/**
 * \brief 마우스 커서를 보일지 말지를 설정한다.
 *
 * \param f true/false
 */
void App::setShowCursor(bool f)
{
	SDL_ShowCursor(f);
}

/**
 * \brief 기본 폰트 위치 설정
 *
 * 아무런 설정을 하지 않았을때 기본 위치는 환경변수 $PD_DIR/lib/fonts 가 된다.\n
 * 만약에 이 위치를 바꾸고자 할때에 이 함수를 호출하여 변경하면 된다.
 *
 * \param dir 패스
 *
 * \sa fontDir()
 */
void App::setFontDir(const char* dir)
{
	d->fontDir = dir;
}

/**
 * \brief 현재 설정된 폰트위치를 읽어옴
 *
 * \return 폰트위치
 * \sa setFontDir()
 */
std::string App::fontDir() { return d->fontDir; }

/**
 * \brief 기본 폰트파일명을 읽어옴
 *
 * \return 폰트파일명
 * \sa setFontName()
 */
std::string App::fontName() { return d->fontName; }

/**
 * \brief 기본 폰트파일을 설정한다.
 *
 * 폰트를 설정할때에는 반드시 파일명으로 지정한다.\n
 * 예) theApp->setFontName("arial.ttf");
 *
 * \param name 폰트파일명
 * \sa fontName()
 */
void App::setFontName(const char* name)
{
	d->fontName = name;
}

/**
 * \brief 기본 폰트 크기를 설정한다.
 *
 * 예) theApp->setFontSize(12);
 *
 *
 * \param size 폰트의 pixel 크기
 * \sa fontSize()
 */
void App::setFontSize(int size) { d->fontSize = size; }

/**
 * \brief 기본 폰트 크기를 읽어온다.
 *
 * \return 폰트의 pixel 크기
 * \sa setFontSize()
 */
int App::fontSize() { return d->fontSize; }
	
/**
 * \brief 테마 객체 포인터를 얻어온다.
 *
 * \return 테마 객체 포인터
 * \sa setTheme()
 */
Theme* App::theme() { return d->theme; }

/**
 * \brief 테마를 설정한다.
 *
 * \param s 테마 객체 포인터
 * \sa theme()
 */
void App::setTheme(Theme* s) { d->theme = s; }

/**
 * \brief 폰트 데이타베이스 객체의 레퍼런스를 얻어온다.
 *
 * \return 폰트 데이타베이스 객체 레퍼런스
 */
FontDB& App::fontDB() { return d->fontDB; }

/**
 * \brief 현재 설정된 이벤트 필터를 읽어온다.
 *
 * \return 이벤트 필터 포인터
 * \sa setEventFilter()
 */
EventFilter* App::eventFilter() { return d->eventFilter; }

/**
 * \brief 이벤트 필터를 지정한다.
 *
 * 이벤트 필터를 지정하면 모든 이벤트는 해당 필터를 거친후에 처리가 된다.
 *
 * \param w 이벤트 필터 포인터
 * \sa eventFilter()
 */
void App::setEventFilter(EventFilter* w) { d->eventFilter = w; }

/**
 * \brief 현재 설정된 언어를 읽어온다.
 *
 * \return Lang포인터
 * \sa setLanguage()
 * \sa tr()
 */
Lang* App::language() { return d->language; }

/**
 * \brief 언어를 지정한다.
 *
 * \param l 언어
 * \sa language()
 * \sa tr()
 */
void App::setLanguage(Lang* l){ d->language = l; }

/**
 * \brief 이벤트 큐의 Mutex를 얻어온다(내부용)
 *
 * \return Mutex
 * \sa eventList()
 */
Mutex& App::eventListMutex() { return d->eventListMutex; }

/**
 * \brief 이벤트 큐를 얻어온다.(내부용)
 *
 * \return EventQueue
 * \sa eventListMutex()
 */
App::EventList& App::eventList() { return d->eventList; }

bool App::deleteAfterMouseUp() { return d->deleteAfterMouseUp; }
void App::setDeleteAfterMouseUp(bool f) { d->deleteAfterMouseUp = f; }

/**
 * \brief 다국어 처리를 위한 함수
 *
 * \param group 그룹명
 * \param key 키값
 *
 * \return 변환된 다국어
 * \sa language()
 * \sa setLanguage()
 */
std::string App::tr(const std::string& group, const std::string& key)
{
	if ( d->language == NULL )
		return key;
	else
		return language()->tr(group, key);
}

/**
 * \brief 전체화면인지를 확인
 *
 * \return true/false
 * \sa setFullScreen()
 */
bool App::isFullScreen()
{
	return d->fullScreen;
}

/**
 * \brief 전체화면 설정
 *
 * \param f true/false
 * \sa isFullScreen()
 */
void App::setFullScreen(bool f)
{
	d->fullScreen = f;
}

/**
 * \brief 화면 가로 해상도를 얻음
 *
 * \return 화면 가로 해상도
 */
int App::screenWidth()
{
	return d->screenWidth;
}

/**
 * \brief 화면 세로 해상도를 얻음
 *
 * \return 화면 세로 해상도
 */
int App::screenHeight()
{
	return d->screenHeight;
}

/**
 * \brief 화면 depth를 얻음
 *
 * \return 화면 depth
 */
int App::screenBpp()
{
	return d->screenBpp;
}

void App::setScreen(int w, int h, int bpp)
{
	d->screenWidth = w;
	d->screenHeight = h;
	d->screenBpp = bpp;
}

/**
 * \brief 마우스 포인터의 위치를 얻음
 *
 * \return 마우스 포인터의 위치
 */
Point App::mousePosition()
{
	int x=-1; 
	int y=-1;

	SDL_GetMouseState(&x, &y);

	return Point(x, y);
}

/**
 * \brief desktop wiget의 포인터를 얻음
 *
 * \return desktop widget의 포인터
 */
DesktopWidget* App::desktopWidget()
{
	return &d->desktopWidget;
}

/**
 * \brief palette설정파일을 읽어서 system palette설정
 *
 * \param fn 파일이름
 * \param size 파일크기
 *
 * \return true/false
 * \sa printPalette()
 */
bool App::setPalette(const char* fn, size_t size)
{
    File f;
    if (f.open(fn, File::ReadOnly) == -1)
    {
        printf("App::setPalette failed to open '%s'\n", fn);
        return false;
    }

    SDL_Color* pal = new SDL_Color[size];
    size_t n = f.read((unsigned char*)pal, sizeof(SDL_Color)*size);
    if (n != sizeof(SDL_Color)*size)
    {
        delete [] pal;

        printf("App::setPalette failed to read '%s'\n", fn);
        return false;
    }

    SDL_SetPalette(d->desktopWidget.surface(),
        SDL_LOGPAL|SDL_PHYSPAL, pal, 0, 256);
    //printPalette(d->desktopWidget.surface());

    delete [] pal;

    return true;
}

/**
 * \brief surface의 palette 정보를 console로 print(debugging용)
 *
 * \param surface SDL surface 포인터
 * \sa setPalette()
 */
void App::printPalette(SDL_Surface* surface)
{
	assert(surface != 0);

	printf("App::printPalette ncolors:%d\n", 
			surface->format->palette->ncolors);
	SDL_Color* col = surface->format->palette->colors;
	for (int i=0; i<surface->format->palette->ncolors; i++)
	{
		printf("%03d --> R:0x%02X, G:0x%02X, B:0x%02X\n",
			i, col->r, col->g, col->b);
		col++;
	}
}

/**
 * \brief 메인 wiget 포인터
 *
 * \return 메인 widget 포인터
 * \sa setMainWidget()
 */
Widget* App::mainWidget()
{
	return d->mainWidget;
}

/**
 * \brief 메인 wiget 포인터를 설정
 *
 * \param w 메인 widget 포인터
 * \sa mainWidget()
 */
void App::setMainWidget(Widget* w)
{
	assert(w != 0);
	//printf("App::setMainWidget name:%s\n", w->name());
	d->mainWidget = w;
}

/**
 * \brief 마우스 wiget 포인터
 *
 * \return 마우스 widget 포인터
 * \sa setMouseWidget()
 */
Widget* App::mouseWidget()
{
	return d->mouseWidget;
}

/**
 * \brief 마우스 wiget 포인터를 설정
 *
 * \param w 마우스 widget 포인터
 * \sa mouseWidget()
 */
void App::setMouseWidget(Widget* w)
{
	d->mouseWidget = w;
}

/**
 * \brief 포커스 wiget 포인터
 *
 * \return 포커스 widget 포인터
 * \sa setFocusWidget()
 */
Widget* App::focusWidget()
{
	return d->focusWidget;
}

/**
 * \brief 포커스 wiget 포인터를 설정
 *
 * \param w 포커스 widget 포인터
 * \sa focusWidget()
 */
void App::setFocusWidget(Widget* w)
{
	if (w == d->focusWidget) return;
	//if (w) printf("App::setFocusWidget name:%s\n", w->name());
	//else printf("App::setFocusWidget delete\n");

	if (d->focusWidget)
	{
		d->focusWidget->killFocus();
		if (d->focusWidget->isVisible())
		{
			FocusOutEvent* evt = new FocusOutEvent;
			postEvent(d->focusWidget, evt);
		}
	}

	d->focusWidget = w;
}

/**
 * \brief popup wiget 포인터
 *
 * \return popup widget 포인터
 * \sa setPopupWidget()
 */
Widget* App::popupWidget()
{
	return d->popupWidget;
}

/**
 * \brief popup wiget 포인터를 설정
 *
 * \param w popup widget 포인터
 * \sa popupWidget()
 */
void App::setPopupWidget(Widget* w)
{
	//if (w) printf("App::setPopupWidget name:%s\n", w->name());
	d->popupWidget = w;
}

/**
 * \brief modal wiget 포인터
 *
 * \return modal widget 포인터
 * \sa setModalWidget()
 */
Widget* App::modalWidget()
{
	return d->modalWidget;
}

/**
 * \brief modal wiget 포인터를 설정
 *
 * \param w modal widget 포인터
 * \sa modalWidget()
 */
void App::setModalWidget(Widget* w)
{
	//if (w) printf("App::setModalWidget name:%s\n", w->name());
	//else printf("App:setModalWidget delete\n");
	d->modalWidget = w;
}

/**
 * \brief widget에게 event를 전달한다
 *
 * postEvent함수는 sendEvent함수와 동일하게 widget에게 event를 전달하는\n
 * 역할을 하지만, 이 두함수의 차이점은 postEvent는 내부 event queue의 끝에추가되어\n
 * 기존에 남아있던 event가 모두 처리되고 나서 수행되지만, sendEvent의 경우\n
 * 기존에 있는 queue와 상관없이 그 즉시 처리가 된다.
 *
 * 예)
 * PD::KeyEvent* evt = new PD::KeyEvent(PD::Event::KeyPress, SDLK_UP);
 * theApp->postEvent(evt);
 *
 * \param w event를 받을 widget 포인터
 * \param evt event
 *
 * \sa sendEvent()
 */
void App::postEvent(Widget* w, Event* evt)
{
	if (w == 0 || evt == 0) return;
	evt->setWidget(w);

	if (w && w->isClosing() && 
		evt->msg() != Event::Close)
	{
		//printf("App::postEvent name:%s isClosing\n", w->name());
		delete evt;
		return;
	}
	MutexLocker ml(&d->eventListMutex);
	d->eventList.push_back(evt);
}

/**
 * \brief widget에게 event를 전달한다
 *
 * postEvent와 달리 sendEvent함수는 그 즉시 widget에게 event를 전달한다.\n
 * postEvent와 sendEvent의 차이는 postEvent함수 설명 참조
 *
 * PD::KeyEvent evt(PD::Event::KeyPress, SDLK_UP);
 * theApp->postEvent(&evt);
 *
 * \param w event를 받을 widget 포인터
 * \param evt event
 *
 * \sa postEvent()
 */
bool App::sendEvent(Widget* w, Event* evt)
{
	if (w == 0) return false;
	if (w && w->isClosing() && 
		evt->msg() != Event::Close)
	{
		//printf("App::sendEvent name:%s isClosing\n", w->name());
		return false;
	}

	w->event(evt);
	return false;
}

/**
 * \brief 이벤트 queue에 남아있던 모든 이벤트를 비운다.
 */
void App::flushEvent()
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) 
	{
		//printf("App::flushEvent delete event\n");
	}
}

/**
 * \brief 특정 widget의 이벤트 queue를 지운다.
 *
 * \param widget 지우고자 하는 widget포인터
 */
void App::removeEvent(Widget* widget)
{
	MutexLocker ml(&theApp->eventListMutex());
	if (theApp->eventList().size() == 0) return;


	EventList& list = theApp->eventList();
	EventListIt it = list.begin();
	while (it != list.end())
	{
		Event* evt = *it;
		//printf("App::removeEvent name:%s msg:%d\n", 
		//	evt->widget()->name(), evt->msg());
		if (evt->widget() == widget)
		{
			//printf("App::removeEvent name:%s\n", evt->widget()->name());
			list.erase(it++);
		}
		else
			it++;
	}
}

/**
 * \brief 이벤트 queue의 이벤트들을 처리한다.(내부처리용)
 */
void App::processEvent()
{
	Event* evt = 0;
	SDL_Event sdlEvt;
	if (SDL_PollEvent(&sdlEvt)) AppPrivate::convertSDLEvent(sdlEvt);

	{
		MutexLocker ml(&theApp->eventListMutex());
		if (theApp->eventList().size() == 0) { return; }

		evt = theApp->eventList().front();
		theApp->eventList().pop_front();
	}
	if (evt == 0) return;

	//printf("App::processEvent name:%s msg:%d...1\n", 
	//	evt->widget()->name(), evt->msg());

	if (theApp->eventFilter() &&
		theApp->eventFilter()->filter(evt))
	{
		delete evt;
		return;
	}

	if (evt->widget() && !evt->widget()->isClosed()) 
		evt->widget()->event(evt);
		
	//printf("App::processEvent name:%s msg:%d...2\n", 
	//	evt->widget()->name(), evt->msg());
	delete evt;

}

/**
 * \brief 이벤트 loop
 *
 * \return true/false
 */
bool App::pollEvent()
{
	//printf("App::pollEvent start\n");
	while (!theApp->d->exitFlag)
	{
		processEvent();
		usleep(0);
	}
	//printf("App::pollEvent end\n");

	return false;
}

/**
 * \brief 프로그램 종료
 *
 * 프로그램을 종료하고 싶을때 호출한다.\n
 * retCode에 값을 넣으면 exec()가 종료될때 반환된다.
 *
 * \param retCode 종료코드
 */
void App::exit(int retCode)
{
	d->retCode = retCode;
	d->exitFlag = true;
}

/**
 * \brief 이벤트 loop
 *
 * \return 프로그램 종료코드
 */
int App::exec()
{
	flushEvent();
	pollEvent();
	return d->retCode;
}

} //namespace PD {

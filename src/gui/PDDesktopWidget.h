#ifndef _PDDESKTOPWIDGET_H_
#define _PDDESKTOPWIDGET_H_

#include <SDL.h>
#include "PDColor.h"
#include "PDWidget.h"

namespace PD {

class DesktopWidgetPrivate;

/**
 * \brief desktop widget
 * \ingroup gui
 */
class DesktopWidget
{
public:
	typedef std::list<Widget*>      WidgetList;
	typedef WidgetList::iterator    WidgetListIt;
	typedef WidgetList::reverse_iterator WidgetListReverseIt;

private:
	DesktopWidgetPrivate* d;

public:
	DesktopWidget();
	~DesktopWidget();

	SDL_Surface* surface();

	int width();
	int height();

	Uint32 rMask();
	Uint32 gMask();
	Uint32 bMask();
	Uint32 aMask();
	Uint8 bpp();

	int create(int w, int h, int bpp);
	void setBackground(const Color& rgb);
	void setBackground(int color);

	void addChild(Widget* w);
	void removeChild(Widget* w);
	Widget* findMouseWidget(const Point& pt);
	Widget* findChild(Widget* w);

	bool screenShot(const std::string& fn);

	void paintBg(Rect& r);
	void paintBg();

	void paintChild(Rect& r);
	void paintChild();

	void paint(Rect& r);
	void paint();

	Widget* nextMainWidget(Widget* w);

	WidgetList&	childList();
};

} //namespace PD {


#endif

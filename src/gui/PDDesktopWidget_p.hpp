#ifndef _PDDESKTOPWIDGET_P_H_
#define _PDDESKTOPWIDGET_P_H_

namespace PD {

class DesktopWidgetPrivate
{
public:
	SDL_Surface* surface;
	Color brushColor;

	DesktopWidget::WidgetList childList;

	int width;
	int height;
	Uint32 rMask;
	Uint32 gMask;
	Uint32 bMask;
	Uint32 aMask;
	Uint8 bpp;

public:
	DesktopWidgetPrivate()
	{
		surface = 0;
		brushColor = lightgray;

		rMask = 0;
		gMask = 0;
		bMask = 0;
		aMask = 0;
		bpp = 0;

		width = 0;
		height = 0;
	}

	~DesktopWidgetPrivate()
	{
		childList.clear();
	}
};


} //namespace PD 
#endif

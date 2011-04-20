#ifndef _PDWIDGET_P_H_
#define _PDWIDGET_P_H_

namespace PD {

class WidgetPrivate
{
public:
	Widget::WidgetList childList;

	Widget* parent;
	int	result;
	Uint32 style;
	std::string	name;

	bool mousePressDown;

	bool closed;
	bool closing;

	bool popup;
	bool modal;

	BgMode bgMode;

	Rect geometry;
	SDL_Surface* surface;

	Image* bgImage;

	Font* font;

	FocusPolicy	focusPolicy;
	bool hasFocus;
	bool visible;

	bool mouseInOutEvent;

	Palette palette;
	WidgetKeyMover keyMover;
	bool disable;

	Color	maskColor;
	bool maskColorFlag;

public:
	WidgetPrivate(Widget* _parent, const char* _name, Uint32 _style)
	{
		closed = false;
		closing = false;
		mousePressDown = false;

		popup = false;
		modal = false;
		bgImage = 0;
		result = 0;
		disable = false;
		maskColorFlag = false;

		font = 0;

		bgMode = FillBg;

		geometry = Rect(0,0,0,0);
		parent = _parent;
		if (_name && strlen(_name) > 0) name = _name;
		else name = "noName";
		style = _style;
		surface = NULL;

		focusPolicy = StrongFocus;
		hasFocus = false;
		visible = false;
		mouseInOutEvent = false;
	}

	~WidgetPrivate()
	{
		childList.clear();

		if (bgImage) { delete bgImage; bgImage = 0; }
		if (surface) { SDL_FreeSurface(surface); surface = NULL; }
	}


};
} //namespace PD {
#endif

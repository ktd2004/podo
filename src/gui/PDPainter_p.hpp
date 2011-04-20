#ifndef _PDPAINTER_P_H_
#define _PDPAINTER_P_H_

namespace PD {

class PainterPrivate
{
public:
	Widget* widget;
	Color penColor;
	Color brushColor;

	Color savedPenColor;
	Color savedBrushColor;

public:
	PainterPrivate(Widget* _widget)
	{
		widget = _widget;

		penColor = widget->palette().color(Palette::Text);
		savedPenColor = widget->palette().color(Palette::Text);
		brushColor = widget->palette().color(Palette::Background);
		savedBrushColor = widget->palette().color(Palette::Background);
	}
};
} //namespace PD {
#endif

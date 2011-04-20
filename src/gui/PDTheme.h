#ifndef _PDTHEME_H_
#define _PDTHEME_H_

#include "PDPalette.h"

namespace PD {

class ThemePrivate;

/**
 * \brief 
 * \ingroup gui
 */
class Theme
{
public:
	enum Control
	{
		Widget=0,
		Button,
		CalendarUI,
		CheckBox,
		ComboBox,
		DateTimeEdit,
		IpAddrEdit,
		Label,
		LineEdit,
		ListBox,
		PopupMenu,
		Progress,
		Slider,
		SpinBox,
		TableWidget,
		TableWidgetItem,
		ScrollBar,
		MaxControl
	};
private:
	ThemePrivate* d;

public:
	Theme();

	Palette* palette(Control c);
	void setPalette(Control c, Palette& pal);
};

} // namespace PD

#endif

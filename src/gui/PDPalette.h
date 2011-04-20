#ifndef _PDPALETTE_H_
#define _PDPALETTE_H_

#include "PDColor.h"

namespace PD {

/**
 * \brief
 * \ingroup gui
 */
class Palette
{
public:
	enum ColorRole 
	{
		Background = 0,
		Highlight,
		Text,
		HighlightText,
		FocusColor,
		LightColor,
		DarkColor,
		MaxColorRole
	};

	enum State
	{ 
		Enable=0,
		Disable,
		MaxState,
	};

private:
	Color m_palette[Palette::MaxColorRole][Palette::MaxState];

public:
	Palette();
	Palette(Palette& c);
	~Palette();

	Color color(ColorRole, State s=Enable);
	void setColor(ColorRole role, Color c, State s=Enable);

	Palette& operator=(Palette& c);
	int operator==(Palette& c);
	int operator!=(Palette& c);
};

} // namespace PD

#endif

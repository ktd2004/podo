#ifndef _PDTHEME_P_H_
#define _PDTHEME_P_H_

namespace PD {

class ThemePrivate
{
public:
	Palette* palette[Theme::MaxControl];

public:
	ThemePrivate()
	{
		for (int i=0; i<Theme::MaxControl; i++)
		{
			palette[i] = 0;
		}
	}
};

} //namespace PD {
#endif


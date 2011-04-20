#include "PDTheme.h"
#include "PDTheme_p.hpp"

namespace PD {

Theme::Theme()
{
	d = new ThemePrivate;
}

Palette* Theme::palette(Control c)
{
	if (d->palette[c] == 0)
		d->palette[c] = new Palette;
	return d->palette[c];
}

void Theme::setPalette(Control c, Palette& pal)
{
	if (d->palette[c]) delete d->palette[c];

	d->palette[c] = new Palette(pal);
}

} //namespace PD {


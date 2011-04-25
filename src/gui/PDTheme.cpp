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


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
#include "PDSkin.h"
#include <map>
#include <string>
#include <assert.h>

#include "PDApp.h"
#include "PDGlobal.h"

#include "PDButton.h"
#include "PDLabel.h"
#include "PDCheckBox.h"

#include "../base/PDIniFile.h"
#include "PDSkin_p.hpp"

namespace PD {

Skin::Skin(Widget* parent)
{
	d = new SkinPrivate(parent);
}

Skin::~Skin()
{
	delete d;
}
	
void Skin::setParent(Widget* parent)
{
	d->parent = parent;
}

int Skin::load(const char* fileName)
{
	int ret = d->iniFile.read(fileName);
	if (ret == -1)
	{
		printf("Skin::load failed to open '%s'\n", fileName);
		return -1;
	}

	d->initControl(this);
	d->initKeyMover(this);

	return 0;
}

Widget* Skin::control(std::string v)
{
	Widget *w = d->controlMap[v];
	return w;
}

Image* Skin::image(std::string v)
{
	Image* i = d->imageMap[v];
	if (i == NULL) return NULL;

	return i;
}

Palette* Skin::palette(std::string v)
{
	return d->paletteMap[v];
}

} //namespace PD {

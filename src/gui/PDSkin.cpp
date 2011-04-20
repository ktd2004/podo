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

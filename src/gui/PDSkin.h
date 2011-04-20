#ifndef _PDSKIN_H_
#define _PDSKIN_H_

#include "PDWidget.h"

namespace PD
{

class SkinPrivate;

/**
 * \brief
 * \ingroup gui
 */
class Skin
{
	friend class SkinPrivate;

private:
	SkinPrivate* d;

public:
	Skin(Widget* parent);
	virtual ~Skin();
	
	void setParent(Widget* parent);
	int load(const char* fileName);
	Widget* control(std::string v);
	Image* image(std::string v);
	Palette* palette(std::string v);

protected:
	virtual void initCustom(std::string /*grp*/) {};
};

}

#endif

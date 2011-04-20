#include "PDLabel.h"
#include "PDPainter.h"
#include "../base/PDString.h"
#include <assert.h>
#include "PDLabel_p.hpp"

namespace PD {

Label::Label(Widget* parent, const char* name/*=0*/) : 
	Widget(parent, name, 0, Theme::Label)
{
	d = new LabelPrivate;

	setFocusPolicy(NoFocus);
	setFocus(false);
}

Label::Label(Widget* parent, const char* name, const char* text) : 
	Widget(parent, name, 0, Theme::Label)
{
	d = new LabelPrivate;

	setText(text);
	setFocusPolicy(NoFocus);
	setFocus(false);
}

Label::~Label()
{
	delete d;
}

std::string Label::text()
{
	return d->text;
}

void Label::setText(const std::string& text)
{
	d->text = text;
}

bool Label::border()
{
	return d->border;
}

void Label::setBorder(bool f)
{
	d->border = f;
}

int Label::alignment()
{
	return d->alignment;
}

void Label::setAlignment(int align)
{
	d->alignment = align;
}

void Label::setMargin(unsigned int margin ) { d->margin = margin; };
unsigned int Label::margin() { return d->margin; };

void Label::paintEvent(PaintEvent*)
{
	Painter p(this);

	String::StringList list = String::split(d->text, "\n");

	int marginX = d->margin;
	int marginY = 0;
	int y = marginY;
	int w = width();
	int h = height();
	if (list.size() > 1) h /=list.size() ;

	if (bgMode() == FillBg)
	{
		if (background())
		{
			p.drawImage(0, 0, *background());
		}
		else
		{
			p.setBrushColor(palette().color(Palette::Background));
			p.fillRect(Rect(0, 0, width(), height()));
		}
	}


	if (d->border) p.drawRect(0, 0, width(), height());

	for (size_t i=0; i<list.size(); i++)
	{
		p.setPenColor(palette().color(Palette::Text));
		if( (alignment() == PD::AlignVCenter) || 
			(alignment() == PD::AlignLeft) )
			marginX = d->margin;
		else
			marginX = 0;
		
		p.drawText(Rect(marginX, y, w, h),
				list[i].c_str(), (PD::Alignment)alignment() );

		y += h + marginY;
	}

	if (bgMode() != FillBg)
	{
		SDL_SetColorKey(surface(), SDL_SRCCOLORKEY, 
			SDL_MapRGB(surface()->format, 
			palette().color(Palette::Background).r, 
			palette().color(Palette::Background).g, 
			palette().color(Palette::Background).b));
	}
}

} //namespace PD {

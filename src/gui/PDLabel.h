#ifndef _PDLABEL_H_
#define _PDLABEL_H_

#include "PDWidget.h"

namespace PD {

class LabelPrivate;

/**
 * \brief
 * \ingroup gui
 */
class Label : public Widget
{
private:
	LabelPrivate* d;

public:
						Label(Widget* parent, const char* name=0);
						Label(Widget* parent, const char* name, 
							const char* text);
						~Label();

	std::string			text();
	void				setText(const std::string& text);

	bool				border();
	void 				setBorder(bool f);

	int					alignment();
	void				setAlignment(int align);

	void				setMargin(unsigned int margin);
	unsigned int		margin();

protected:
	virtual void 		paintEvent(PaintEvent*);
};

} //namespace PD {

#endif

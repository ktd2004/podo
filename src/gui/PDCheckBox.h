#ifndef _PDCHECKBOX_H_
#define _PDCHECKBOX_H_

#include "PDWidget.h"
#include "PDPainter.h"

namespace PD {

class CheckBoxPrivate;

/**
 * \brief checkbox
 * \ingroup gui
 */
class CheckBox : public Widget
{
public:
	enum CheckStyle { CheckV =0, CheckRect };

private:
	CheckBoxPrivate* d;

public:
	CheckBox(Widget* parent, const char* name=0);
	~CheckBox();

	void setCheckFlag(bool flag);
	bool checkFlag();

	void setCheckStyle(CheckStyle s);

	void setText(const char* text);
	std::string text();

	sigslot::signal1<bool>	changeState;	
	sigslot::signal2<CheckBox*, bool>	changeStateWithWidget;	

protected:
	void paintEvent(PaintEvent*);
	bool keyReleaseEvent(KeyEvent* evt);
	void mouseReleaseEvent(MouseEvent* evt);
	bool focusInEvent(FocusInEvent*);
	bool focusOutEvent(FocusOutEvent*);
};

} //namespace PD {

#endif

#ifndef _STATUSBAR_H_
#define _STATUSBAR_H_

#include <gui/PDWidget.h>
#include <gui/PDButton.h>
#include <gui/PDLabel.h>
#include <gui/PDTimer.h>

class StatusBar : public PD::Widget
{
private:
	PD::Button* m_menuBtn;

	PD::Button* m_layout1x1Btn;
	PD::Button* m_layout2x2Btn;
	PD::Button* m_layout3x3Btn;
	PD::Button* m_layout4x4Btn;

	PD::Label* m_timeLabel;

	PD::Timer* m_timer;

public:
	StatusBar(PD::Widget* parent);
	~StatusBar();

	PD::Button* menuBtn() { return m_menuBtn; }

	PD::Button* layout1x1Btn() { return m_layout1x1Btn; }
	PD::Button* layout2x2Btn() { return m_layout2x2Btn; }
	PD::Button* layout3x3Btn() { return m_layout3x3Btn; }
	PD::Button* layout4x4Btn() { return m_layout4x4Btn; }

private:
	void timeout();
};

#endif

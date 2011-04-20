#ifndef _MENUFRM_H_
#define _MENUFRM_H_

#include <gui/PDWidget.h>
#include <gui/PDLabel.h>

class Button;

class MenuFrm : public PD::Widget
{
private:
	PD::Button* m_cameraBtn;
	PD::Button* m_recordBtn;
	PD::Button* m_searchBtn;
	PD::Button* m_systemBtn;

	PD::Label* m_cameraLabel;
	PD::Label* m_recordLabel;
	PD::Label* m_searchLabel;
	PD::Label* m_systemLabel;

	PD::Button* m_okBtn;
	PD::Button* m_cancelBtn;

public:
	MenuFrm(PD::Widget* parent);
	~MenuFrm();

private:
	void clickedOk(PD::Button*);
	void clickedCancel(PD::Button*);

	void clickedCamera(PD::Button*);
	void clickedRecord(PD::Button*);
	void clickedSearch(PD::Button*);
	void clickedSystem(PD::Button*);
};

#endif

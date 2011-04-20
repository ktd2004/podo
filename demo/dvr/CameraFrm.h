#ifndef _CAMERAFRM_H_
#define _CAMERAFRM_H_

#include <gui/PDWidget.h>
#include <gui/PDLabel.h>
#include <gui/PDTableWidget.h>

class Button;

class CameraFrm : public PD::Widget
{
private:
	PD::Label* m_titleLabel;

	PD::TableWidget* m_table;

	PD::Button* m_okBtn;
	PD::Button* m_cancelBtn;

public:
	CameraFrm(PD::Widget* parent);
	~CameraFrm();

private:
	void initTitle();
	void initTable();
	void initOkCancel();

	void clickedOk(PD::Button*);
	void clickedCancel(PD::Button*);
};

#endif

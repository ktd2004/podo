#include "MenuFrm.h"
#include <gui/PDButton.h>
#include "CameraFrm.h"

MenuFrm::MenuFrm(PD::Widget* parent) : PD::Widget(parent, "MenuFrm")
{
	PD::Color bgColor(16, 64, 104);
	palette().setColor(PD::Palette::Background, bgColor);

	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	int wMargin = 40;

	x = 80; y = 100; w = 128; h = 128;
	m_cameraBtn = new PD::Button(this, "CameraBtn");
	m_cameraBtn->clicked.connect(this, &MenuFrm::clickedCamera);
	m_cameraBtn->setBackground("./images/camera.png");
	m_cameraBtn->setFocusBg("./images/camera.png");
	m_cameraBtn->palette().setColor(PD::Palette::Background, bgColor);
	m_cameraBtn->setGeometry(x, y, w, h);
	m_cameraBtn->show();
	x += w+wMargin;


	m_recordBtn = new PD::Button(this, "RecordBtn");
	m_recordBtn->clicked.connect(this, &MenuFrm::clickedRecord);
	m_recordBtn->setBackground("./images/record.png");
	m_recordBtn->setFocusBg("./images/record.png");
	m_recordBtn->palette().setColor(PD::Palette::Background, bgColor);
	m_recordBtn->setGeometry(x, y, w, h);
	m_recordBtn->show();
	x += w+wMargin;

	m_searchBtn = new PD::Button(this, "SearchBtn");
	m_searchBtn->clicked.connect(this, &MenuFrm::clickedSearch);
	m_searchBtn->setBackground("./images/search.png");
	m_searchBtn->setFocusBg("./images/search.png");
	m_searchBtn->palette().setColor(PD::Palette::Background, bgColor);
	m_searchBtn->setGeometry(x, y, w, h);
	m_searchBtn->show();
	x += w+wMargin;
	
	m_systemBtn = new PD::Button(this, "SystemBtn");
	m_systemBtn->clicked.connect(this, &MenuFrm::clickedSystem);
	m_systemBtn->setBackground("./images/system.png");
	m_systemBtn->setFocusBg("./images/system.png");
	m_systemBtn->palette().setColor(PD::Palette::Background, bgColor);
	m_systemBtn->setGeometry(x, y, w, h);
	m_systemBtn->show();
	x += w+wMargin;


	x = 80; y = 100 + h + 5; w = 128; h = 20;
	m_cameraLabel = new PD::Label(this, "CameraLabel", "Camera");
	m_cameraLabel->setAlignment(PD::AlignCenter);
	m_cameraLabel->palette().setColor(PD::Palette::Text, PD::white);
	m_cameraLabel->palette().setColor(PD::Palette::Background, bgColor);
	m_cameraLabel->setGeometry(x, y, w, h);
	m_cameraLabel->show();
	x += w+wMargin;

	m_recordLabel = new PD::Label(this, "RecordLabel", "Record");
	m_recordLabel->setAlignment(PD::AlignCenter);
	m_recordLabel->palette().setColor(PD::Palette::Text, PD::white);
	m_recordLabel->palette().setColor(PD::Palette::Background, bgColor);
	m_recordLabel->setGeometry(x, y, w, h);
	m_recordLabel->show();
	x += w+wMargin;

	m_searchLabel = new PD::Label(this, "SearchLabel", "Search");
	m_searchLabel->setAlignment(PD::AlignCenter);
	m_searchLabel->palette().setColor(PD::Palette::Text, PD::white);
	m_searchLabel->palette().setColor(PD::Palette::Background, bgColor);
	m_searchLabel->setGeometry(x, y, w, h);
	m_searchLabel->show();
	x += w+wMargin;

	m_systemLabel = new PD::Label(this, "SystemLabel", "System");
	m_systemLabel->setAlignment(PD::AlignCenter);
	m_systemLabel->palette().setColor(PD::Palette::Text, PD::white);
	m_systemLabel->palette().setColor(PD::Palette::Background, bgColor);
	m_systemLabel->setGeometry(x, y, w, h);
	m_systemLabel->show();
	x += w+wMargin;




	m_okBtn = new PD::Button(this, "OkBtn", "OK");
	m_okBtn->clicked.connect(this, &MenuFrm::clickedOk);
	m_okBtn->setGeometry(550, 350, 80, 30);
	m_okBtn->show();

	m_cancelBtn = new PD::Button(this, "CancelBtn", "Cancel");
	m_cancelBtn->clicked.connect(this, &MenuFrm::clickedCancel);
	m_cancelBtn->setGeometry(650, 350, 80, 30);
	m_cancelBtn->show();
}

MenuFrm::~MenuFrm()
{
	if (m_okBtn) delete m_okBtn;
	if (m_cancelBtn) delete m_cancelBtn;

	if (m_cameraLabel) delete m_cameraLabel;
	if (m_recordLabel) delete m_recordLabel;
	if (m_searchLabel) delete m_searchLabel;
	if (m_systemLabel) delete m_systemLabel;

	if (m_cameraBtn) delete m_cameraBtn;
	if (m_recordBtn) delete m_recordBtn;
	if (m_searchBtn) delete m_searchBtn;
	if (m_systemBtn) delete m_systemBtn;
}

void MenuFrm::clickedOk(PD::Button*)
{
	close(0);
}

void MenuFrm::clickedCancel(PD::Button*)
{
	close(-1);
}

void MenuFrm::clickedCamera(PD::Button*)
{
	printf("MenuFrm::clickedCamera\n");
	CameraFrm frm(0);
	frm.center(800, 600);
	frm.exec();
}

void MenuFrm::clickedRecord(PD::Button*)
{
	printf("MenuFrm::clickedRecord\n");
}

void MenuFrm::clickedSearch(PD::Button*)
{
	printf("MenuFrm::clickedSearch\n");
}

void MenuFrm::clickedSystem(PD::Button*)
{
	printf("MenuFrm::clickedSystem\n");
}

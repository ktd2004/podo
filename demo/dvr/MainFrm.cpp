#include "MainFrm.h"
#include "MenuFrm.h"
#include <gui/PDApp.h>

MainFrm::MainFrm(Widget* parent) : Widget(parent, "MainFrm") 
{
	m_screen = new Screen(this);
	m_screen->show();

	m_statusBar = new StatusBar(this);
	m_statusBar->menuBtn()->clicked.connect(this, 
		&MainFrm::clickedMenu);

	m_statusBar->layout1x1Btn()->clicked.connect(this, 
		&MainFrm::clickedLayout1x1);
	m_statusBar->layout2x2Btn()->clicked.connect(this, 
		&MainFrm::clickedLayout2x2);
	m_statusBar->layout3x3Btn()->clicked.connect(this, 
		&MainFrm::clickedLayout3x3);
	m_statusBar->layout4x4Btn()->clicked.connect(this, 
		&MainFrm::clickedLayout4x4);
	m_statusBar->show();
}

MainFrm::~MainFrm()
{
	delete m_screen;
	delete m_statusBar;
}

void MainFrm::showEvent()
{
	m_screen->setGeometry(0, 0, width(), height());
	m_statusBar->setGeometry(0, height()-40, width(), 40);
}

bool MainFrm::keyPressEvent(PD::KeyEvent* evt)
{
	printf("MainFrm::keyPressEvent\n");

	if (evt->key() == SDLK_m)
	{
		clickedMenu(0);
		return true;	
	}
	else if (evt->key() == SDLK_UP || 
			 evt->key() == SDLK_RIGHT ||
			 evt->key() == SDLK_DOWN ||
			 evt->key() == SDLK_LEFT)
	{
		PD::KeyEvent keyEvt(PD::Event::KeyPress, evt->key());
		PD::theApp->sendEvent(m_screen, &keyEvt);
		return true;
	}

	return false;
}

void MainFrm::clickedMenu(PD::Button*)
{
	MenuFrm menuFrm(this);
	menuFrm.center(800, 400);
	menuFrm.exec();
}

void MainFrm::clickedLayout1x1(PD::Button*)
{
	m_screen->setLayout(Screen::Layout_1x1);
}

void MainFrm::clickedLayout2x2(PD::Button*)
{
	m_screen->setLayout(Screen::Layout_2x2);
}

void MainFrm::clickedLayout3x3(PD::Button*)
{
	m_screen->setLayout(Screen::Layout_3x3);
}

void MainFrm::clickedLayout4x4(PD::Button*)
{
	m_screen->setLayout(Screen::Layout_4x4);
}


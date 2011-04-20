#include "Launcher.h"

Launcher::Launcher(Widget* parent) : Widget(parent) 
{
	palette().setColor(PD::Palette::Background, PD::black);
	m_bgImg = new PD::Image("./images/indicator/Launcher_bg.png");
}

Launcher::~Launcher()
{
	if (m_bgImg) delete m_bgImg;
}

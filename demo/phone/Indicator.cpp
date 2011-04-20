#include "Indicator.h"
#include <gui/PDPainter.h>

Indicator::Indicator(Widget* parent) : Widget(parent) 
{
	m_bgImg = new PD::Image("./images/indicator_bg.png");

	m_signalImg = new PD::Image("./images/signal.png");
	m_batteryImg = new PD::Image("./images/battery.png");
}

Indicator::~Indicator()
{
	if (m_bgImg) delete m_bgImg;

	if (m_signalImg) delete m_signalImg;
	if (m_batteryImg) delete m_batteryImg;
}

void Indicator::paintEvent(PD::PaintEvent*)
{
	PD::Painter p(this);

	p.fillRect(0, 0, width(), height(), PD::black);

	int x = 0;
	int y = 2;
	int w = 21;
	int wMargin = 5;

	p.drawImage(x, y, *m_bgImg);

	p.drawImage(x, y, *m_signalImg); x += w + wMargin;

	p.setPenColor(PD::white);
	p.drawText(x+10, y+3, "PODO");

	p.drawImage(x+110, y, *m_batteryImg);
}


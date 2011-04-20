#include <gui/PDApp.h>
#include <gui/PDWidget.h>
#include <gui/PDPainter.h>

class MainFrm : public PD::Widget
{
public:	
	MainFrm() : Widget() 
	{
	}

protected:
	void paintEvent(PD::PaintEvent*)
	{
		PD::Painter p(this);
		p.fillRect(0, 0, width(), height());
		p.drawRect(0, 0, width(), height());
		p.drawHLine(10, 10, width()-10, 10);
		p.drawVLine(10, 15, 10, height()-30);
		p.drawRect(5, 5, width()-5, height()-5);
	}

protected:
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(400, 200);

	MainFrm m;
	m.setGeometry(0, 0, 400, 200);
	m.show();

	return app.exec();
}

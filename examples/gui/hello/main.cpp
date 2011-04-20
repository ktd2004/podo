#include <gui/PDApp.h>
#include <gui/PDWidget.h>
#include <gui/PDPainter.h>

class hello : public PD::Widget
{
public:

public:	
	hello(Widget* parent) : Widget(parent) 
	{
	}

protected:
	void paintEvent(PD::PaintEvent*)
	{
		PD::Painter p(this);
		p.fillRect(0, 0, width(), height(), PD::blue );
		p.fillRect(10, 10, 280, 60);

		p.drawText(10, 10, "Hello PODO");
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(300, 80);

	hello h(NULL);
	h.setGeometry(0, 0, 300, 80);
	h.show();

	return app.exec();
}

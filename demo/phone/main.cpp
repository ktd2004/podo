#include <gui/PDApp.h>
#include "MainFrm.h"

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(176, 220);

	MainFrm m(NULL);
	m.setGeometry(0, 0, 176, 220);
	m.show();

	return app.exec();
}

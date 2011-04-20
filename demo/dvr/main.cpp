#include <gui/PDApp.h>
#include "MainFrm.h"

int main(int /*argc*/, char** /*argv*/)
{
	PD::App app(1024, 768);
	app.setFontName("VeraBd.ttf");

	PD::Theme theme;

	// tableWidget
	theme.palette(PD::Theme::TableWidget)->setColor(
		PD::Palette::Background, PD::Color(16, 64, 104));
	theme.palette(PD::Theme::TableWidget)->setColor(
		PD::Palette::Text, PD::white);

	// tableWidgetItem
	theme.palette(PD::Theme::TableWidgetItem)->setColor(
		PD::Palette::Background, PD::Color(16, 64, 104));
	theme.palette(PD::Theme::TableWidgetItem)->setColor(
		PD::Palette::Text, PD::white);
	theme.palette(PD::Theme::TableWidgetItem)->setColor(
		PD::Palette::Highlight, PD::Color(16, 64, 104));
	theme.palette(PD::Theme::TableWidgetItem)->setColor(
		PD::Palette::HighlightText, PD::yellow);
	theme.palette(PD::Theme::TableWidgetItem)->setColor(
		PD::Palette::Background, PD::Color(166, 198, 236), PD::Palette::Disable);
	theme.palette(PD::Theme::TableWidgetItem)->setColor(
		PD::Palette::Text, PD::gray, PD::Palette::Disable);

	app.setTheme(&theme);

	MainFrm m(NULL);
	m.setGeometry(0, 0, 1024, 768);
	m.show();

	return app.exec();
}

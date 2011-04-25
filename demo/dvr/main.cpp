/* 
   Copyright 2011 PODO. 
   This file is part of PODO. 
   
   PODO is free software: you can redistribute it and/or modify 
   it under the terms of the GNU Lesser General Public License as  
   published by the Free Software Foundation, either version 3 of  
   the License, or (at your option) any later version. 
   
   PODO is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of 
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU Lesser General Public License for more details. 
   
   You should have received a copy of the GNU Lesser General Public  
   License along with PODO. If not, see <http://www.gnu.org/licenses/>. 
 */
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

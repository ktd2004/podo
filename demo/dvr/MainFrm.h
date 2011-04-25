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
#ifndef _MAINFRM_H_
#define _MAINFRM_H_

#include <gui/PDWidget.h>
#include "Screen.h"
#include "StatusBar.h"

class MainFrm : public PD::Widget
{
private:
	Screen* m_screen;
	StatusBar* m_statusBar;

public:
	MainFrm(PD::Widget* parent);
	~MainFrm();

protected:
	void showEvent();
	bool keyPressEvent(PD::KeyEvent* evt);

private:
	void clickedMenu(PD::Button*);
	void clickedLayout1x1(PD::Button*);
	void clickedLayout2x2(PD::Button*);
	void clickedLayout3x3(PD::Button*);
	void clickedLayout4x4(PD::Button*);
};

#endif //#define _MAINFRM_H_

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
#ifndef _MENUFRM_H_
#define _MENUFRM_H_

#include <gui/PDWidget.h>
#include <gui/PDLabel.h>

class Button;

class MenuFrm : public PD::Widget
{
private:
	PD::Button* m_cameraBtn;
	PD::Button* m_recordBtn;
	PD::Button* m_searchBtn;
	PD::Button* m_systemBtn;

	PD::Label* m_cameraLabel;
	PD::Label* m_recordLabel;
	PD::Label* m_searchLabel;
	PD::Label* m_systemLabel;

	PD::Button* m_okBtn;
	PD::Button* m_cancelBtn;

public:
	MenuFrm(PD::Widget* parent);
	~MenuFrm();

private:
	void clickedOk(PD::Button*);
	void clickedCancel(PD::Button*);

	void clickedCamera(PD::Button*);
	void clickedRecord(PD::Button*);
	void clickedSearch(PD::Button*);
	void clickedSystem(PD::Button*);
};

#endif

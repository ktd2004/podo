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
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <gui/PDWidget.h>
#include <gui/PDImage.h>
#include <gui/PDPopupMenu.h>


class Screen : public PD::Widget
{
public:
	enum Layout
	{
		Layout_1x1=1,
		Layout_2x2=2,
		Layout_3x3=3,
		Layout_4x4=4,
		Layout_Max=4
	};

private:
	std::string m_cameraName[Layout_Max*Layout_Max];
	bool m_showLogo[Layout_Max*Layout_Max];

	int m_baseChannel;
	Layout m_layout;

	int m_oldBaseChannel;
	Layout m_oldLayout;

	int m_maxChannel;

	PD::Color m_selectedColor;
	int m_selectedIndex;
	int m_oldRow;
	int m_oldColumn;

	bool m_hasBorderLine;
	bool m_isVisibleCameraName;
	bool m_isVisibleOSD;

    bool m_panic;

	PD::Image m_logoImage[4];

	PD::PopupMenu* m_popupMenu;

public:
	Screen(PD::Widget* parent);
	~Screen();

	int baseChannel();
	void setBaseChannel(int c);

	int maxChannel();
	void setMaxChannel(int c);


	Layout layout();
	void setLayout(Layout l, int baseChannel=0);

	const std::string& cameraName(int idx);
	void setCameraName(int idx, const std::string& name);

	void setShowLogo(int idx, bool f); 

	bool isVisibleCameraName();
	void showCameraName(bool f);

	bool hasBorderLine();
	void setBorderLine(bool f);

	bool isVisibleOSD();
	void showOSD(bool f);

	PD::Color selectedColor();
	void setSelectedColor(const PD::Color& color);

	int selectedIndex();
	void selectIndex(int idx);

    void setPanic(bool f) { m_panic = f; }
    bool panic() { return m_panic; }

	sigslot::signal1<int> clicked;

protected:
	void paintEvent(PD::PaintEvent*);

	void mousePressEvent(PD::MouseEvent*);

	bool keyPressEvent(PD::KeyEvent*);

private:
	void drawChannelArea(int idx, const PD::Rect& rect, PD::Painter* p);
	void clickedPopupMenu(int idx);
};

#endif

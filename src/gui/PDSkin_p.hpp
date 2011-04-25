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
#ifndef _PDSKIN_P_H_
#define _PDSKIN_P_H_

namespace PD {

typedef std::map<std::string, Widget*> ControlMap;
typedef std::map<std::string, Widget*>::iterator ControlMapIt;
typedef std::map<std::string, Image*> ImageMap;
typedef std::map<std::string, Image*>::iterator ImageMapIt;
typedef std::map<std::string, Palette*> PaletteMap;
typedef std::map<std::string, Palette*>::iterator PaletteMapIt;

class SkinPrivate
{
public:
	Widget *parent;
	IniFile iniFile;

	ControlMap controlMap;
	ImageMap imageMap;
	PaletteMap paletteMap;

public:
	SkinPrivate(Widget* _parent)
	{
		parent = _parent;
	}

	~SkinPrivate()
	{
		ControlMapIt itW = controlMap.begin();
		while(itW != controlMap.end())
		{
			Widget* w = (*itW).second;
			if (w) delete w;
			itW++;
		}

		ImageMapIt itI = imageMap.begin();
		while(itI != imageMap.end())
		{
			Image* i = (*itI).second;
			if (i) delete i;
			itI++;
		}

		PaletteMapIt itP = paletteMap.begin();
		while(itP != paletteMap.end())
		{
			Palette* p = (*itP).second;
			if (p) delete p;
			itP++;
		}
	}

	void initMain(Widget *widget, std::string grp)
	{
		assert(widget != 0);

		std::string value;

		// Geometry
		value = iniFile.readEntry(grp, "geometry");
		if ( !value.empty() ) setGeometry( widget, value );
		// BackgroundImage
		value = iniFile.readEntry(grp, "bgImg");
		if (	!value.empty() ) widget->setBackground(value.c_str());
		// BackgroundColor
		value = iniFile.readEntry(grp, "backgroundColor");
		if ( !value.empty() ) setPalette(widget, Palette::Background, value);
		// HighlightColor
		value = iniFile.readEntry(grp, "highlightColor");
		if ( !value.empty() ) setPalette(widget, Palette::Highlight, value);
		// TextColor
		value = iniFile.readEntry(grp, "textColor");
		if ( !value.empty() ) setPalette(widget, Palette::Text, value);
		// HighlightTextColor
		value = iniFile.readEntry(grp, "highlightTextColor");
		if ( !value.empty() ) setPalette(widget, Palette::HighlightText, value);
		// focusColor
		value = iniFile.readEntry(grp, "focusColor");
		if ( !value.empty() ) setPalette(widget, Palette::FocusColor, value);
		// lightColor
		value = iniFile.readEntry(grp, "lightColor");
		if ( !value.empty() ) setPalette(widget, Palette::LightColor, value);
		// darkColor
		value = iniFile.readEntry(grp, "darkColor");
		if ( !value.empty() ) setPalette(widget, Palette::DarkColor, value);

		// MaskColor
		value = iniFile.readEntry(grp, "maskColor");
		if ( !value.empty() ) 
		{
			int r, g, b, a;
			strToRgb(value, r, g, b, a);
			widget->setMaskColor(Color(r, g, b, a));
		}

		// Font, FontSize
		setFont(widget, iniFile.readEntry(grp,"font"),
				iniFile.readEntry(grp,"fontSize"));
		// Show
		value = iniFile.readEntry(grp, "show");
		if ( !value.empty() ) widget->show();

	}

	void initBtn(Button* btn, std::string grp)
	{
		assert(btn != 0);

		std::string value;

		// Geometry
		value = iniFile.readEntry(grp, "geometry");
		if ( !value.empty() ) setGeometry( (Widget*)btn, value );

		// BackgroundImageLeft
		value = iniFile.readEntry(grp, "bgImgLeft");
		if (	!value.empty() ) btn->setBackgroundLeft(value.c_str());
		// BackgroundImage
		value = iniFile.readEntry(grp, "bgImg");
		if (	!value.empty() ) btn->setBackground(value.c_str());
		// BackgroundImageRight
		value = iniFile.readEntry(grp, "bgImgRight");
		if (	!value.empty() ) btn->setBackgroundRight(value.c_str());

		// HoverImageLeft
		value = iniFile.readEntry(grp, "hoverImgLeft");
		if ( !value.empty() ) btn->setHoverBgLeft(value.c_str());
		// HoverImage
		value = iniFile.readEntry(grp, "hoverImg");
		if ( !value.empty() ) btn->setHoverBg(value.c_str());
		// HoverImageRight
		value = iniFile.readEntry(grp, "hoverImgRight");
		if ( !value.empty() ) btn->setHoverBgRight(value.c_str());

		// FocusImageLeft
		value = iniFile.readEntry(grp, "focusImgLeft");
		if ( !value.empty() ) btn->setFocusBgLeft(value.c_str());
		// FocusImage
		value = iniFile.readEntry(grp, "focusImg");
		if ( !value.empty() ) btn->setFocusBg(value.c_str());
		// FocusImageRight
		value = iniFile.readEntry(grp, "focusImgRight");
		if ( !value.empty() ) btn->setFocusBgRight(value.c_str());

		// DisabledBgLeft
		value = iniFile.readEntry(grp, "disabledImgLeft");
		if ( !value.empty() ) btn->setDisabledBgLeft(value.c_str());
		// DisabledBg
		value = iniFile.readEntry(grp, "disabledImg");
		if ( !value.empty() ) btn->setDisabledBg(value.c_str());
		// DisabledBgRight
		value = iniFile.readEntry(grp, "disabledImgRight");
		if ( !value.empty() ) btn->setDisabledBgRight(value.c_str());

		// TextColor
		value = iniFile.readEntry(grp, "textColor");
		if ( !value.empty() ) setPalette((Widget*)btn, Palette::Text, value);
		// HighlightTextColor
		value = iniFile.readEntry(grp, "highlightTextColor");
		if ( !value.empty() ) 
			setPalette((Widget*)btn, Palette::HighlightText, value);
		// BackgroundColor
		value = iniFile.readEntry(grp, "backgroundColor");
		if ( !value.empty() ) setPalette((Widget*)btn, Palette::Background, value);
		// HighlightColor
		value = iniFile.readEntry(grp, "highlightColor");
		if ( !value.empty() ) setPalette((Widget*)btn, Palette::Highlight, value);
		// MaskColor
		value = iniFile.readEntry(grp, "maskColor");
		if ( !value.empty() ) 
		{
			int r, g, b, a;
			strToRgb(value, r, g, b, a);
			btn->setMaskColor(Color(r, g, b, a));
		}
		// Alignment
		value = iniFile.readEntry(grp, "alignment");
		if ( !value.empty() ) btn->setAlignment(strToAlign(value));
		// ToggleButton
		value = iniFile.readEntry(grp, "toggleButton");
		if ( !value.empty() ) btn->setToggleButton(strToBool(value));
		// Font, FontSize
		setFont((Widget*)btn, iniFile.readEntry(grp,"font"),
				iniFile.readEntry(grp,"fontSize"));
		// Text
		value = iniFile.readEntry(grp, "text");
		if ( !value.empty() ) 
		{
			int spaceCnt = 0;
			if ( value[0] == '"' && value[value.length()-1] == '"')
			{
				value = String::mid(value, 1, value.length()-2);
				for(int i=0; i<(int)value.length(); i++)
				{
					if ( isspace(value[i]) ) spaceCnt++;
					else break;
				}
			}
			std::string langGrp = iniFile.readEntry(grp, "langGrp");
			if ( langGrp == "" )	btn->setText(value.c_str());
			else 
			{
				if ( spaceCnt > 0 )
				{
					value = String::trim(value);
					std::string temp;
					for(int i=0; i<spaceCnt; i++) temp += " ";
					temp += PD_TR(langGrp, value);
					btn->setText(temp.c_str());
				}
				else
					btn->setText(PD_TR(langGrp, value).c_str());
			}
		}
		// Show
		value = iniFile.readEntry(grp, "show");
		if ( !value.empty() ) btn->show();

		addControl( (Widget*)btn, grp);
	}

	void initLabel(Label* label, std::string grp)
	{
		assert(label != 0);

		std::string value;

		// Geometry
		value = iniFile.readEntry(grp, "geometry");
		if ( !value.empty() ) setGeometry( (Widget*)label, value );
		// BackgroundImage
		value = iniFile.readEntry(grp, "bgImg");
		if (	!value.empty() ) label->setBackground(value.c_str());
		// TextColor
		value = iniFile.readEntry(grp, "textColor");
		if ( !value.empty() ) setPalette((Widget*)label, Palette::Text, value);
		// BackgroundColor
		value = iniFile.readEntry(grp, "backgroundColor");
		if ( !value.empty() ) setPalette((Widget*)label, Palette::Background, value);
		// Margin
		value = iniFile.readEntry(grp, "margin");
		if ( !value.empty() ) label->setMargin((unsigned int)atoi(value.c_str()));
		// Alignment
		value = iniFile.readEntry(grp, "alignment");
		if ( !value.empty() ) label->setAlignment(strToAlign(value));
		// Font, FontSize
		setFont((Widget*)label, iniFile.readEntry(grp,"font"),
				iniFile.readEntry(grp,"fontSize"));
		// BGMode
		value = String::trim(iniFile.readEntry(grp, "bgMode"));
		if ( !value.empty() )
		{
			if ( value == "NoBg" ) label->setBgMode(NoBg);
			else label->setBgMode(ParentBg);
		}
		// Text
		value = iniFile.readEntry(grp, "text");
		if ( !value.empty() ) 
		{
			std::string langGrp = iniFile.readEntry(grp, "langGrp");
			if ( langGrp == "" )	label->setText(value.c_str());
			else label->setText(PD_TR(langGrp, value).c_str());
		}
		// Show
		value = iniFile.readEntry(grp, "show");
		if ( !value.empty() ) label->show();

		addControl( (Widget*)label, grp);
	}

	void initImage(Image* img, std::string grp)
	{
		assert(img != 0);

		std::string value;

		value = iniFile.readEntry(grp, "path");
		if (!img->load(value.c_str()) )
		{
			delete img;
			img = 0;
		}
		assert(img != 0);

		addImage(img, grp);
	}

	void initPalette(Palette* p, std::string grp)
	{
		std::string value;

		// textColor
		value = iniFile.readEntry(grp, "textColor");
		if ( !value.empty() ) setPalette(p, Palette::Text, value);
		// textColor_disable
		value = iniFile.readEntry(grp, "textColor_disable");
		if ( !value.empty() ) setPalette(p, Palette::Text, value, false);

		// highlightTextColor
		value = iniFile.readEntry(grp, "highlightTextColor");
		if ( !value.empty() ) setPalette(p, Palette::HighlightText, value);
		// highlightTextColor_disable
		value = iniFile.readEntry(grp, "highlightTextColor_disable");
		if ( !value.empty() ) setPalette(p, Palette::HighlightText, value, false);

		// focusColor
		value = iniFile.readEntry(grp, "focusColor");
		if ( !value.empty() ) setPalette(p, Palette::FocusColor, value);
		// focusColor_disable
		value = iniFile.readEntry(grp, "focusColor_disable");
		if ( !value.empty() ) setPalette(p, Palette::FocusColor, value, false);

		// backgroundColor
		value = iniFile.readEntry(grp, "backgroundColor");
		if ( !value.empty() ) setPalette(p, Palette::Background, value);
		// backgroundColor_disable
		value = iniFile.readEntry(grp, "backgroundColor_disable");
		if ( !value.empty() ) setPalette(p, Palette::Background, value, false);

		// highlightColor
		value = iniFile.readEntry(grp, "highlightColor");
		if ( !value.empty() ) setPalette(p, Palette::Highlight, value);
		// highlightColor_disable
		value = iniFile.readEntry(grp, "highlightColor_disable");
		if ( !value.empty() ) setPalette(p, Palette::Highlight, value, false);

		// lightColor
		value = iniFile.readEntry(grp, "lightColor");
		if ( !value.empty() ) setPalette(p, Palette::LightColor, value);
		// lightColor_disable
		value = iniFile.readEntry(grp, "lightColor_disable");
		if ( !value.empty() ) setPalette(p, Palette::LightColor, value, false);

		// darkColor
		value = iniFile.readEntry(grp, "darkColor");
		if ( !value.empty() ) setPalette(p, Palette::DarkColor, value);
		// darkColor_disable
		value = iniFile.readEntry(grp, "darkColor_disable");
		if ( !value.empty() ) setPalette(p, Palette::DarkColor, value, false);

		addPalette(p, grp);
	}

	void initCheckBox(CheckBox* c, std::string grp)
	{
		std::string value;

		// Geometry
		value = iniFile.readEntry(grp, "geometry");
		if ( !value.empty() ) setGeometry( (Widget*)c, value );
		// CheckFlag
		value = iniFile.readEntry(grp, "checkFlag");
		if ( !value.empty() ) c->setCheckFlag( strToBool(value) );
		// CheckStyle
		value = iniFile.readEntry(grp, "checkStyle");
		if ( !value.empty() ) 
		{
			PD::CheckBox::CheckStyle style = PD::CheckBox::CheckV;
			if ( String::trim(value) == "checkRect" ) 
				style = PD::CheckBox::CheckRect;
			c->setCheckStyle( style );
		}
		// TextColor
		value = iniFile.readEntry(grp, "textColor");
		if ( !value.empty() ) setPalette((Widget*)c, Palette::Text, value);
		// BackgroundColor
		value = iniFile.readEntry(grp, "backgroundColor");
		if ( !value.empty() ) setPalette((Widget*)c, Palette::Background, value);
		// Font, FontSize
		setFont((Widget*)c, iniFile.readEntry(grp,"font"),
				iniFile.readEntry(grp,"fontSize"));
		// Text
		value = iniFile.readEntry(grp, "text");
		if ( !value.empty() ) 
		{
			std::string langGrp = iniFile.readEntry(grp, "langGrp");
			if ( langGrp == "" )	c->setText(value.c_str());
			else c->setText(PD_TR(langGrp, value).c_str());
		}
		// Show
		value = iniFile.readEntry(grp, "show");
		if ( !value.empty() ) c->show();

		addControl( (Widget*)c, grp);
	}

	void initControl(Skin* skin)
	{
		std::string grp;
		String::StringList list = iniFile.readGroupList();
		for(int i=0; i<(int)list.size(); i++)
		{
			grp = String::trim(list[i]);
			std::string value = iniFile.readEntry(grp, "type" );
			if ( value == "Widget" ) initMain(parent, grp);
			else if ( value == "Button" ) 
			{
				Button *btn = new Button(parent, grp.c_str());
				initBtn(btn, grp);
			}
			else if ( value == "Label" ) 
			{
				Label *label = new Label(parent, grp.c_str());
				initLabel(label, grp);
			}
			else if ( value == "Image" )
			{
				Image* i = new Image();
				initImage(i, grp);
			}
			else if ( value == "Palette" )
			{
				Palette* p = new Palette();
				initPalette(p, grp);
			}
			else if ( value == "CheckBox" )
			{
				CheckBox* c = new CheckBox(parent, grp.c_str());
				initCheckBox(c, grp);
			}
			else if ( value == "Custom" ) skin->initCustom(grp);
			else 
			{
				printf("SkinPrivate::initControl unsupport '%s' type control\n",
						value.c_str());
			}
		}
	}


	void initKeyMover(Skin* skin)
	{
		std::string grp;
		String::StringList list = iniFile.readGroupList();
		for(int i=0; i<(int)list.size(); i++)
		{
			grp = String::trim(list[i]);
			std::string value = iniFile.readEntry(grp, "type" );
			std::string up, down, left, right;
			up = iniFile.readEntry(grp, "keyMoveUp" );
			down = iniFile.readEntry(grp, "keyMoveDown" );
			left = iniFile.readEntry(grp, "keyMoveLeft" );
			right = iniFile.readEntry(grp, "keyMoveRight" );

			if (up.empty() && down.empty() && left.empty() && right.empty())
				continue;

			Widget* w = skin->control(grp);
			if (w == 0)
			{
				printf("Skin::initKeyMover failed to find grp:'%s'\n",
						grp.c_str());
				printf("Skin::initKeyMover u:%s d:%s l:%s r:%s\n",
						up.c_str(), down.c_str(), left.c_str(), right.c_str());
				continue;
			}
			if ( !up.empty() )
			{
				w->keyMover().setUp(skin->control(up));
			}
			if ( !down.empty() )
			{
				w->keyMover().setDown(skin->control(down));
			}
			if ( !left.empty() )
			{
				w->keyMover().setLeft(skin->control(left));
			}
			if ( !right.empty() )
			{
				w->keyMover().setRight(skin->control(right));
			}
		}
	}

	void addControl(Widget* p, std::string grp)
	{
		assert(p != 0);

		controlMap[grp] = p;
	}

	void addImage(Image* i, std::string grp)
	{
		assert(i != 0);

		imageMap[grp] = i;
	}

	void addPalette(Palette* p, std::string grp)
	{
		paletteMap[grp] = p;
	}

	void setPalette(Palette* p, Palette::ColorRole role, 
			std::string v, bool enable=true)
	{
		Palette::State s = Palette::Enable;
		int r, g, b, a;
		strToRgb(v, r, g, b, a);
		if ( !enable ) s = Palette::Disable;

		p->setColor(role, Color(r, g, b, a), s);
	}

	void setPalette(Widget* w, Palette::ColorRole role, std::string v)
	{
		assert(w != 0);

		int r, g, b, a;
		strToRgb(v, r, g, b, a);
		w->palette().setColor(role, Color(r, g, b, a));
	}

	void setGeometry(Widget* w, std::string v)
	{
		assert(w != 0);

		String::StringList list;
		list = String::split(v, ",");
		w->setGeometry(atoi(list[0].c_str()), atoi(list[1].c_str()),
				atoi(list[2].c_str()), atoi(list[3].c_str()) );
	}

	void setFont(Widget* w, std::string f, std::string fs)
	{
		assert(w != 0);

		if ( f.empty() || fs.empty() ) return;

		if ( f == "default" && fs == "default" )
			w->setFont(w->font()->name(), w->font()->size());	
		else if ( f == "default" && fs != "default" )
			w->setFont(w->font()->name(), atoi(fs.c_str()) );	
		else if ( f != "default" && fs == "default" )
			w->setFont(f.c_str(), w->font()->size());	
		else
			w->setFont(f.c_str(), atoi(fs.c_str()));	
	}

	Alignment strToAlign(std::string align)
	{
		String::StringList list = String::split(align, ",");
		if ( list.size() == 0 ) return AlignCenter;

		int ret = 0;
		for(int i=0; i<(int)list.size(); i++)
		{
			std::string v = String::trim(list[i]);
			if ( v == "AlignLeft" ) ret |= AlignLeft;
			else if ( v == "AlignRight" ) ret |= AlignRight;
			else if ( v == "AlignHCenter" ) ret |= AlignHCenter;
			else if ( v == "AlignTop" ) ret |= AlignTop;
			else if ( v == "AlignBottom" ) ret |= AlignBottom;
			else if ( v == "AlignVCenter" ) ret |= AlignVCenter;
			else if ( v == "AlignCenter" ) ret |= AlignCenter;
		}
		return (Alignment)ret;
	}

	void strToRgb(std::string v, int& r, int& g, int &b, int &a)
	{
		String::StringList list;
		list = String::split(v, ",");
		r = atoi(list[0].c_str());
		g = atoi(list[1].c_str());
		b = atoi(list[2].c_str());
		if ( list.size() == 4 )
			a = atoi(list[3].c_str());
		else
			a = 0;
	}

	bool strToBool(std::string v)
	{
		if ( String::trim(v) == "true" ) return true;
		return false;
	}
};

} //namespace PD {
#endif

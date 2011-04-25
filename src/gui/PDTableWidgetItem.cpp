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
#include "PDTableWidgetItem.h"
#include "PDApp.h"
#include "PDArrowXpm.h"
#include "PDCheckXpm.h"
#include "../base/PDString.h"
#include <assert.h>
#include "PDTableWidgetItem_p.hpp"

namespace PD {

TableWidgetItem::TableWidgetItem(Widget* parent, int row, int col)
{
	d = new TableWidgetItemPrivate(parent, row, col);

	Theme* theme = theApp->theme();
	if (theme)
	{
		Palette* p = theme->palette(Theme::TableWidgetItem);
		if (p) setPalette(*p);
	}
}

TableWidgetItem::~TableWidgetItem()
{
	delete d;
}

void TableWidgetItem::setText(std::string text) 
{ 
	d->backupText = d->text;
	d->text = text; 
}
std::string& TableWidgetItem::text() { return d->text; }
std::string& TableWidgetItem::backupText() { return d->backupText; }

int TableWidgetItem::row() { return d->row; }
int TableWidgetItem::column() { return d->column; }

void TableWidgetItem::setSelectable(bool flag) { d->selectable = flag; }
bool TableWidgetItem::selectable() { return d->selectable; }

Palette& TableWidgetItem::palette() { return d->palette; }
void TableWidgetItem::setPalette(Palette p) { d->palette = p; }

Widget* TableWidgetItem::parent() { return d->parent; }


void TableWidgetItem::setGeometry(Rect r) { d->geometry = r; }
Rect TableWidgetItem::geometry() { return d->geometry; }

bool TableWidgetItem::hasFocus() { return d->hasFocus; }
void TableWidgetItem::setHasFocus(bool f) { d->hasFocus = f; }

void TableWidgetItem::setAlignment(int al) { d->alignment = al; }
int TableWidgetItem::alignment() { return d->alignment; }

const std::string& TableWidgetItem::fontName(){ return d->fontName; }
int TableWidgetItem::fontSize(){ return d->fontSize; }

void TableWidgetItem::redraw(bool highlight/*=false*/)
{
	Painter p(parent());
	drawItem(p, highlight);
}

void TableWidgetItem::drawText(Painter&p, Rect rect, const char* text)
{
	if ( text == NULL ) 
	{
		printf("TableWidgetItem::drawText text == NULL!\n");
		return;
	}

	std::string fontName;
	int fontSize = 0;

	if (p.parent() && !d->fontName.empty() && d->fontSize )
	{
		fontName = p.parent()->font()->name();
		fontSize = p.parent()->font()->size();
		p.parent()->setFont( d->fontName.c_str(), d->fontSize ); 
	}

	p.drawText(rect, text, alignment());

	if (p.parent() && !d->fontName.empty() && d->fontSize ) 
		p.parent()->setFont( fontName.c_str(), fontSize );
}

void TableWidgetItem::drawItem(Painter& p, bool highlight/*=false*/)
{
	Palette::State s = Palette::Enable;
	if ( !selectable() ) s = Palette::Disable;
		
	//printf("TableWidgetItem::drawItem r:%d c:%d text:%s\n", 
	//		row(), column(), text().c_str());
	
	if (highlight)
	{
		p.setBrushColor(palette().color(Palette::Highlight, s));
		p.setPenColor(palette().color(Palette::HighlightText, s));
	}
	else
	{
		p.setBrushColor(palette().color(Palette::Background, s));
		p.setPenColor(palette().color(Palette::Text, s));
	}

	p.fillRect(geometry(), palette().color(Palette::Background, s));

	Rect textRect(geometry().x()+2, geometry().y(),
		geometry().width()-2, geometry().height());
	
	drawText(p, textRect, text().c_str() );

	int w = geometry().width();
	int h = geometry().height();
	int x = geometry().x();
	int y = geometry().y();

	//printf("TableWidgetItem::drawItem x:%d y:%d w:%d h:%d\n",
	//	x, y, w, h);

	if (highlight)
	{
		p.setPenColor(palette().color(Palette::FocusColor, s ));

		p.setPenColor(  palette().color(Palette::FocusColor, s));
		p.drawRect(x, y, x+w-1, y+h-1);
	}
}


TableWidgetTextItem::TableWidgetTextItem(Widget* parent, int row, int col) :
	TableWidgetItem(parent, row, col)
{
}

TableWidgetTextItem::~TableWidgetTextItem()
{

}

TableWidgetLineEditItem::TableWidgetLineEditItem(PD::Widget* parent,
    int row, int col) : TableWidgetItem(parent, row, col)
{
    m_mode = Normal;
	m_maxLength = 0;
	m_min = -1;
	m_max = -1;
}

TableWidgetLineEditItem::~TableWidgetLineEditItem()
{
}

void TableWidgetLineEditItem::drawItem(PD::Painter& p, bool highlight)
{
	Palette::State s = Palette::Enable;
	if ( !selectable() ) s = Palette::Disable;

	//printf("TableWidgetLineEditItem::drawItem r:%d c:%d\n", row(), column());
	if (highlight)
	{
		p.setBrushColor(palette().color(PD::Palette::Highlight, s));
		p.setPenColor(palette().color(PD::Palette::HighlightText, s));
	}
	else
	{
		p.setBrushColor(palette().color(PD::Palette::Background, s));
		p.setPenColor(palette().color(PD::Palette::Text, s));
	}

	p.fillRect(geometry());

	if ( m_mode == Password)
	{
		std::string temp;

		if (m_maxLength)
		{
			if ( text().length() > static_cast<unsigned>(m_maxLength) )
				setText(PD::String::left(text(), m_maxLength));
		}
		else
		{
			setText(text());
		}

		for(size_t i=0; i<text().length(); i++)
			temp += "*";
		TableWidgetItem::drawText(p, geometry(), temp.c_str() );
	}
	else
	{
		if ( m_mode == Number )
		{
			if ( text().length() != 0 )
			{
				const char *temp = text().c_str();
				int ch = temp[text().length()-1];
				if ( isdigit(ch) == 0 )
				{
					setText(backupText());
					TableWidgetItem::drawText(p, geometry(), text().c_str() );
				}
				else
				{    		
					int value = atoi(text().c_str());
					if ( !(m_min == -1 && m_max == -1 ) )
					{
						if ( value >= m_min && value <= m_max )
						{
							TableWidgetItem::drawText(p, geometry(), 
									text().c_str() );
						}
						else
						{
							setText(backupText());
							TableWidgetItem::drawText(p, geometry(), 
									text().c_str() );
						}
					}
					else
					{
						TableWidgetItem::drawText(p, geometry(), 
								text().c_str() );
					}
				}
			}
		}
		else
		{
			TableWidgetItem::drawText(p, geometry(), text().c_str() );
		}
	}

	int w = geometry().width();
	int h = geometry().height();
	int x = geometry().x();
	int y = geometry().y();

	//printf("TableWidgetItem::drawItem x:%d y:%d w:%d h:%d\n",
	//  x, y, w, h);

	if (highlight)
	{
		p.setPenColor(palette().color(PD::Palette::FocusColor, s));

		p.setPenColor(  palette().color(PD::Palette::FocusColor, s));
		p.drawRect(x, y, x+w-1, y+h-1);
	}
}


TableWidgetComboItem::TableWidgetComboItem(PD::Widget* parent, int row, int col) :
    TableWidgetItem(parent, row, col)
{
}

TableWidgetComboItem::~TableWidgetComboItem()
{
}

void TableWidgetComboItem::addString(const char* text)
{
    m_list.push_back(text);
}

void TableWidgetComboItem::drawItem(PD::Painter& p, bool highlight/*=false*/)
{
	Palette::State s = Palette::Enable;
	if ( !selectable() ) s = Palette::Disable;

	if (highlight)
	{
		p.setBrushColor(palette().color(PD::Palette::Highlight, s));
		p.setPenColor(palette().color(PD::Palette::HighlightText, s));
	}
	else
	{
		p.setBrushColor(palette().color(PD::Palette::Background, s));
		p.setPenColor(palette().color(PD::Palette::Text, s));
	}

	p.fillRect(geometry());
	// draw combo select button
	//if (highlight)
	{
		PD::Image img;
		if (img.loadXpm(PD::arrow_down_xpm) )
		{
			PD::Rect xpmRect(geometry().x()+geometry().width() - 20, geometry().y(),
					geometry().height(), geometry().height());

			//printf("TableWidgetComboItem::drawItem..r:%d c:%d highlight:%d"
			//   " x:%d y:%d\n",
			//      row(), column(), highlight,
			//      xpmRect.x() + ((xpmRect.width()/2)-(img.width()/2)),
			//      xpmRect.y() + ((xpmRect.height()/2)-(img.height()/2)));
			p.drawImage(xpmRect.x() + ((xpmRect.width()/2)-(img.width()/2)),
					xpmRect.y() + ((xpmRect.height()/2)-(img.height()/2)),
					img);
		}
	}

	int x = geometry().x();
	int y = geometry().y();
	int w = geometry().width();
	int h = geometry().height();
	PD::Rect textRect(x, y, w-20, h);

	TableWidgetItem::drawText(p, textRect, text().c_str() );
	//printf("row:%d text:%s\n", row(), text().c_str());


	if (highlight)
	{
		p.setPenColor(palette().color(PD::Palette::FocusColor, s));

		p.setPenColor(  palette().color(PD::Palette::FocusColor, s));
		p.drawRect(x, y, x+w-1, y+h-1);
	}

}
TableWidgetCheckItem::TableWidgetCheckItem(Widget* parent, 
	int row, int col) : TableWidgetItem(parent, row, col)
{
}

TableWidgetCheckItem::~TableWidgetCheckItem()
{
}

void TableWidgetCheckItem::drawItem(Painter& p, bool highlight/*=false*/)
{
	Palette::State s = Palette::Enable;
	if ( !selectable() ) s = Palette::Disable;

	if (highlight)
	{
		p.setBrushColor(palette().color(Palette::Highlight, s));
		p.setPenColor(palette().color(Palette::HighlightText, s));
	}
	else
	{
		p.setBrushColor(palette().color(Palette::Background, s));
		p.setPenColor(palette().color(Palette::Text , s));
	}

	p.fillRect(geometry());


	Rect r = geometry();

	p.setPenColor(palette().color(Palette::Text, s));
	Rect checkBox(r.x()+(r.width()/2) - (r.height()/2),
			r.y() + (r.height()/2) - (r.height()/2),
			r.height(), r.height());
	p.drawRect(checkBox.x()+3, checkBox.y()+3, checkBox.x()+checkBox.height()-3,
			checkBox.y()+checkBox.height()-3);


	if (m_checkFlag)
	{
		Image img;
		if (img.loadXpm(check_xpm))
		{
			p.drawImage(checkBox.x()+((checkBox.width()/2)-(img.width()/2)),
					checkBox.y() + ((checkBox.height()/2)-(img.height()/2)),
					img);
		}
	}

	if (highlight) 
	{ 
		p.setPenColor(palette().color(Palette::FocusColor, s)); 

		p.setPenColor(  palette().color(Palette::FocusColor, s)); 
		p.drawRect(r.x(), r.y(), r.x()+r.width()-1, r.y()+ r.height()-1); 
	}    

}

TableWidgetImageItem::TableWidgetImageItem(PD::Widget* parent, int row, int col) :
    TableWidgetItem(parent, row, col)
{
    m_image = NULL;
}

TableWidgetImageItem::~TableWidgetImageItem()
{
}

void TableWidgetImageItem::setImage(PD::Image* img)
{
	assert(m_image == NULL);
    m_image = img;
}

void TableWidgetImageItem::drawItem(PD::Painter& p, bool highlight/*=false*/)
{
	Palette::State s = Palette::Enable;
	if ( !selectable() ) s = Palette::Disable;
	if (highlight)
	{
		p.setBrushColor(palette().color(PD::Palette::Highlight, s));
		p.setPenColor(palette().color(PD::Palette::HighlightText, s));
	}
	else
	{
		p.setBrushColor(palette().color(PD::Palette::Background, s));
		p.setPenColor(palette().color(PD::Palette::Text, s ));
	}

	p.fillRect(geometry());

	int x = geometry().x();
	int y = geometry().y();
	int w = geometry().width();
	int h = geometry().height();
	p.drawImage(x + (w/2)-(m_image->width()/2),
			y + (h/2)-(m_image->height()/2),
			*m_image);

	if (highlight)
	{
		p.setPenColor(palette().color(PD::Palette::FocusColor, s));

		p.drawRect(x, y, x+w-1, y+h-1);
	}
}

void TableWidgetItem::setFont(const char* name, int size)
{ 
	d->fontName = name;
	d->fontSize = size;
}

} //namespace PD {

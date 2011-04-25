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
#ifndef _PDTABLEWIDGETITEM_P_H_
#define _PDTABLEWIDGETITEM_P_H_

namespace PD {

class TableWidgetItemPrivate
{
public:
	std::string text;
	bool selectable;
	int row;
	int column;
	Palette palette;
	Rect geometry;
	TableWidgetItem* around[4];

	Widget* parent;
	bool hasFocus;
	int alignment;

	std::string backupText;
	std::string fontName;
	int fontSize;

public:
	TableWidgetItemPrivate(Widget* _parent, int _row, int _col)
	{
		parent = _parent;
		row = _row;
		column = _col;
		selectable = true;

		around[TableWidgetItem::Up] = 0;
		around[TableWidgetItem::Down] = 0;
		around[TableWidgetItem::Left] = 0;
		around[TableWidgetItem::Right] = 0;
		hasFocus = false;
		alignment = AlignCenter;
		fontSize = 0;
	}
};

} //namespace PD {
#endif

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
#ifndef _PDTABLEWIDGET_P_H_
#define _PDTABLEWIDGET_P_H_

#include <map>

namespace PD {

typedef std::map<int, TableWidgetItem*> ItemMap;
typedef ItemMap::iterator				ItemMapIt;
typedef std::map<int, int>	 			SizeMap;

class TableWidgetPrivate
{
public:
	int marginX;
	int marginY;

	int cellSpaceWidth;
	int cellSpaceHeight;

	int rowCount;
	int columnCount;

	SizeMap columnWidthMap;
	SizeMap rowHeightMap;

	ItemMap itemMap;

	int curRow;
	int curColumn;

	TableWidget::KeyMoveMode keyMoveMode;

	TableWidgetItem* focusItem;

	bool mouseReleaseFlag;
	bool keyProcessing;

	int tableViewSize;

public:
	TableWidgetPrivate(int row, int col)
	{
		mouseReleaseFlag = false;
		rowCount = row;
		columnCount = col;
		keyProcessing = false;

		init();
	}

	~TableWidgetPrivate()
	{
		ItemMapIt it = itemMap.begin();

		while(it != itemMap.end())
		{
			TableWidgetItem* item = it->second;
			//printf("TableWidget::~TableWidget r:%d c:%d delete\n", item->row(),
			//	item->column());
			if (item->isTextItem()) delete (TableWidgetTextItem*)item;
			else if (item->isComboItem()) delete (TableWidgetComboItem*)item;
			else if (item->isImageItem()) delete (TableWidgetImageItem*)item;
			else if (item->isLineEditItem()) delete (TableWidgetLineEditItem*)item;
			else if (item->isCheckItem()) delete (TableWidgetCheckItem*)item;
			else delete item;
			it++;
		}
	}


	void init()
	{
		marginX = 5;
		marginY = 5;

		cellSpaceWidth = 5; 
		cellSpaceHeight = 5; 

		curRow = -1;
		curColumn = -1;

		focusItem = NULL;

		keyMoveMode = TableWidget::NonRotate;
	}
};

} // namespace PD {
#endif

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

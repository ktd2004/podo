#ifndef _PDTABLEWIDGET_H_
#define _PDTABLEWIDGET_H_

#include "PDWidget.h"
#include "PDTableWidgetItem.h"

namespace PD {

class TableWidgetPrivate;

/**
 * \brief 
 * \ingroup gui
 */
class TableWidget : public Widget
{
public:
	enum Around { Up = 0, Down, Left, Right };
	enum KeyMoveMode { NonRotate = 0, VerticalRotate, HorizontalRotate, AllRotate };


private:
	TableWidgetPrivate* d;

public:
	TableWidget(Widget* parent, const char* name, int row, int col);
	virtual ~TableWidget();

	void setKeyMoveMode(KeyMoveMode m);
	KeyMoveMode keyMoveMode();

	void setFocusItem(TableWidgetItem* item);
	TableWidgetItem* focusItem();

	void setMarginX(int x);
	void setMarginY(int y);
	int marginX();
	int marginY();

	int curRow();
	int curColumn();

	void setRowCount(int row);
	void setColumnCount(int column);
	int rowCount();
	int columnCount();

	void setCellSpaceWidth(int w);
	void setCellSpaceHeight(int h);

	int cellSpaceWidth();
	int cellSpaceHeight();

	void setColumnWidth(int col, int width);
	void setRowHeight(int row, int height);

	int rowHeight(int row);
	int columnWidth(int col);

	void cellUpdate(int row, int column, bool focus=false);
	void drawItem(int row, int column, bool focus=false);

	void setItem(int row, int col, TableWidgetItem* item);
	TableWidgetItem* item(int row, int col);

	TableWidgetItem* getPossibleFocusItem(Around a, int row, int col);

	void clearSelection();

	sigslot::signal2<int,int>	selected;	
	sigslot::signal1<int>		focusOut;	
	sigslot::signal0<>			exitTable;

protected:
	virtual void 		paintEvent(PaintEvent*);
	virtual void		drawCellItem(Painter& p, int row, int column,
		bool focus=false);
	virtual void		mousePressEvent(MouseEvent* evt);
	virtual void		mouseReleaseEvent(MouseEvent* evt);
	virtual void 		mouseMoveEvent(MouseEvent* evt);

	virtual bool		keyPressUpEvent(int key);
	virtual bool		focusInEvent(FocusInEvent*);
	virtual bool		focusOutEvent(FocusOutEvent*);

private:
	void checkItem(int x, int y, int& row, int& col);	
};

} // namespace PD

#endif

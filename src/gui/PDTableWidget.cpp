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
#include "PDTableWidget.h"
#include "../base/PDString.h"
#include "../base/PDFlagScoper.h"
#include <vector>
#include <string>
#include <map>
#include <assert.h>
#include "PDTableWidget_p.hpp"

namespace PD {

TableWidget::TableWidget(Widget* parent, const char* name, int row, int col) : 
	Widget(parent, name, 0, Theme::TableWidget)
{
	d = new TableWidgetPrivate(row, col);
}

TableWidget::~TableWidget()
{
	delete d;
}

void TableWidget::setKeyMoveMode(KeyMoveMode m) { d->keyMoveMode = m; }
TableWidget::KeyMoveMode TableWidget::keyMoveMode() { return d->keyMoveMode; }

void TableWidget::setFocusItem(TableWidgetItem* item) 
{
	if( item )
	{
		d->focusItem = item; 
		d->curRow = item->row();
		d->curColumn = item->column();
		d->focusItem->setHasFocus(true);
	}
	else printf("TableWidget::setFocusItem item is NULL!!!\n");
}
TableWidgetItem* TableWidget::focusItem() { return d->focusItem; }

void TableWidget::setMarginX(int x) { d->marginX = x; }
void TableWidget::setMarginY(int y) { d->marginY = y; }
int TableWidget::marginX() { return d->marginX; }
int TableWidget::marginY() { return d->marginY; }

int TableWidget::curRow() { return d->curRow; }
int TableWidget::curColumn() { return d->curColumn; }

void TableWidget::setRowCount(int row) { d->rowCount = row; }
void TableWidget::setColumnCount(int column) { d->columnCount = column; }
int TableWidget::rowCount() { return d->rowCount; }
int TableWidget::columnCount() { return d->columnCount; }

void TableWidget::setCellSpaceWidth(int w)
{ 
	d->cellSpaceWidth = w; 
}
void TableWidget::setCellSpaceHeight(int h) { d->cellSpaceHeight = h; }

int TableWidget::cellSpaceWidth() { return d->cellSpaceWidth; }
int TableWidget::cellSpaceHeight() { return d->cellSpaceHeight; }



void TableWidget::setItem(int row, int col, TableWidgetItem* i)
{
	//printf("View::setItem row:%d col:%d text:%s\n", row, col,
	//	i->text().c_str());
	// focusItem이 NULL이면 제일 처음 선택가능한 item을 focusItem으로 설정함.
	if(!focusItem() && i->selectable()) setFocusItem(i);
	if(item(row, col))
	{

		TableWidgetItem* item = d->itemMap[row*columnCount()+col];

		if (item->isTextItem()) delete (TableWidgetTextItem*)item;
		else if (item->isComboItem()) delete (TableWidgetComboItem*)item;
		else if (item->isImageItem()) delete (TableWidgetImageItem*)item;
		else if (item->isLineEditItem()) delete (TableWidgetLineEditItem*)item;
		else if (item->isCheckItem()) delete (TableWidgetCheckItem*)item;
		else delete item;
	}
	d->itemMap[row*columnCount()+col] = i;
}


bool TableWidget::focusOutEvent(FocusOutEvent*)
{
	clearSelection();
	return false;
}

bool TableWidget::focusInEvent(FocusInEvent*)
{
	cellUpdate(d->curRow, d->curColumn, true);
	return false;
}

TableWidgetItem* TableWidget::item(int row, int col)
{
	ItemMapIt it = d->itemMap.find(row*columnCount()+col);	

	if(it == d->itemMap.end()) return NULL;

	return d->itemMap[row*columnCount()+col];
}


void TableWidget::setColumnWidth(int col, int width)
{
	assert(col < columnCount());
	d->columnWidthMap[col] = width;
}

void TableWidget::setRowHeight(int row, int height)
{
	assert(row < rowCount());
	d->rowHeightMap[row] = height;
}

int TableWidget::rowHeight(int row)
{
	assert(row < rowCount());
	return d->rowHeightMap[row];
}
int TableWidget::columnWidth(int col)
{
	assert(col < columnCount());
	return d->columnWidthMap[col];
}

void TableWidget::paintEvent(PaintEvent*)
{
	Painter p(this);
	for(int row=0; row<rowCount(); row++)
	{
		for(int col=0; col<columnCount(); col++)
		{
			drawCellItem(p, row, col);
		}
	}
}

void TableWidget::drawCellItem(Painter& p, int row, int column, bool focus/*=false*/)
{
	//if(!isVisible()) return;
	//printf("TableWidget::drawCellItem r:%d c:%d (%s)\n",
	//	row, column, (focus)? "focus" : "");
	int width = d->columnWidthMap[column];
	int height = d->rowHeightMap[row];

	int x = d->marginX;
	int y = d->marginY;

	// y 좌표 계산
	for(int i=0; i<row; i++) y += (d->rowHeightMap[i]+d->cellSpaceHeight);
	//  좌표 계산
	for(int j=0; j<column; j++) x += (d->columnWidthMap[j]+d->cellSpaceWidth);
	//printf("row:%d col:%d x : %d y: %d\n", row, column, x, y);
	
	Rect r(	x, y, width, height);

	TableWidgetItem* i= (TableWidgetItem*)item(row, column);
	if(i)
	{
		i->setGeometry(r);
		i->drawItem(p, focus);
	}
}

void TableWidget::cellUpdate(int row, int column, bool focus/*=false*/)
{
	if(!isVisible()) return;
	if( row<0 || column<0 )
	{
		printf("TableWidget::cellUpdate r:%d c:%d focus:%d\n", 
				row, column, focus);
		return;
	}
	//printf("TableWidget::cellUpdate r:%d c:%d focus:%d\n", row, column, focus);
	//printf("TableWidget::cellUpdate true!!\n");

	drawItem(row, column, focus);

	int width = d->columnWidthMap[column];
	int height = d->rowHeightMap[row];

	int x = d->marginX;
	int y = d->marginY;

	for(int i=0; i<row; i++) y += (d->rowHeightMap[i]+d->cellSpaceHeight);
	for(int j=0; j<column; j++) x += (d->columnWidthMap[j]+d->cellSpaceWidth);

	Rect r(x, y, width, height);
	//printf("x:%d y:%d width:%d height:%d visible:%d\n",
	//	x,y,width,height, isVisible());

	update(r);
}

void TableWidget::drawItem(int row, int column, bool focus)
{
	Painter p(this);

	drawCellItem(p, row, column, focus);
}



void TableWidget::mousePressEvent(MouseEvent* evt)
{
	//printf("TableWidget::mousePressEvent\n");
}

void TableWidget::mouseReleaseEvent(MouseEvent* evt)
{
	if (d->mouseReleaseFlag)
	{
		printf("TableWidget::mouseReleaseEvent already processing...\n");
		return;
	}
	d->mouseReleaseFlag = true;

	int row = 0;
	int col = 0;

	checkItem(evt->x(), evt->y(), row, col);	

	// 아이템영역이 아님
	if(row < 0 && col <0) { d->mouseReleaseFlag=false; return; }

	if(!item(row, col) ) { d->mouseReleaseFlag=false; return; }

	// 선택할수 없는 아이템이면 그리지 않음
	if(!item(row, col)->selectable()) { d->mouseReleaseFlag=false; return; }

	bool same = false;
	if(row == d->curRow && col == d->curColumn)
	{
		same = true;
	}

	Painter p(this);

	if(focusItem() && !same)
	{
		focusItem()->setHasFocus(false);
		focusItem()->redraw();
		cellUpdate(focusItem()->row(), focusItem()->column());
	}

	if(item(d->curRow, d->curColumn) && !same)
	{
		item(d->curRow, d->curColumn)->setHasFocus(false);
		item(d->curRow, d->curColumn)->redraw();
		cellUpdate(d->curRow, d->curColumn);
	}

	if(item(row, col)) 
	{
		setFocusItem(item(row, col));
		focusItem()->redraw(true);
		if(focusItem()->isCheckItem())
		{
			((TableWidgetCheckItem*)focusItem())->setCheckFlag(
				!((TableWidgetCheckItem*)focusItem())->checkFlag());
		}
		cellUpdate(row, col, true);
	}

	if(!hasFocus()) setFocus();

	//printf("TableWidget::mouseReleaseEvent row:%d col:%d\n",
	//	d->curRow, d->curColumn);
	selected.emit(d->curRow, d->curColumn);

	d->mouseReleaseFlag = false;
}

void TableWidget::mouseMoveEvent(MouseEvent*  evt)
{
	int row = 0;
	int col = 0;

	checkItem(evt->x(), evt->y(), row, col);	
	// 아이템영역이 아님
	if(row < 0 && col <0) return;

	if(!item(row, col) ) return;
	// 선택할수 없는 아이템이면 그리지 않음
	if(!item(row, col)->selectable()) return;

	// 이전아이템과 같으면 그리지 않음
	if(row == d->curRow && col == d->curColumn) return;

	Painter p(this);
	cellUpdate(d->curRow, d->curColumn);

	d->curRow = row;
	d->curColumn = col;
	cellUpdate(d->curRow, d->curColumn, true);
}

void TableWidget::checkItem(int x, int y, int& r, int& c)
{
	Point globalPt(x, y);
	Point localPt = mapFromGlobal(globalPt);

	bool find = false;

	for(int row=0; row<rowCount(); row++)
	{
		for(int col=0; col<columnCount(); col++)
		{
			if(!item(row, col)) continue;
			if(item(row, col)->geometry().contains(localPt.x(), localPt.y()))
			{
				find = true;
				r = row;
				c = col;
				break;
			}
		}
	}
	if(!find)  { r = -1; c = -1; }
}

bool TableWidget::keyPressUpEvent(int key)
{
	int row = d->curRow;
	int col = d->curColumn;
	bool move = false;
	bool exitWhile = false;

	if (key == SDLK_RETURN)
	{
		if(d->keyProcessing) return true;
		PD::FlagScoper f(&d->keyProcessing);
		TableWidgetItem* i = item(row, col);
		if( i == 0 || !i->selectable() ) return true;
		if(i->isCheckItem())
		{
			((TableWidgetCheckItem*)i)->setCheckFlag(
				!((TableWidgetCheckItem*)i)->checkFlag());
			cellUpdate(row, col, true);
		}
		selected.emit(d->curRow, d->curColumn);
		return true;
	}
	else if(key == SDLK_LEFT)
	{
		int cnt = 0;
		// 선택할수없는 영역일때 skip처리
		while(1)
		{
			if( cnt>=columnCount() ) return true;
			col--;
			if(exitWhile && col == d->curColumn) break;
			if(col<0)
			{
				if(d->keyMoveMode == HorizontalRotate || 
					d->keyMoveMode == AllRotate)
				{
					col = columnCount()-1;
				}
				else
				{
					focusOut.emit(Left);
					return true;
				}
			}
			if(item(row, col) && item(row, col)->selectable())
			{
				break;
			}
			//if(d->curColumn <0) d->curColumn = d->columnCount-1;
			cnt++;
		}
		move = true;

	}
	else if(key == SDLK_RIGHT)
	{
		int cnt = 0;
		// 선택할수없는 영역일때 skip처리
		while(1)
		{
			if( cnt>=columnCount() ) return true;
			col++;
			if(exitWhile && col == d->curColumn) break;
			if(col > columnCount()-1)
			{
				if(d->keyMoveMode == HorizontalRotate || 
					d->keyMoveMode == AllRotate)
				{
					col = 0;	
				}
				else
				{
					focusOut.emit(Right);
					return true;
				}

			}
			if(item(row, col) && item(row, col)->selectable()) break;
			cnt++;
		}
		move = true;
	}
	else if(key == SDLK_UP)
	{
		int cnt = 0;
		// 선택할수없는 영역일때 skip처리
		while(1)
		{
			if( cnt>=rowCount() ) return true;
			row--;
			if(exitWhile && row == d->curRow) break;
			if(row < 0)
			{
			
				if(d->keyMoveMode == VerticalRotate || 
					d->keyMoveMode == AllRotate)
				{
					row = rowCount()-1;	
				}
				else 
				{
					focusOut.emit(Up);
					return true;
				}
			}
			if(item(row, col) && item(row, col)->selectable()) break;
			cnt++;
		}
		move = true;
	}

	else if(key == SDLK_DOWN)
	{
		int cnt = 0;
		// 선택할수없는 영역일때 skip처리
		while(1)
		{
			if( cnt>=rowCount() ) return true;
			row++;
			if(exitWhile && row == d->curRow) break;
			if(row > rowCount()-1)
			{
				if(d->keyMoveMode == VerticalRotate || 
					d->keyMoveMode == AllRotate)
				{
					row = 0;
				}
				else 
				{
					focusOut.emit(Down);
					return true;
				}
			}
			if(item(row, col) && item(row, col)->selectable()) break;
			cnt++;
		}
		move = true;
	}
	else if(key == SDLK_ESCAPE)
	{
		return false;
	}
	else
	{
		if( item(row, col) == 0 ) return true;
		if(item(row, col)->isLineEditItem())
		{
			if(key == SDLK_BACKSPACE)
			{
				std::string x = item(row, col)->text();
				if(x.length() == 1) x = "";
				x = String::left(x, x.length()-1);
				item(row, col)->setText(x.c_str());
				cellUpdate(row, col, true);
			}
			else
			{
				std::string c;
				c = String::format("%c", key);
				std::string x = item(row, col)->text();
				x.append(c);
				int textWidth = 0;
				int textHeight = 0;
				font()->textSize(x.c_str(), textWidth, textHeight);

				PD::TableWidgetLineEditItem* lineEdit = 
					(PD::TableWidgetLineEditItem*)item(row, col);

				// maxLength 설정 되어 있음.(default:0)
				if(lineEdit->maxLength())
				{
					if((int)x.length() > lineEdit->maxLength())
						return false;
				}
				// maxLEngth 설정 되어 있지 않으면, item의 width만큼
				// 자동으로 제한됨.
				else if(item(row,col)->geometry().width() < textWidth)
				{
					return false;
				}
				item(row, col)->setText(x.c_str());
				cellUpdate(row, col, true);

			}
			return true;
		}
	}

	if(move)
	{
		Painter p(this);
		
		if(focusItem())
		{
			focusItem()->setHasFocus(false);
			cellUpdate(focusItem()->row(), focusItem()->column());
		}
		if( focusItem() && (focusItem()->row() != d->curRow || 
			focusItem()->column() != d->curColumn) )
		{
			if(item(d->curRow, d->curColumn) )
			{
				item(d->curRow, d->curColumn)->setHasFocus(false);
				cellUpdate(d->curRow, d->curColumn);
			}
		}
		
		if(item(row, col)) 
		{
			setFocusItem(item(row, col));
			cellUpdate(row, col, true);
		}
		return true;
	}
	return false;
}

void TableWidget::clearSelection()
{
	//printf("TableWidget::clearSelection() curRow:%d curCol:%d\n",
	//	d->curRow, d->curColumn);
	if(d->curRow < 0 && d->curColumn < 0) return;
	if(!item(d->curRow, d->curColumn)) return ;
	if(!isVisible()) return;
	Painter p(this);
	cellUpdate(d->curRow, d->curColumn);
}


TableWidgetItem* TableWidget::getPossibleFocusItem(Around a, int /*row*/, int col)
{
	TableWidgetItem* i= NULL;
	int c = 0;
	bool first = true;
	if(a == Up)
	{
		for(int r=0; r<rowCount(); r++)
		{
			c = col;
			while(1)
			{
				i = item(r, c);
				if(i)
				{
					if(i->selectable())
					{
						return i;
						break;
					}
				}
				c++;
				if(c >=columnCount()) break;
				else if(c == col && !first) break;

				first = false;
			}
		}
	}
	else if(a == Down)
	{
		for(int r=rowCount()-1; r>=0; r--)
		{
			c = col;
			while(1)
			{
				i = item(r, c);

				if(i)
				{
					if(i->selectable())
					{
						return i;
						break;
					}
				}
				c++;
				if(c >=columnCount()) break;
				else if(c == col && !first) break;

				first = false;
			}

		}
	}
	else if(a == Left)
	{
		// TODO:..
	}
	else if(a == Right)
	{
		// TODO:..
	}

	return NULL;
}

} // PD

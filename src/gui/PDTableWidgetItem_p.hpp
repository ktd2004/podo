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

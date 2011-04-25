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
#ifndef _PDTABLEWIDGETITEM_H_
#define _PDTABLEWIDGETITEM_H_

#include "PDWidget.h"
#include "PDPainter.h"
#include <vector>

namespace PD {

class TableWidgetItemPrivate;

/**
 * \brief 
 * \ingroup gui
 */
class TableWidgetItem 
{
	friend class TableWidgetTextItem;
	friend class TableWidgetComboItem;
	friend class TableWidgetLineEditItem;
	friend class TableWidgetCheckItem;
	friend class TableWidgetImageItem;

public:
	enum Around { Up=0, Down, Left, Right };

private:
	TableWidgetItemPrivate* d;

protected:
	void drawText(Painter& p, Rect rect, const char* text);

public:
	TableWidgetItem(Widget* parent, int row, int col);
	virtual ~TableWidgetItem();

	virtual bool isTextItem() = 0;
	virtual bool isComboItem() = 0;
	virtual bool isImageItem() = 0;
	virtual bool isLineEditItem() = 0;
	virtual bool isCheckItem() = 0;

	virtual void setText(std::string text);
	std::string& text();
	std::string& backupText();

	int row();
	int column();

	void setSelectable(bool flag);
	bool selectable();

	Palette& palette();
	void setPalette(Palette p);

	Widget* parent();

	void setGeometry(Rect r);
	Rect geometry();

	bool hasFocus();
	void setHasFocus(bool f);

	void setAlignment(int al);
	int alignment();

	void redraw(bool highlight=false);
	virtual void drawItem(Painter& p, bool highlight=false);
	void setFont(const char* name, int size);
	const std::string& fontName();
	int fontSize();
};

/**
 * \brief 
 * \ingroup gui
 */
class TableWidgetTextItem : public TableWidgetItem
{
public:
	TableWidgetTextItem(PD::Widget* parent, int row, int col);
	virtual ~TableWidgetTextItem();

	bool isTextItem() { return true; }
	bool isComboItem() { return false; }
	bool isImageItem() { return false; }
	bool isLineEditItem() { return false; }
	bool isCheckItem() { return false; }
};

/**
 * \brief 
 * \ingroup gui
 */
class TableWidgetComboItem : public PD::TableWidgetItem
{
public:
    typedef std::vector<std::string> StringList;

private:
    StringList m_list;

public:
    TableWidgetComboItem(PD::Widget* parent, int row, int col);
    virtual ~TableWidgetComboItem();

    bool isTextItem() { return false; }
    bool isComboItem() { return true; }
    bool isImageItem() { return false; }
    bool isLineEditItem() { return false; }
    bool isCheckItem() { return false; }

    void setStringList(StringList list) { m_list = list; }
    StringList stringList() { return m_list; }

    void addString(const char* text);
    void drawItem(PD::Painter& p, bool highlight=false);
};

/**
 * \brief 
 * \ingroup gui
 */
class TableWidgetLineEditItem : public PD::TableWidgetItem
{
public:
    enum EchoMode
    {
        Normal = 0,
        Password,
        Number,
    };

private:
    EchoMode m_mode;
	int m_maxLength;
	int m_min, m_max;

public:
    TableWidgetLineEditItem(PD::Widget* parent, int row, int col);
    virtual ~TableWidgetLineEditItem();

    void setEchoMode(EchoMode t) { m_mode = t; };
	void setMaxLength(int len) { m_maxLength = len; }
	int maxLength() { return m_maxLength; }
	void setRange(int min, int max) { m_min = min; m_max = max; }

    virtual bool isTextItem() { return false; }
    virtual bool isComboItem() { return false; }
    virtual bool isImageItem() { return false; }
    virtual bool isLineEditItem() { return true; }
    virtual bool isCheckItem() { return false; }

    virtual void drawItem(PD::Painter& p, bool highlight=false);
};

/**
 * \brief 
 * \ingroup gui
 */
class TableWidgetCheckItem : public TableWidgetItem
{
private:
	bool m_checkFlag;

public:
	TableWidgetCheckItem(PD::Widget* parent, int row, int col);
	virtual ~TableWidgetCheckItem();

	bool isTextItem() { return false; }
	bool isComboItem() { return false; }
	bool isImageItem() { return false; }
	bool isLineEditItem() { return false; }
	bool isCheckItem() { return true; }

	void setCheckFlag(bool f) { m_checkFlag = f; }
	bool checkFlag() { return m_checkFlag; }

	void drawItem(PD::Painter& p, bool highlight=false);

};

/**
 * \brief 
 * \ingroup gui
 */
class TableWidgetImageItem : public PD::TableWidgetItem
{
private:
    PD::Image* m_image;
public:
    TableWidgetImageItem(PD::Widget* parent, int row, int col);
    virtual ~TableWidgetImageItem();

    virtual bool isTextItem() { return false; }
    virtual bool isComboItem() { return false; }
    virtual bool isImageItem() { return true; }
    virtual bool isLineEditItem() { return false; }
    virtual bool isCheckItem() { return false; }

    void setImage(PD::Image* image);

    void drawItem(PD::Painter& p, bool highlight=false);
};

} //namespace PD {

#endif

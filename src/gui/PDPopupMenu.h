#ifndef _PDPOPUPMENU_H_
#define _PDPOPUPMENU_H_

#include "PDWidget.h"
#include "PDButton.h"
#include "PDPainter.h"
#include <vector>
#include <string>

namespace PD {

/**
 * \brief
 * \ingroup gui
 */
class PopupMenuItem
{
private:
	size_t m_no;
	std::string m_text;
	bool m_enable;

public:
	PopupMenuItem();
	PopupMenuItem(const char* text, bool enable=true);

	size_t no();
	void setNo(size_t n);

	const char* text();
	void setText(const char* t);

	bool enable() const;
	void setEnable(bool f);

	PopupMenuItem& operator=(PopupMenuItem& item);
};

class PopupMenuPrivate;

/**
 * \brief
 * \ingroup gui
 */
class PopupMenu : public PD::Widget
{
public:
	typedef std::vector<PopupMenuItem> ItemList;

private:
	PopupMenuPrivate* d;

public:
	PopupMenu(PD::Widget* parent=NULL, const char* name=0,
		uint style=Style_NoTitle);
	~PopupMenu();

	ItemList& itemList();

	void addItem(const PopupMenuItem& item);
	PopupMenuItem* item(int idx);

	int selectedItem();
	void setSelectItem(int idx);

	sigslot::signal1<int> clicked;

protected:
	void drawItem(PD::Painter& p, int idx);
	void paintEvent(PaintEvent*);

	void mouseEvent(MouseEvent* evt);
	void mouseReleaseEvent(MouseEvent* evt);

	bool keyReleaseEvent(KeyEvent* evt);

private:
	int nextItem(int current, bool down=true);
	int selectedItem(int x, int y);
};

} //namespace PD {

#endif

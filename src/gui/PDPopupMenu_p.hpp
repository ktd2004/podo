#ifndef _PDPOPUPMENU_P_H_
#define _PDPOPUPMENU_P_H_

namespace PD {

class PopupMenuPrivate
{
public:
	std::string title;
	PopupMenu::ItemList itemList;

	int select;

public:
	PopupMenuPrivate()
	{
		select = -1;
	}
};
} //namespace PD {
#endif

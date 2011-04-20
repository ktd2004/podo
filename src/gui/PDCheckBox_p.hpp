#ifndef _PDCHECKBOX_P_H_
#define _PDCHECKBOX_P_H_

namespace PD {

class CheckBoxPrivate
{
public:
	bool checkFlag;
	std::string text;
	CheckBox::CheckStyle checkStyle;

public:
	CheckBoxPrivate()
	{
		checkFlag = false;
		checkStyle = CheckBox::CheckV;
	}

};

} //namespace PD
#endif

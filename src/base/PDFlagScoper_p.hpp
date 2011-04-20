#ifndef _PDFLAGSCOPER_P_H_
#define _PDFLAGSCOPER_P_H_

namespace PD {

class FlagScoperPrivate
{
public:
	bool defaultVal;
	bool* flag;

	FlagScoperPrivate(bool* f, bool def)
	{
		defaultVal = def;
		flag = f;
		*flag = def;
	}
	
	~FlagScoperPrivate()
	{
		*flag = !defaultVal;
	}
};

} //namespace
#endif

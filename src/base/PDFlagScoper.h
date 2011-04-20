#ifndef _PDFLAGSCOPER_H_
#define _PDFLAGSCOPER_H_

namespace PD {

class FlagScoperPrivate;

/**
 * \brief flag scoper
 * \ingroup base
 */
class FlagScoper
{
private:
	FlagScoperPrivate* d;

public:
	FlagScoper(bool* flag, bool defaultVal=true);
	~FlagScoper();
};

} //namespace PD

#endif

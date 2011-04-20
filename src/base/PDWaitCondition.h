#ifndef _PDWAITCONDITION_H_
#define _PDWAITCONDITION_H_

namespace PD {

class WaitConditionPrivate;

/**
 * \brief 
 * \ingroup base
 */
class WaitCondition
{
private:
	WaitConditionPrivate* d;

public:
	WaitCondition();
	~WaitCondition();

	bool wait(int timeout=-1);
	void wakeOne();
	void wakeAll();
};

} //namespace PD {

#endif //#define _PDWAITCONDITION_H_

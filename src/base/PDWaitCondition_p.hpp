#ifndef _PDWAITCONDITION_P_H_
#define _PDWAITCONDITION_P_H_

namespace PD {

class WaitConditionPrivate
{
public:
	Mutex mutex;
	pthread_cond_t cond;

public:
	WaitConditionPrivate()
	{
		pthread_cond_init(&cond, 0);
	}

	~WaitConditionPrivate()
	{
		pthread_cond_destroy(&cond);
	}
};

} //namespace PD {
#endif

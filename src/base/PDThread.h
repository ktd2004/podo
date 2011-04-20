#ifndef _PDTHREAD_H_
#define _PDTHREAD_H_

#ifndef WIN32
#include <pthread.h>
#else
#include <process.h>
#endif

#include "PDMutex.h"

namespace PD {

class ThreadPrivate;

/**
 * \brief 
 * \ingroup base
 */
class Thread
{
public:
	enum Priority
	{
		IdlePriority=0,
		LowestPriority=1,
		LowPriority=2,
		NormalPriority=3,
		HighPriority=4,
		HighestPriority=5,
		TimeCriticalPriority=6,
		InheritPriority=7
	};

private:
	ThreadPrivate* d;

public:
	Thread();
	virtual ~Thread();

	Mutex& mutex();

	Priority priority();
	void setPriority(Priority p);

	bool isStop();
	bool isRunning();
	virtual void stop();
	virtual int start(Priority priority=InheritPriority);
	virtual int wait();

	virtual int run() = 0;

private:
#ifndef WIN32
	static void* run2(void*);
#else
	static unsigned int __stdcall run2(void*);
#endif
};

} //namespace PD {

#endif

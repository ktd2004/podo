#ifndef _PDTHREAD_P_H_
#define _PDTHREAD_P_H_

namespace PD {

class ThreadPrivate
{
public:
	Mutex mutex;
	bool stop;
	bool running;

	Thread::Priority priority;

#ifndef WIN32
	pthread_t handle;
#else
	HANDLE handle;
#endif

public:
	ThreadPrivate()
	{
		stop = false;
		running = false;
		handle = 0;
		priority = Thread::InheritPriority;
	}

	~ThreadPrivate()
	{
		#ifdef WIN32
		if (d->handle != 0)
		{
			CloseHandle(d->handle);
			d->handle = 0;
		}
		#endif
	}
};

} //namespace PD {
#endif

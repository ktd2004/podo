#ifndef _PDMUTEX_P_H_
#define _PDMUTEX_P_H_

namespace PD {

class MutexPrivate
{
public:
	#ifndef WIN32
	pthread_mutex_t mutex;	
	#else
	CRITICAL_SECTION crit;
	#endif

public:
	MutexPrivate()
	{
		#ifndef WIN32
		pthread_mutex_init(&mutex, NULL);
		#else
		InitializeCriticalSection(&crit); 
		#endif
	}

	~MutexPrivate()
	{
		#ifndef WIN32
		pthread_mutex_destroy(&mutex);
		#else
		DeleteCriticalSection(&crit); 
		#endif
	}
};

} //namespace PD {
#endif


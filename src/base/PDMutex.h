#ifndef _PDMUTEX_H_
#define _PDMUTEX_H_

#ifndef WIN32
#include <pthread.h>
#else
#ifdef _AFXDLL
#include <afx.h>
#else
#include <windows.h>
#endif //#ifdef _AFXDLL
#endif

namespace PD {

class MutexPrivate;

/**
 * \brief 
 * \ingroup base
 */
class Mutex
{
private:
	MutexPrivate* d;

public:
	Mutex();
	~Mutex();

#ifndef WIN32
	pthread_mutex_t* instance();
#else
	CRITICAL_SECTION* instance();
#endif

	void lock();
	void unLock();
};

} //namespace PD {

#endif

#ifndef _PDMUTEXLOCKER_H_
#define _PDMUTEXLOCKER_H_

#include "PDMutex.h"

namespace PD {

/**
 * \brief 
 * \ingroup base
 */
class MutexLocker
{
private:
	Mutex* m_mutex;

public:
	MutexLocker(Mutex* mutex);
	~MutexLocker();
};

} //namespace PD {

#endif

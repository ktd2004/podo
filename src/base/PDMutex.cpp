#include "PDMutex.h"
#include "PDMutex_p.hpp"

namespace PD {

/**
 * \brief 생성자
 */
Mutex::Mutex()
{
	d = new MutexPrivate;
}

/**
 * \brief 소멸자
 */
Mutex::~Mutex()
{
	delete d;
}

#ifndef WIN32
/**
 * \brief instance를 가지고옴
 *
 * \return instance
 */
pthread_mutex_t* Mutex::instance() { return &d->mutex; }
#else
/**
 * \brief instance를 가지고옴
 *
 * \return instance
 */
CRITICAL_SECTION* Mutex::instance() { return &d->crit; }
#endif

/**
 * \brief 잠그기
 */
void Mutex::lock()
{
#ifndef WIN32
	pthread_mutex_lock(&d->mutex);
#else
	::EnterCriticalSection(&d->crit);
#endif
}

/**
 * \brief 잠금 해제
 */
void Mutex::unLock()
{
#ifndef WIN32
	pthread_mutex_unlock(&d->mutex);
#else
	::LeaveCriticalSection(&d->crit);
#endif
}

} //namespace PD {


#include "PDMutexLocker.h"
#include <assert.h>

namespace PD {

/**
 * \brief 생성자
 *
 * lock, unlock을 빼먹는 실수로 인해 dead lock이 걸리는것을 방지하기 위한\n
 * help class
 *
 * \param mutex 
 */ 
MutexLocker::MutexLocker(Mutex* mutex)
{
	assert(mutex != 0);

	m_mutex = mutex;
	m_mutex->lock();
}

/**
 * \brief 소멸자
 */
MutexLocker::~MutexLocker()
{
	m_mutex->unLock();
}

} //namespace PD {

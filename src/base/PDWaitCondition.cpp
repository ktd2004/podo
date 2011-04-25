/* 
   Copyright 2011 PODO. 
   This file is part of PODO. 
   
   PODO is free software: you can redistribute it and/or modify 
   it under the terms of the GNU Lesser General Public License as  
   published by the Free Software Foundation, either version 3 of  
   the License, or (at your option) any later version. 
   
   PODO is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of 
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU Lesser General Public License for more details. 
   
   You should have received a copy of the GNU Lesser General Public  
   License along with PODO. If not, see <http://www.gnu.org/licenses/>. 
 */
#include "PDWaitCondition.h"

#ifndef WIN32
#include <pthread.h>
#else

#endif
#include "PDMutex.h"
#include "PDMutexLocker.h"
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include "PDWaitCondition_p.hpp"

namespace PD {

/**
 * \brief 생성자
 */
WaitCondition::WaitCondition()
{
	d = new WaitConditionPrivate;
}

/**
 * \brief 소멸자
 */
WaitCondition::~WaitCondition()
{
	wakeAll();
	delete d;
}

/**
 * \brief 대기
 *
 * \param timeout 대기시간(밀리초)
 *
 * \return true/false(대기시간이 설정된 경우 경과후 false가 반환됨)
 */
bool WaitCondition::wait(int timeout/*=-1*/)
{
	int n = 0;

	{
		MutexLocker ml(&d->mutex);

		if (timeout == -1)
		{
			n = pthread_cond_wait(&d->cond, d->mutex.instance());
		}
		else
		{
			struct timeval now;
			struct timespec tout;
			gettimeofday(&now, 0);

			tout.tv_sec = ((int)now.tv_sec) + timeout;
			tout.tv_nsec = now.tv_usec * 1000;

			n = pthread_cond_timedwait(&d->cond, d->mutex.instance(), &tout);
		}
	}

	if (n == 0) return true;
	else if (n == ETIMEDOUT) return false;

	return false;
}

/**
 * \brief 대기중인 것을 깨움
 */
void WaitCondition::wakeOne()
{
	MutexLocker ml(&d->mutex);
	pthread_cond_signal(&d->cond);
}

/**
 * \brief 대기중인 것을 전체 깨움
 */
void WaitCondition::wakeAll()
{
	MutexLocker ml(&d->mutex);
	pthread_cond_broadcast(&d->cond);
}

} //namespace PD {

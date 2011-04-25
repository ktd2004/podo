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
#include "PDThread.h"
#include "PDThread_p.hpp"
#include "PDMutexLocker.h"
#include <algorithm> // for std::max

#ifndef WIN32
#include <sched.h>
#include <errno.h>
#endif

#ifdef WIN32
#undef min
#undef max
#endif

namespace PD {

/**
 * \brief 생성자
 */
Thread::Thread()
{
	d = new ThreadPrivate;
}

/**
 * \brief 소멸자
 */
Thread::~Thread()
{
	stop();
	wait();

	delete d;
}


/**
 * \brief mutex를 반환
 *
 * \return mutex
 */
Mutex& Thread::mutex() { return d->mutex; }

/**
 * \brief 쓰레드 우선순위를 반환
 *
 * \return 쓰레드 우선순위를 반환
 * \sa setPriority()
 */
Thread::Priority Thread::priority() { return d->priority; }

/**
 * \brief 쓰레드 우선순위를 설정
 *
 * \param p Thread::Priority
 *
 * \sa priority()
 */
void Thread::setPriority(Priority p) { d->priority = p; }

/**
 * \brief 쓰레드가 정지되어 있는지 확인
 *
 * \return true/false
 * \sa stop()
 */
bool Thread::isStop()
{
	MutexLocker ml(&d->mutex);
	return d->stop;
}

/**
 * \brief 쓰레드가 동작중인지를 확인
 *
 * \sa true/false
 */
bool Thread::isRunning()
{
	return d->running;
}

/**
 * \brief 쓰레드가 정지시킴
 *
 * \sa isStop()
 */
void Thread::stop()
{
	MutexLocker ml(&d->mutex);
	d->stop = true;
}

/**
 * \brief 쓰레드를 시작
 *
 * \param priority 우선순위
 *
 * \return 0:ok, -1:error
 */
int Thread::start(Priority priority/*=InheritPriority*/)
{
	setPriority(priority);

	d->stop = false;
#ifndef WIN32

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//does not work pthread_join with PTHRAD_CREATE_DETACHED
	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (d->priority == InheritPriority)
	{
		pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
	}
	else
	{
		int prio;
		int schedPolicy;
		if (pthread_attr_getschedpolicy(&attr, &schedPolicy) == 0) 
		{
			int prioMin = sched_get_priority_min(schedPolicy);
			int prioMax = sched_get_priority_max(schedPolicy);
			if (prioMin != -1 && prioMax != -1) 
			{
				if (d->priority == IdlePriority) prio = prioMin;
				else if (d->priority == TimeCriticalPriority) prio = prioMax;
				else
				{
					prio = (((prioMax - prioMin) / TimeCriticalPriority) * 
						d->priority) + prioMin;
					prio = std::max(prioMin, std::min(prioMax, prio));
				}

				sched_param sp;
				sp.sched_priority = prio;

				if (pthread_attr_setinheritsched(&attr, 
					PTHREAD_EXPLICIT_SCHED) != 0
					|| pthread_attr_setschedpolicy(&attr, schedPolicy) != 0
					|| pthread_attr_setschedparam(&attr, &sp) != 0) 
				{
					pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
				}

			} //if (prioMin != -1 && prioMax != -1) 

		} //if (pthread_attr_getschedpolicy(&attr, &schedPolicy) == 0) 
	}

	int n = ::pthread_create(&d->handle, &attr, Thread::run2, this);
	if (n == EPERM)
	{
		// permission error
		pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
		n = pthread_create(&d->handle, &attr, Thread::run2, this);
	}

	pthread_attr_destroy(&attr);

	if (n)
	{
		return -1;
	}
#else
	unsigned int thrdAddr = 0;
	d->handle = (HANDLE)_beginthreadex(NULL,0,Thread::run2,this,0,&thrdAddr);
	if (d->handle == 0) return -1;
	SetThreadPriority(d->handle,THREAD_PRIORITY_BELOW_NORMAL);
#endif
	
	return 0;
}

/**
 * \brief 쓰레드가 종료되기를 기다림
 *
 * \return 0:ok, -1:error
 */
int Thread::wait()
{
	if (d->handle == 0) return 0;

#ifndef WIN32
	if (::pthread_join(d->handle, NULL) != 0) return -1;
#else
	WaitForSingleObject(d->handle,INFINITE);
#endif

	return 0;
}

#ifndef WIN32
void* Thread::run2(void* arg)
#else
unsigned int __stdcall Thread::run2(void* arg)
#endif

{
	Thread* t = (Thread*)arg;

	t->d->running = true;
	t->run();
	t->d->running = false;

	return 0;
}

} //namespace PD {

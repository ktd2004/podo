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


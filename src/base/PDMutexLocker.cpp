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

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

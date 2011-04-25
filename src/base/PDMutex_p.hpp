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


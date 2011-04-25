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
#ifndef _PDTHREAD_P_H_
#define _PDTHREAD_P_H_

namespace PD {

class ThreadPrivate
{
public:
	Mutex mutex;
	bool stop;
	bool running;

	Thread::Priority priority;

#ifndef WIN32
	pthread_t handle;
#else
	HANDLE handle;
#endif

public:
	ThreadPrivate()
	{
		stop = false;
		running = false;
		handle = 0;
		priority = Thread::InheritPriority;
	}

	~ThreadPrivate()
	{
		#ifdef WIN32
		if (d->handle != 0)
		{
			CloseHandle(d->handle);
			d->handle = 0;
		}
		#endif
	}
};

} //namespace PD {
#endif

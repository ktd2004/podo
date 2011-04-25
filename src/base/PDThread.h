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
#ifndef _PDTHREAD_H_
#define _PDTHREAD_H_

#ifndef WIN32
#include <pthread.h>
#else
#include <process.h>
#endif

#include "PDMutex.h"

namespace PD {

class ThreadPrivate;

/**
 * \brief 
 * \ingroup base
 */
class Thread
{
public:
	enum Priority
	{
		IdlePriority=0,
		LowestPriority=1,
		LowPriority=2,
		NormalPriority=3,
		HighPriority=4,
		HighestPriority=5,
		TimeCriticalPriority=6,
		InheritPriority=7
	};

private:
	ThreadPrivate* d;

public:
	Thread();
	virtual ~Thread();

	Mutex& mutex();

	Priority priority();
	void setPriority(Priority p);

	bool isStop();
	bool isRunning();
	virtual void stop();
	virtual int start(Priority priority=InheritPriority);
	virtual int wait();

	virtual int run() = 0;

private:
#ifndef WIN32
	static void* run2(void*);
#else
	static unsigned int __stdcall run2(void*);
#endif
};

} //namespace PD {

#endif

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
#include "PDTimer.h"
#include <SDL.h>
#include <base/PDDateTime.h>
#include <time.h>
#include "PDTimer_p.hpp"

namespace PD {

Timer::Timer()
{
	d = new TimerPrivate;
}

Timer::~Timer()
{
	stop();
	delete d;
}

unsigned int Timer::timeoutProc(unsigned int interval, void* param)
{
	((Timer*)param)->timeoutProc2();
	return interval;
}

void Timer::timeoutProc2()
{
	timeout();
}

void Timer::start(int msec)
{
	d->interval = msec;

	if (d->id != 0) 
		stop();

	d->id = SDL_AddTimer(msec, &Timer::timeoutProc, this);

	PD::DateTime startTime;
	d->startSec = startTime.sec();
	d->startMsec = startTime.msec();
}

void Timer::restart()
{
	stop();
	start(d->interval);
}

void Timer::stop()
{
	if (d->id == 0) return;

	SDL_RemoveTimer(d->id);
	d->id = 0;
}
bool Timer::isActive()
{
	if (d->id == 0) return false;
	return true;
}

int Timer::elapsed()
{
	PD::DateTime end;
	long endSec = end.sec();
	long endMsec = end.msec();

	long ret = 0;
	if ( endSec == d->startSec )
	{
		ret = endMsec - d->startMsec;
	}
	else if ( endSec > d->startSec )
	{
		if ( endMsec >= d->startMsec)
		{
			ret = endMsec + ((endSec - d->startSec)*1000);
		}
		else
		{
			ret = ((endSec - d->startSec)*1000) - endMsec;
		}
	}
	
	return (int)d->interval - ret;
}

} //namespace PD {

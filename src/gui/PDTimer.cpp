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

#ifndef _PDTIMER_P_H_
#define _PDTIMER_P_H_

namespace PD {

class TimerPrivate
{
public:
	SDL_TimerID  id;
	int interval;
	time_t startTime;
	long startSec;
	long startMsec;

public:
	TimerPrivate() :
		id(0),
		interval(0),
		startTime(0),
		startSec(0),
		startMsec(0)
	{

	}
};
} //namespace PD {
#endif

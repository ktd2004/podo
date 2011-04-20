#ifndef _PDTIMER_H_
#define _PDTIMER_H_

#include <base/PDObject.h>

namespace PD {

class TimerPrivate;

/**
 * \brief
 * \ingroup gui
 */
class Timer : public Object
{
private:
	TimerPrivate* d;

public:
	Timer();
	~Timer();

	void start(int msec);
	void restart();
	void stop();
	bool isActive();
	int elapsed();

	sigslot::signal0<> timeout;

protected:
	static unsigned int timeoutProc(unsigned int interval, void* param);

private:
	void timeoutProc2();
};

} //namespace PD {

#endif

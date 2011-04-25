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

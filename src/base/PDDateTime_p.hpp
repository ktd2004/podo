#ifndef _PDDATETIME_P_H_
#define _PDDATETIME_P_H_

namespace PD {

class DateTimePrivate
{
public:
#ifdef WIN32
	struct timeval 
	{  
		long tv_sec;  
		long tv_usec;
	};
#endif
	struct timeval tv;

public:
	DateTimePrivate()
	{
	}

	DateTimePrivate(struct timeval t)
	{
		tv = t;
	}

	DateTimePrivate(const DateTime& t)
	{
		tv = t.d->tv;
	}

	int toInt(const char* s, size_t len)
	{
		int v = 0;
		for (size_t i = 0; i < len; i++)  
		{
			v = v * 10 +  (s[i] - '0');
		}
		return v;
	}
};
} //namespace PD {
#endif


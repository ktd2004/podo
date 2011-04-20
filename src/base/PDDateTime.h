#ifndef _PDDATETIME_H_
#define _PDDATETIME_H_

#include <string>
#ifndef WIN32
#include <sys/time.h>
#include <unistd.h>
#else
#include <time.h>
#define snprintf	_snprintf
#endif

namespace PD {

class DateTimePrivate;

/**
 * \brief datetime
 * \ingroup base
 */
class DateTime
{
public:
	DateTimePrivate* d;

public:
	DateTime();
	DateTime(long sec, long usec=0);
	DateTime(struct timeval t);
	DateTime(const DateTime& t);
	DateTime(int year, int month, int day, 
		int hour, int min, int sec, long usec=0, bool isGmt=false);
	~DateTime();

	bool update(long sec, long usec=0);
	bool update();
	bool update(int year, int month, int day, 
		int hour, int min, int sec, long usec=0, bool isGmt=false);

	bool fromString(const char* datetime, bool isGmt=false);
	std::string toString(bool isGmt=false);

	int year(bool isGmt=false);
	int month(bool isGmt=false);
	int day(bool isGmt=false);

	int weekday(bool isGmt=false);
	bool isLeapYear(int year);
	int daysInMonth();

	float dayCount();
	float minuteCount();

	int hour(bool isGmt=false);
	int minute(bool isGmt=false);
	int second(bool isGmt=false);
	int msecond();
	int usecond();

	int setSystemTime();
	static int setSystemTime(struct timeval& t);

	bool isEqualMonth(DateTime d, bool isGmt=false);
	bool isEqualDay(DateTime d, bool isGmt=false);
	bool isEqualHour(DateTime d, bool isGmt=false);
	bool isEqualMinute(DateTime d, bool isGmt=false);
	bool isEqualSecond(DateTime d, bool isGmt=false);

	long sec() const;
	long msec() const;
	long usec() const;
	long tz() const;

	void addDay(int d);
	void addHour(int h);
	void addMinute(int m);
	void addSec(int s);

	void print(bool isGmt=false);

	DateTime& operator=(const DateTime& d);
	DateTime& operator=(const struct timeval& t);

	int operator==(const DateTime& d);
	int operator!=(const DateTime& d);

	int operator<(const DateTime& d) const;
	int operator>(const DateTime& d) const;

	int operator<=(const DateTime& d) const;
	int operator>=(const DateTime& d) const;

	DateTime& operator-(const DateTime& d);

};

} //namespace PD {

#endif

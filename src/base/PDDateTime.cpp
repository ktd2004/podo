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
#include "PDDateTime.h"
#include "PDDateTime_p.hpp"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // for debug printf
#include <limits.h>
#ifdef WIN32
#include <windows.h>
#endif
#include "PDString.h"

namespace PD {

static const short monthDays[] =
{
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/**
 * \brief 생성자
 */
DateTime::DateTime()
{
	d = new DateTimePrivate;
	update();	
}

/**
 * \brief 생성자
 *
 * \param sec 초단위 시간
 * \param usec 마이크로초 단위 시간
 */
DateTime::DateTime(long sec, long usec/*=0*/)
{
	d = new DateTimePrivate;
	update(sec, usec);
}

/**
 * \brief 생성자
 *
 * \param t timeval 
 */
DateTime::DateTime(struct timeval t)
{
	d = new DateTimePrivate(t);
}

/**
 * \brief 생성자
 *
 * \param t DateTime
 */
DateTime::DateTime(const DateTime& t)
{
	d = new DateTimePrivate(t);
}

/**
 * \brief 생성자
 *
 * \param year 연도
 * \param month 월
 * \param day 일
 * \param hour 시간
 * \param min 분
 * \param sec 초
 * \param usec 마이크로초
 * \param isGmt GMT유무
 */
DateTime::DateTime(int year, int month, int day, 
	int hour, int min, int sec, long usec/*=0*/, bool isGmt/*=false*/)
{
	d = new DateTimePrivate;
	update(year, month, day, hour, min, sec, usec, isGmt);
}

/**
 * \brief 소멸자
 */
DateTime::~DateTime()
{
	delete d;
}

/**
 * \brief 입력받은 초,마이크로초로 시간을 설정한다.
 *
 * \param sec 초
 * \param usec 마이크로초
 *
 * \return true/false
 */
bool DateTime::update(long sec, long usec/*=0*/)
{
	d->tv.tv_sec = sec;
	d->tv.tv_usec = usec;

	return true;
}

/**
 * \brief 현재시간으로 시간을 설정한다.
 *
 * \return true/false
 */
bool DateTime::update()
{
#ifdef WIN32
    ::time((time_t*)&d->tv.tv_sec);
#else
    gettimeofday(&d->tv, 0);
#endif

	return true;
}

/**
 * \brief 입력받은 인자로 시간을 설정한다.
 *
 * \param year 연도
 * \param month 월
 * \param day 일
 * \param hour 시간
 * \param min 분
 * \param sec 초
 * \param usec 마이크로초
 * \param isGmt GMT유무
 *
 * \return true/false
 */
bool DateTime::update(int year, int month, int day, 
	int hour, int min, int sec, long usec/*=0*/, bool isGmt/*=false*/)
{
	struct tm t;
	memset (&t, 0, sizeof (t));

	t.tm_year = year - 1900;  // years since 1900
	t.tm_mon  = month - 1;      // months since january - 0, 11 
	t.tm_mday = day;
	t.tm_hour = hour;
	t.tm_min  = min;
	t.tm_sec  = sec;

	if (!isGmt) t.tm_isdst = -1;

	time_t tmp = ::mktime(&t);
	if (tmp == (time_t)-1) return false;

	if (!isGmt) d->tv.tv_sec = (long)tmp;
	else d->tv.tv_sec = (long)(tmp - timezone);

	d->tv.tv_usec = usec;

	return true;
}

/**
 * \brief 문자열 포맷으로 데이타를 입력받아 시간을 설정한다.
 *
 * \param datetime YYYYMMDDhhmmss형식의 문자열(연/월/일/시간/분/초)
 * \param isGmt GMT유무
 * 
 * \return true/false
 * \sa toString()
 */
bool DateTime::fromString(const char* datetime, bool isGmt/*=false*/)
{
	if (strlen(datetime) != 14) return false;

	int year, mon, day, hour, min, sec;

	year = d->toInt(&datetime[0], 4);
	mon  = d->toInt(&datetime[4], 2);
	day  = d->toInt(&datetime[6], 2); 
	hour = d->toInt(&datetime[8], 2);
	min  = d->toInt(&datetime[10], 2);
	sec  = d->toInt(&datetime[12], 2);

	return update (year, mon, day, hour, min, sec, 0, isGmt);
}

/**
 * \brief 시간을 문자열 포맷으로 변환하여 반환한다.
 *
 * \param isGmt GMT유무
 *
 * \return YYYYMMDDhhmmss형식의 문자열(연/월/일/시간/분/초)
 * \sa fromString()
 */
std::string DateTime::toString(bool isGmt/*=false*/)
{
	//printf("DateTime::toString isGmt:%d\n", isGmt);
	return String::format("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
		year(isGmt), month(isGmt), day(isGmt),
		hour(isGmt), minute(isGmt), second(isGmt), msecond());
}

/**
 * \brief 연도
 *
 * \param isGmt GMT유무
 * \return 연도
 */
int DateTime::year(bool isGmt/*=false*/)
{
#ifdef WIN32
    struct tm* t = 0;

	if (isGmt) t = ::_gmtime32((const __time32_t*)&d->tv.tv_sec);
	else t = ::_localtime32((const __time32_t*)&d->tv.tv_sec);	

    return t->tm_year + 1900;
#else
    struct tm t;

	if (isGmt) ::gmtime_r (&d->tv.tv_sec, &t);
	else ::localtime_r (&d->tv.tv_sec, &t);

    return t.tm_year + 1900;
#endif
}

/**
 * \brief 월
 *
 * \param isGmt GMT유무
 * \return 월
 */
int DateTime::month(bool isGmt/*=false*/)
{
#ifdef WIN32
	struct tm* t = 0;
	if (isGmt) t = ::_gmtime32((const __time32_t*)&d->tv.tv_sec);
	else t = ::_localtime32((const __time32_t*)&d->tv.tv_sec);

	return t->tm_mon + 1;
#else
	struct tm t;

	if (isGmt) ::gmtime_r (&d->tv.tv_sec, &t);
	else ::localtime_r (&d->tv.tv_sec, &t);

	return t.tm_mon + 1;
#endif

}

/**
 * \brief 일자
 *
 * \param isGmt GMT유무
 * \return 일자
 */
int DateTime::day(bool isGmt/*=false*/)
{
#ifdef WIN32
	struct tm* t = 0;

	if (isGmt) t = ::_gmtime32((const __time32_t*)&d->tv.tv_sec);
	else t = ::_localtime32((const __time32_t*)&d->tv.tv_sec);

	return t->tm_mday;
#else
	struct tm t;

	if (isGmt) ::gmtime_r (&d->tv.tv_sec, &t);
	else ::localtime_r (&d->tv.tv_sec, &t);

	return t.tm_mday;
#endif
}

/**
 * \brief 요일을 반환한다.
 *
 * \param isGmt GMT유무
 * \return 요일(0:일, 1:월, 2:화, 3:수, 4:목, 5:금, 6:토)
 */
int DateTime::weekday(bool isGmt/*false*/)
{
#ifdef WIN32
	struct tm *t;
	
	if( isGmt ) t = ::_gmtime32((const __time32_t*)&d->tv.tv_sec);
	else t = ::_localtime32((const __time32_t*)&d->tv.tv_sec);

	return t->tm_wday;
#else
	struct tm t;

	if (isGmt) ::gmtime_r (&d->tv.tv_sec, &t);
	else ::localtime_r (&d->tv.tv_sec, &t);

	return t.tm_wday;
#endif
}
		
/**
 * \brief 윤달이 있는 해인지를 체크한다.
 *
 * \param year 연도
 * \return true/false
 */
bool DateTime::isLeapYear(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

/**
 * \brief 현재 설정된 월의 일수를 계산한다.
 *
 * \return 일수
 */
int DateTime::daysInMonth()
{
    int y, m, d;
    y = year();
    m = month();
    d = day();

    if (m == 2 && isLeapYear(y)) return 29; 
    else return monthDays[m];
}

/**
 * \brief 1970-01-01 00:00:00 이후의 시간을 계산한다.
 *
 * \return 분
 */
float DateTime::minuteCount()
{
	float n = (float)sec() / 60;
	return n;
}

/**
 * \brief 1970-01-01 00:00:00 이후의 일수를 계산한다.
 *
 * \return 분
 */
float DateTime::dayCount()
{
	float n = minuteCount() / 24;
	return n;
}

/**
 * \brief 현재 '시'를 반한환다.
 *
 * \param isGmt GMT유무
 * \return 시
 */
int DateTime::hour(bool isGmt/*=false*/)
{
#ifdef WIN32
	struct tm* t = 0;

	if (isGmt) t = ::_gmtime32((__time32_t*)&d->tv.tv_sec);
	else t = ::_localtime32((__time32_t*)&d->tv.tv_sec);

	return t->tm_hour;
#else
	struct tm t;

	if (isGmt) ::gmtime_r (&d->tv.tv_sec, &t);
	else ::localtime_r (&d->tv.tv_sec, &t);

	return t.tm_hour;
#endif

}

/**
 * \brief 현재 분을 반한환다.
 *
 * \param isGmt GMT유무
 * \return 분
 */
int DateTime::minute(bool isGmt/*=false*/)
{
#ifdef WIN32
	struct tm* t = 0;

	if (isGmt) t = ::_gmtime32((__time32_t*)&d->tv.tv_sec);
	else t = ::_localtime32((__time32_t*)&d->tv.tv_sec);

	return t->tm_min;
#else
	struct tm t;

	if (isGmt) ::gmtime_r (&d->tv.tv_sec, &t);
	else ::localtime_r (&d->tv.tv_sec, &t);

	return t.tm_min;
#endif

}

/**
 * \brief 현재 초를 반한환다.
 *
 * \param isGmt GMT유무
 * \return 초
 */
int DateTime::second(bool isGmt/*=false*/)
{
#ifdef WIN32
	struct tm* t = 0;

	if (isGmt) t = ::_gmtime32((const __time32_t*)&d->tv.tv_sec);
	else t = ::_localtime32((const __time32_t*)&d->tv.tv_sec);

	return t->tm_sec;
#else
	struct tm t;

	if (isGmt) ::gmtime_r (&d->tv.tv_sec, &t);
	else ::localtime_r (&d->tv.tv_sec, &t);

	return t.tm_sec;
#endif

}

/**
 * \brief 현재 밀리초를 반한환다.
 *
 * \return 밀리초
 */
int DateTime::msecond()
{
	return (d->tv.tv_usec/1000);
}

/**
 * \brief 현재 마이크로초를 반한환다.
 *
 * \return 마이크로초
 */
int DateTime::usecond()
{
	return d->tv.tv_usec;
}

/**
 * \brief 입력받은 인자와 월이 같은지를 비교한다.
 *
 * \param d DateTime
 * \param isGmt GMT유무
 * \return true/false
 * \sa isEqualDay()
 * \sa isEqualHour()
 * \sa isEqualMinute()
 * \sa isEqualSecond()
 */
bool DateTime::isEqualMonth(DateTime d, bool isGmt/*=false*/)
{
	return(
		year(isGmt) == d.year(isGmt) &&
		month(isGmt) == d.month(isGmt)
	);
}

/**
 * \brief 입력받은 인자와 일자가 같은지를 비교한다.
 *
 * \param d DateTime
 * \param isGmt GMT유무
 * \return true/false
 * \sa isEqualMonth()
 * \sa isEqualHour()
 * \sa isEqualMinute()
 * \sa isEqualSecond()
 */
bool DateTime::isEqualDay(DateTime d, bool isGmt/*=false*/)
{
	return(
		year(isGmt) == d.year(isGmt) &&
		month(isGmt) == d.month(isGmt) &&
		day(isGmt) == d.day(isGmt)
	);
}

/**
 * \brief 입력받은 인자와 시간이 같은지를 비교한다.
 *
 * \param d DateTime
 * \param isGmt GMT유무
 * \return true/false
 * \sa isEqualMonth()
 * \sa isEqualDay()
 * \sa isEqualMinute()
 * \sa isEqualSecond()
 */
bool DateTime::isEqualHour(DateTime d, bool isGmt/*=false*/)
{
	return(
		year(isGmt) == d.year(isGmt) &&
		month(isGmt) == d.month(isGmt) &&
		day(isGmt) == d.day(isGmt) &&
		hour(isGmt) == d.hour(isGmt)
	);
}

/**
 * \brief 입력받은 인자와 분이 같은지를 비교한다.
 *
 * \param d DateTime
 * \param isGmt GMT유무
 * \return true/false
 * \sa isEqualMonth()
 * \sa isEqualDay()
 * \sa isEqualHour()
 * \sa isEqualSecond()
 */
bool DateTime::isEqualMinute(DateTime d, bool isGmt/*=false*/)
{
	return(
		year(isGmt) == d.year(isGmt) &&
		month(isGmt) == d.month(isGmt) &&
		day(isGmt) == d.day(isGmt) &&
		hour(isGmt) == d.hour(isGmt) &&
		minute(isGmt) == d.minute(isGmt)
	);
}

/**
 * \brief 입력받은 인자와 초가 같은지를 비교한다.
 *
 * \param d DateTime
 * \param isGmt GMT유무
 * \return true/false
 * \sa isEqualMonth()
 * \sa isEqualDay()
 * \sa isEqualHour()
 * \sa isEqualMinute()
 */
bool DateTime::isEqualSecond(DateTime d, bool isGmt/*=false*/)
{
	return(
		year(isGmt) == d.year(isGmt) &&
		month(isGmt) == d.month(isGmt) &&
		day(isGmt) == d.day(isGmt) &&
		hour(isGmt) == d.hour(isGmt) &&
		minute(isGmt) == d.minute(isGmt) &&
		second(isGmt) == d.second(isGmt)
	);
}

/**
 * \brief 1970-01-01 00:00:00이후의 초를 반환한다.
 *
 * \return 초
 */
long DateTime::sec() const
{
	return d->tv.tv_sec;
}

/**
 * \brief 밀리초를 반환한다.
 *
 * \return 밀리초
 */
long DateTime::msec() const
{
	if (d->tv.tv_usec == 0) return 0;

	return (d->tv.tv_usec/1000);
}

/**
 * \brief 마이크로초를 반환한다.
 *
 * \return 마이크로초
 */
long DateTime::usec() const
{
	return d->tv.tv_usec;
}

/**
 * \brief 타임존을 반환한다.
 *
 * \return 타임존
 */
long DateTime::tz() const
{
	return timezone;
}

/**
 * \brief 일자를 더한다.
 *
 * \param d 일수
 */
void DateTime::addDay(int d)
{
	addHour(d * 24);
}

/**
 * \brief 시간을 더한다.
 *
 * \param h 시간
 */
void DateTime::addHour(int h)
{
	addMinute(h * 60);
}

/**
 * \brief 분을 더한다.
 *
 * \param m 분
 */
void DateTime::addMinute(int m)
{
	addSec(m * 60);
}

/**
 * \brief 초를 더한다.
 *
 * \param s 초
 */
void DateTime::addSec(int s)
{
	d->tv.tv_sec += s;
}

/**
 * \brief 콘솔로 시간을 출력한다.(디버깅용)
 *
 * \param isGmt GMT유무
 */
void DateTime::print(bool isGmt/*=false*/)
{
	printf("%s", toString(isGmt).c_str());
}

DateTime& DateTime::operator=(const DateTime& dateTime)
{
	d->tv = dateTime.d->tv;	
	return *this;
}

DateTime& DateTime::operator=(const struct timeval& t)
{
	d->tv = t;
	return *this;
}

int DateTime::operator==(const DateTime& dateTime)
{
	return (d->tv.tv_sec == dateTime.d->tv.tv_sec && 
			d->tv.tv_usec == dateTime.d->tv.tv_usec);
}

int DateTime::operator!=(const DateTime& dateTime)
{
	return (d->tv.tv_sec != dateTime.d->tv.tv_sec && 
			d->tv.tv_usec != dateTime.d->tv.tv_usec);
}

int DateTime::operator<(const DateTime& dateTime) const
{
	if (d->tv.tv_sec < dateTime.d->tv.tv_sec) return 1;
	if (d->tv.tv_sec == dateTime.d->tv.tv_sec &&
		d->tv.tv_usec < dateTime.d->tv.tv_usec) return 1;

	return 0;
}

int DateTime::operator>(const DateTime& dateTime) const
{
	if (d->tv.tv_sec > dateTime.d->tv.tv_sec) return 1;
	if (d->tv.tv_sec == dateTime.d->tv.tv_sec &&
		d->tv.tv_usec > dateTime.d->tv.tv_usec) return 1;

	return 0;

}

int DateTime::operator<=(const DateTime& dateTime) const
{
	if (d->tv.tv_sec < dateTime.d->tv.tv_sec) return 1;
	if (d->tv.tv_sec == dateTime.d->tv.tv_sec &&
		d->tv.tv_usec <= dateTime.d->tv.tv_usec) return 1;

	return 0;
}

int DateTime::operator>=(const DateTime& dateTime) const
{
	if (d->tv.tv_sec > dateTime.d->tv.tv_sec) return 1;
	if (d->tv.tv_sec == dateTime.d->tv.tv_sec &&
		d->tv.tv_usec >= dateTime.d->tv.tv_usec) return 1;

	return 0;
}

DateTime& DateTime::operator-(const DateTime& dateTime)
{
	d->tv.tv_sec -= dateTime.d->tv.tv_sec;
	d->tv.tv_usec -= dateTime.d->tv.tv_usec;

	return *this;	
}


/**
 * \brief 현재시스템 시간을 변경한다.
 *
 * \return 0:ok -1:error
 */
int DateTime::setSystemTime()
{
	return setSystemTime(d->tv);
}

/**
 * \brief 현재시스템 시간을 변경한다.
 *
 * \param t timeval
 * \return 0:ok -1:error
 */
int DateTime::setSystemTime(struct timeval& t)
{
#ifdef WIN32
	struct tm* ptm = ::_localtime32 ((const __time32_t*)&t.tv_sec);

	SYSTEMTIME st;
	st.wYear         = (WORD)(ptm->tm_year + 1900);
	st.wMonth        = (WORD)(ptm->tm_mon + 1);
	st.wDay          = (WORD)(ptm->tm_mday);
	st.wHour         = (WORD)(ptm->tm_hour);
	st.wMinute       = (WORD)(ptm->tm_min);
	st.wSecond       = (WORD)(ptm->tm_sec);
	st.wMilliseconds = (WORD)(0);

	if (!::SetLocalTime (&st)) return -1;
	return 0;
#else
	return ::settimeofday (&t, 0);
#endif	
}

} //namespace PD {


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
#include "PDCalendar.h"
#include "PDCalendar_p.hpp"
#include <string.h>
#include <assert.h>

namespace PD {

/**
 * \brief 생성자
 */
Calendar::Calendar()
{
	d = new CalendarPrivate;
	calendar(d->curYear, d->curMonth);
}

/**
 * \brief 소멸자
 */
Calendar::~Calendar()
{
	delete d;
}

/**
 * \brief 1달치에 해당하는 날짜별 값을 설정함
 * 
 * 이 값을 이용해서 달력에 추가로 필요한 값을 설정해 넣을 수 있다.
 *
 * \param value 
 * \return CalendarDayValue
 */
CalendarDayValue& Calendar::day(int value)
{
	assert( value >= 0 && value < Calendar::CalendarSize );
	return d->day[value]; 
}

/**
 * \brief 현재 가르키는 연도를 얻음
 *
 * next/previous등의 함수를 통해 연/월이 변경되면 변경된
 * 연도값을 얻어온다.
 *
 * \return 연도
 */
int Calendar::year()
{
	return d->tempYear;
}

/**
 * \brief 현재 가르키는 월을 얻음
 *
 * next/previous등의 함수를 통해 연/월이 변경되면 변경된
 * 월값을 얻어온다.
 *
 * \return 월
 */
int Calendar::month()
{
	return d->tempMonth;
}

/**
 * \brief 시스템에 설정된 연도의 값을 읽어옴
 *
 * \return 연도
 */
int Calendar::currentYear()
{
	return d->curYear;
}

/**
 * \brief 시스템에 설정된 월의 값을 읽어옴
 *
 * \return 월
 */
int Calendar::currentMonth()
{
	return d->curMonth;
}

/**
 * \brief 시스템에 설정된 일의 값을 읽어옴
 *
 * \return 일
 */
int Calendar::currentDay()
{
	return d->curDay;
}

/**
 * \brief 시스템에 설정된 연/월로 설정
 */
void Calendar::todayMonth()
{
	calendar(d->curYear, d->curMonth);
}

/**
 * \brief 다음월로 이동
 */
void Calendar::nextMonth()
{
	d->tempMonth += 1;
	if ( d->tempMonth > Calendar::December )
	{
		d->tempMonth = Calendar::January;
		d->tempYear += 1;
		if ( d->tempYear > Calendar::EndYear)
			d->tempYear = Calendar::StartYear;
	}
	calendar(d->tempYear, d->tempMonth);
}

/**
 * \brief 이전월로 이동
 */
void Calendar::previousMonth()
{
	d->tempMonth -= 1;
	if ( d->tempMonth < Calendar::January )
	{
		d->tempMonth = Calendar::December;
		d->tempYear -= 1;
		if ( d->tempYear < Calendar::StartYear)
			d->tempYear = Calendar::EndYear;
	}
	calendar(d->tempYear, d->tempMonth);
}

/**
 * \brief 다음 연도로 이동
 */
void Calendar::nextYear()
{
	d->tempYear += 1;
	if ( d->tempYear > Calendar::EndYear)
		d->tempYear = Calendar::StartYear;

	calendar(d->tempYear, d->tempMonth);
}

/**
 * \brief 이전  연도로 이동
 */
void Calendar::previousYear()
{
	d->tempYear -= 1;
	if ( d->tempYear < Calendar::StartYear)
		d->tempYear = Calendar::EndYear;

	calendar(d->tempYear, d->tempMonth);
}

/**
 * \brief 특정 연/월로 이동 
 *
 * \param year
 * \param month
 */
void Calendar::calendar(int year, int month)
{   
	int day, week;
	
	DateTime dateTime(year, month, 1, 0, 0, 0); 
	week = dateTime.weekday();
	day = dateTime.daysInMonth();
	d->tempYear = year;
	d->tempMonth = month;
	for(int i=0; i<Calendar::CalendarSize; i++)
	{   
		if ( i < week || i >= day + week )
		{
			d->day[i].setValid(false);
			d->day[i].setValue(0);
		}
		else
		{
			d->day[i].setValid(true);
			d->day[i].setValue(i - week + 1);
		}
	}   
}   

/**
 * \brief 콘솔로 현재 설정된 달력을 출력함(디버깅용)
 */
void Calendar::print()
{   
	printf("======== %d  / %d ========\n", d->tempYear, d->tempMonth);
	printf("Sun Mon Tue Wed Thr Fri Sat\n");
	for(int i=1; i<Calendar::CalendarSize + 1; i++)
	{  
		if (d->day[i-1].value() == d->curDay &&
			d->curYear == d->tempYear && 
			d->curMonth == d->tempMonth )
		{
			printf("%c[1;33m", 27);
			printf("%3d ", d->day[i-1].value());
			printf("%c[0m",27);      
		}
		else
		{
			if (d->day[i-1].valid() == false )
				printf("    ");
			else
				printf("%3d ", d->day[i-1].value() ); 
		}
			
		if (i%7 == 0) printf("\n");
	}   
}   

} //namespace PD {

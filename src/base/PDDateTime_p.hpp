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


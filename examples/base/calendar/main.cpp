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
#include "base/PDCalendar.h"
#include <stdio.h>
#include <stdlib.h>

int main(int /*argc*/, char** /*argv*/)
{
	PD::Calendar a;

	a.todayMonth();
	printf("Today month current(%04d-%02d-%02d) (%04d-%02d)\n",
		a.currentYear(), a.currentMonth(), a.currentDay(),
		a.year(), a.month());
	a.print();	

	a.previousMonth();
	printf("\nPrevious month current(%04d-%02d-%02d) (%04d-%02d)\n",
		a.currentYear(), a.currentMonth(), a.currentDay(),
		a.year(), a.month());
	a.print();

	a.nextMonth();
	printf("\nNext month current(%04d-%02d-%02d) (%04d-%02d)\n",
		a.currentYear(), a.currentMonth(), a.currentDay(),
		a.year(), a.month());
	a.print();

	a.previousYear();
	printf("\nPrevious year current(%04d-%02d-%02d) (%04d-%02d)\n",
		a.currentYear(), a.currentMonth(), a.currentDay(),
		a.year(), a.month());
	a.print();

	a.nextYear();
	printf("\nNext year current(%04d-%02d-%02d) (%04d-%02d)\n",
		a.currentYear(), a.currentMonth(), a.currentDay(),
		a.year(), a.month());
	a.print();



	return 0;
}

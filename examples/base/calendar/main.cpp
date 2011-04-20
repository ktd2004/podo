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

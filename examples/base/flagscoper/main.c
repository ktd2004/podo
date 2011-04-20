#include "base/PDFlagScoper.h"
#include <stdio.h>

int main(int argc, char** /*argv*/)
{
	bool condition=true;
	printf("condition is %d\n", condition);
	while(condition)
	{
		PD::FlagScoper flagscoper(&condition, false);
		break;
		condition=false;
	}
	printf("condition is %d\n", condition);
	return 0;
}



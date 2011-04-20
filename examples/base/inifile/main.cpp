#include <base/PDIniFile.h>
#include <stdio.h>

int main(int /*argc*/, char** /*argv*/)
{
	PD::IniFile iniFile("./config.ini");

	iniFile.writeEntry("general", "name", "podo");
	iniFile.writeEntry("general", "age", "30");
	iniFile.writeEntry("general", "tel", "82-31-704-9390");
	iniFile.write();

	printf("%s\n", iniFile.readEntry("general", "name").c_str());
	printf("%s\n", iniFile.readEntry("general", "age").c_str());
	printf("%s\n", iniFile.readEntry("general", "tel").c_str());

	return 0;
}

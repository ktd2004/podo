#include "PDLang.h"
#include "PDApp.h"
#include "../base/PDFile.h"
#include "../base/PDIniFile.h"
#include "PDLang_p.hpp"

namespace PD
{

Lang::Lang()
{
	d = new LangPrivate;
}

Lang::~Lang()
{
	d = new LangPrivate;
}

CountryCode Lang::countryCode() { return d->countryCode; }

void Lang::setLanguage(const char* fileName)
{
	if( fileName == NULL || !PD::File::exists(fileName) ||
		d->language.read(fileName) == -1 )
	{
		printf("App::setLanguage() language file not loading!\n");
		d->languageCheck = false;
		d->countryCode = CountryCodeEN;
		theApp->setLanguage(this);    
		return;
	}
	d->languageCheck = true;
	d->countryCode = d->CountryCodeToEnum(
		d->language.readEntry("CountryCode", "Code"));
	theApp->setLanguage(this);
}

std::string Lang::tr(const std::string& group, const std::string& key)
{
	if( d->countryCode == CountryCodeEN )
		return key;
	if( d->languageCheck )
	{
		std::string tempKey = key;
		tempKey = PD::String::trim(tempKey);
		std::string temp = d->language.readEntry(group, tempKey);
		temp = PD::String::trim(temp);
		if( temp == "" )
			return key;
		else
		{
			String::replace(temp, "\\n", "\n");
			return temp;
		}
	}
	return key;
}

}

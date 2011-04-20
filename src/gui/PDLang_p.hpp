#ifndef _PDLANG_P_H_
#define _PDLANG_P_H_

namespace PD {

class LangPrivate
{
public:
	IniFile language;
	bool languageCheck;
	CountryCode countryCode;

public:
	LangPrivate()
	{
	}

	CountryCode CountryCodeToEnum(std::string code)
	{
		code = String::trim(code);
		if( code == "EN" ) return CountryCodeEN;
		else if( code == "CT" ) return CountryCodeCT;
		else if( code == "CZ" ) return CountryCodeCZ;
		else if( code == "NL" ) return CountryCodeNL;
		else if( code == "CS" ) return CountryCodeCS;
		else if( code == "FR" ) return CountryCodeFR;
		else if( code == "DE" ) return CountryCodeDE;
		else if( code == "HU" ) return CountryCodeHU;
		else if( code == "IT" ) return CountryCodeIT;
		else if( code == "JP" ) return CountryCodeJP;
		else if( code == "KR" ) return CountryCodeKR;
		else if( code == "PL" ) return CountryCodePL;
		else if( code == "PT" ) return CountryCodePT;
		else if( code == "RU" ) return CountryCodeRU;
		else if( code == "ES" ) return CountryCodeES;
		else if( code == "SE" ) return CountryCodeSE;
		else if( code == "TH" ) return CountryCodeTH;
		return CountryCodeEN;
	}

	const char* CountryCodeToStr(CountryCode code)
	{
		if( code == CountryCodeEN ) return "EN";
		else if( code == CountryCodeCT ) return "CT";
		else if( code == CountryCodeCZ ) return "CZ";
		else if( code == CountryCodeNL ) return "NL";
		else if( code == CountryCodeCS ) return "CS";
		else if( code == CountryCodeFR ) return "FR";
		else if( code == CountryCodeDE ) return "DE";
		else if( code == CountryCodeHU ) return "HU";
		else if( code == CountryCodeIT ) return "IT";
		else if( code == CountryCodeJP ) return "JP";
		else if( code == CountryCodeKR ) return "KR";
		else if( code == CountryCodePL ) return "PL";
		else if( code == CountryCodePT ) return "PT";
		else if( code == CountryCodeRU ) return "RU";
		else if( code == CountryCodeES ) return "ES";
		else if( code == CountryCodeSE ) return "SE";
		else if( code == CountryCodeTH ) return "TH";

		return "EN";
	}
};

} //namespace PD {
#endif

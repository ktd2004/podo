#ifndef _PDGLOBAL_H_
#define _PDGLOBAL_H_

namespace PD {

enum Style
{
	Style_NoTitle = 0x000000001,
	Style_None    = 0x000000000
};

enum BgMode
{
	FillBg=0, // default
	ParentBg,
	NoBg
};

enum FocusPolicy
{
	NoFocus		= 0x00,
	TabFocus	= 0x01,
	ClickFocus	= 0x02,
	StrongFocus	= 0x03,
	WheelFocus	= 0x07
};

enum Alignment
{
	AlignLeft		= 0x0001,
	AlignRight		= 0x0002,
	AlignHCenter 	= 0x0004,

	AlignTop		= 0x0008,
	AlignBottom		= 0x0010,
	AlignVCenter	= 0x0020,

	AlignCenter		= AlignHCenter | AlignVCenter
};

enum CountryCode
{
	CountryCodeEN = 0,	// English 
	CountryCodeCT,		// Chinese (Traditional)
	CountryCodeCZ,		// Czech 
	CountryCodeNL,		// Dutch 
	CountryCodeCS,		// Chinese (Simplified)
	CountryCodeFR,		// French  5
	CountryCodeDE,		// German 
	CountryCodeHU,		// Hungarian 
	CountryCodeIT,		// Italian 
	CountryCodeJP,		// Japanese 
	CountryCodeKR,		// Korean 10
	CountryCodePL,		// Polish 
	CountryCodePT,		// Portuguese (Brazil) 
	CountryCodeRU,		// Russian 
	CountryCodeES,		// Spanish 
	CountryCodeSE,		// Swedish 15
	CountryCodeTH		// Thailand
};

}; //namespace PD {

#endif // #ifndef _PDGLOBAL_H_

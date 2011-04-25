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

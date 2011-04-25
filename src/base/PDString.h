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
#ifndef _PDSTRING_H_
#define _PDSTRING_H_

#include <string>
#include <vector>
#include <stdarg.h>

namespace PD {

/**
 * \brief 
 * \ingroup base
 */
class String
{
public:
	typedef std::vector<std::string> StringList;

public:
	static std::string trimLeft(std::string& s);
	static std::string trimRight(std::string& s);
	static std::string trim(const std::string& s);

	static std::string mid(std::string& s, unsigned int start, 
		unsigned int end);
	static std::string left(std::string& s, unsigned int size);
	static std::string right(std::string& s, unsigned int size);

	static std::string number(int value);
	static long toNumber(const char* str, int base=10, bool* success=NULL);

	static StringList split(const std::string line, const char* separators);

	static void replace(std::string &text, const std::string &findToken,
							   const std::string &replaceToken);

	static std::string format_arg_list(const char *fmt, va_list args);
	static std::string format(const char *fmt, ...);

	static std::string toUpper(std::string s);
	static std::string toLower(std::string s);

	static int find(std::string& s, const char* str);

	static void clarifyNumber(std::string& s, 
		char separator = ',', int width = 3);
};

} //namespace PD {

#endif

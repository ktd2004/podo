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
#include "PDString.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include <stdio.h>
#include <cctype>       // std::toupper, std::tolower
#include <errno.h>

#ifdef WIN32
#define _CRT_SECURE_NO_DEPRECATE 1 
#pragma warning(disable:4996) 
#include <mbstring.h>
#endif



namespace PD {

/**
 * \brief 입력된 문자에 대해서 왼쪽 공백문자를 모두 삭제한다.
 *
 * \param s 입력문자열
 * \return 결과 문자열
 */
std::string String::trimLeft(std::string& s) 
{
	std::string::iterator it;

	for( it = s.begin(); it != s.end(); it++ )
	{
#ifdef WIN32
		if( !_ismbcspace( *it ) ) break;
#else
		if( !isspace( *it ) ) break;
#endif
	}

	s.erase( s.begin(), it );
	return s;
}

/**
 * \brief 입력된 문자에 대해서 오른쪽 공백문자를 모두 삭제한다.
 *
 * \param s 입력문자열
 * \return 결과 문자열
 */
std::string String::trimRight(std::string& s) 
{
	std::string::difference_type dt;
	std::string::reverse_iterator it;

	for( it = s.rbegin(); it != s.rend(); it++ )
	{
#ifdef WIN32
		if( !_ismbcspace( *it ) ) break;
#else
		if( !isspace( *it ) ) break;
#endif
	}

	dt = s.rend() - it;

	s.erase( s.begin() + dt, s.end() );
	return s;
}

/**
 * \brief 입력된 문자에 대해서 왼쪽/오른쪽 공백문자를 모두 삭제한다.
 *
 * \param s 입력문자열
 * \return 결과 문자열
 */
std::string String::trim(const std::string& s) 
{
	std::string t = s;
	trimLeft(t);
	trimRight(t);

	return s;
}

/**
 * \brief 입력된 문자에 대해서 start부터 end까지의 문자를 반환한다.
 *
 * \param s 입력문자열
 * \param start 시작위치
 * \param end 종료위치
 *
 * \return 결과 문자열
 */
std::string String::mid(std::string& s, unsigned int start, 
		unsigned int end)
{
	if(start) s.erase(0, start);
	if(s.length() != end) s.erase(end, s.length()-end);

	return s;
}

/**
 * \brief 입력된 문자에 대해서 왼쪽부터 size만큼의 글자를 반환한다.
 *
 * \param s 입력문자열
 * \param size 길이
 *
 * \return 결과 문자열
 */
std::string String::left(std::string& s, unsigned int size)
{
	if(size && size < s.length()) s.erase(size, s.length()-size);
	return s;
}

/**
 * \brief 입력된 문자에 대해서 오른쪽부터 size만큼의 글자를 반환한다.
 *
 * \param s 입력문자열
 * \param size 길이
 *
 * \return 결과 문자열
 */
std::string String::right(std::string& s, unsigned int size)
{
	if(size && size < s.length()) s.erase(0, s.length()-size);
	return s;
}

/**
 * \brief 입력된 숫자에 대해서 문자열을 반환한다.
 *
 * \param value 입력숫자
 *
 * \return 결과 문자열
 */
std::string String::number(int value)
{
	return format("%d", value);
}

/**
 * \brief 입력된 문자열을 separators를 기준으로 분리한 결과를 반환한다.
 *
 * \param line 입력문자열
 * \param separators 구분자
 *
 * \return 결과 리스트
 */
String::StringList String::split(const std::string line, const char* separators)
{
	StringList list;	
	size_t start = line.find_first_not_of(separators);
	size_t end = line.length();

	while (start < end) 
	{
		size_t stop = line.find_first_of(separators, start);
		if (stop > end) stop = end;
		list.push_back(line.substr(start, stop-start));
		start = line.find_first_not_of(separators, stop+1);
	}

	return list;
}

/**
 * \brief 입력된 문자열중 findToken을 replaceToken으로 변환한다.
 *
 * \param text 입력문자열
 * \param findToken 찾을 문자열
 * \param replaceToken 변환할 문자열
 */
void String::replace(std::string &text, const std::string &findToken,
		const std::string &replaceToken)
{
	size_t i = 0;
	while ((i = text.find(findToken)) != std::string::npos)
		text.replace(i, findToken.size(), replaceToken);
}

/**
 * \brief 포맷팅된 문자열 반환
 *
 * \param fmt 포맷
 * \param args 인자
 *
 * \return 변환된 문자열
 */
std::string String::format_arg_list(const char *fmt, va_list args)
{
	if (!fmt) return "";
	int   result = -1, length = 256;
	char *buffer = 0;
	while (result == -1)
	{
		if (buffer) delete [] buffer;
		buffer = new char [length + 1];
		memset(buffer, 0, length + 1);
		result = vsnprintf(buffer, length, fmt, args);
		length *= 2;
	}
	std::string s(buffer);
	delete [] buffer;
	return s;
}

/**
 * \brief 포맷팅된 문자열 반환
 *
 * \param fmt 포맷
 *
 * \return 변환된 문자열
 */
std::string String::format(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	std::string s = format_arg_list(fmt, args);
	va_end(args);
	return s;
}

/**
 * \brief 입력된 문자열을 대문자로 변환해서 반환
 *
 * \param s 입력된 문자열
 *
 * \return 변환된 문자열
 */
std::string String::toUpper(std::string s)
{
	size_t length = s.length();
	for(size_t i=0; i!=length ; ++i)
	{
		s[i] = std::toupper(s[i]);
	}
	return s;
}

/**
 * \brief 입력된 문자열을 소문자로 변환해서 반환
 *
 * \param s 입력된 문자열
 *
 * \return 변환된 문자열
 */
std::string String::toLower(std::string s)
{
	size_t length = s.length();
	for(size_t i=0; i!=length ; ++i)
	{
		s[i] = std::tolower(s[i]);
	}
	return s;
}

/**
 * \brief 입력된 문자열중 str이 포함되어 있는지를 확인
 *
 * \param s 입력된 문자열
 * \param str 찾을 문자열
 *
 * \return -1:error, >0:찾은 위치
 */

int String::find(std::string& s, const char* str)
{
	char* find = (char*)s.c_str();

	int i = -1;
	while(find)
	{
		find = strstr(find, str);
		if(find) 
		{
			find = &find[strlen(str)];
			if (i == -1) i = 0;
			i++;
		}
	}
	return i; 
}


/**
 * \brief 세자리 숫자마다 comma를 찍는다.
 * \code
	string s("1234567890");
	clarifyNumber(s);
	std::cout << s << std::endl;
 * \endcode
 * \param s 입력버퍼
 * \param separator 구분자(기본값 ',')
 * \param width 자리수(기본값 3)
 * 
 */
void String::clarifyNumber(std::string& s, 
		char separator /*=','*/, int width /*= 3*/)
{
	std::string::iterator i = s.end() - width;
	while (i > s.begin())
		i = s.insert(i, separator) - width;
}

/** 
 * \brief 문자열을 정수형태로 변환.
 * 에러처리를 위하여 atoi를 사용하지 않고 strtol을 * 사용하였다.
 * 
 * \param str 변환하려는 문자열
 * \param base 진법(기본값 10진법)
 * \param success 성공 실패를 구분 하기 위한 인자.
 *                리턴값으로는 성공,실패를 구분하기 모호하다.
 * \return 성공시에는 변환된 값을 반환.
 *         실패시에는 -1을반환.
 **/
long String::toNumber(const char* str, int base/*=10*/, bool* success/*=NULL*/)
{   
	errno = 0;
	char* endPtr = 0;
	long val = strtol(str, &endPtr, base);

	if( (errno==ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
			(errno != 0 && val == 0) )
	{   
		//printf("String::toNumber strtol Error!! errno: %d\n",
		//		errno);
		if( success ) *success = false;
		return -1; 
	}   

	if( endPtr == str )
	{   
		//printf("String::toNumber str: %s has no digits!!\n",
		//		str );
		if( success ) *success = false;
		return -1; 
	}   
	if( success ) *success = true;
	return val;
}   

} //namespace PD {

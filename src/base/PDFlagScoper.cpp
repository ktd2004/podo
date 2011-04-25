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
#include "PDFlagScoper.h"
#include "PDFlagScoper_p.hpp"
#include <assert.h>

namespace PD {

/**
 * \brief 생성자
 *
 * bool변수값을 true/false로 설정하고 scope가 벗어나면 다시 초기화시키는\n
 * helper class
 *
 * \param flag
 * \param defaultVal
 */
FlagScoper::FlagScoper(bool* flag, bool defaultVal/*=true*/)
{
	assert(flag);

	d = new FlagScoperPrivate(flag, defaultVal);
}

/**
 * \brief 소멸자
 */
FlagScoper::~FlagScoper()
{
	delete d;
}

} //namespace

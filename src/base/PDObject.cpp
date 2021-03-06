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
#include "PDObject.h"

namespace PD {

/**
 * \brief 생성자
 *
 * PODO의 객체중 signal/slot이 지원되는 객체는 모두 Object를 상속받음
 */
Object::Object() 
{
}

/**
 * \brief 소멸자
 */
Object::~Object() 
{
}

} //namespace PD {

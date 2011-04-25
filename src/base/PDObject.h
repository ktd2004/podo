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
#ifndef _PDOBJECT_H_
#define _PDOBJECT_H_

#include "PDSigSlot.h"

#ifdef WIN32
#pragma warning(disable:4312) 
#endif


namespace PD {

/**
 * \brief 
 * \ingroup base
 */
class Object : public sigslot::has_slots<>
{
public:
	Object();
	virtual ~Object();
};

} //namespace PD {

#endif

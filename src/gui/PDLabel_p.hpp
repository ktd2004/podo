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
#ifndef _PDLABEL_P_H_
#define _PDLABEL_P_H_

namespace PD {

class LabelPrivate
{
public:
	std::string text;
	int	alignment;
	bool border;
	unsigned int margin;

	LabelPrivate() : alignment(AlignLeft | AlignTop)
	{
		border = false;
		margin = 2;
	}

	~LabelPrivate()
	{
	}
};
} //namespace PD {
#endif

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
#ifndef _PDPROCESS_H_
#define _PDPROCESS_H_

#include "PDObject.h"
#include "PDString.h"

namespace PD {

class ProcessPrivate;

/**
 * \brief 
 * \ingroup base
 */
class Process : public Object
{
public:
	enum PipeType{
        ReadPipe = 0,
        WritePipe
    };  

private:
	ProcessPrivate* d;

public:
	Process();
	virtual ~Process();	

	std::string command();
	void setCommand(std::string cmd);

	int start();
	int start(std::string name);

	static int exec(std::string cmd);
	int pid();
	void kill();

	sigslot::signal1<std::string>  readStdOut;
	sigslot::signal1<std::string>  readStdErr;

};

} //namespace PD {

#endif

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
#include "base/PDProcess.h"
#include "base/PDThread.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

using namespace PD;

class Test : public PD::Thread, public Object
{
private:
	Process *m_process;
	
public:
	Test(std::string name)
	{
		m_process = new Process();
		m_process->setCommand(name);
		m_process->readStdOut.connect(this, &Test::stdOut);
		m_process->readStdErr.connect(this, &Test::stdErr);

	};
	Process* process() { return m_process; };

	int run()
	{
		if( m_process->start() == -1 )
		{
			printf("Fail to start process\n");
		}
		return 0;
	}

	void stdOut(std::string s)
	{
		printf("stdOut = %s", s.c_str());
	}
	void stdErr(std::string s)
	{
		printf("stdErr = %s", s.c_str());
	}

};

int main(int /*argc*/, char** /*argv*/)
{
	Test test("/bin/ping yahoo.co.kr -c 5");
	test.start();

	int i = 0;
	while(1)
	{
		sleep(1);
		i = test.process()->pid();
		if( i == -1) break;
	}
	test.wait();

	return 0;
}


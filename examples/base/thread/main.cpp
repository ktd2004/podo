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
#include "base/PDThread.h"
#include "base/PDWaitCondition.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int kbhit()
{
    fd_set fd_read;
    timeval tv;

    FD_SET(0, &fd_read);
    select(1, &fd_read, 0, 0, &tv);
    return FD_ISSET(0, &fd_read);
}

class Test : public PD::Thread
{
private:
	int m_id;
	int m_count;
	bool m_isPause;
	PD::WaitCondition m_waitCondition;

public:
	Test(int id=0) : m_id(id), m_count(0), m_isPause(false) {}

	int count() { return m_count; }
	void setId(int id) { m_id = id; }
	void pause()
	{
		m_isPause = true;
	}

	void resume()
	{
		m_isPause = false;
		m_waitCondition.wakeOne();
	}

	int run()
	{
		printf("Test::run id:%d start\n", m_id);

		m_count = 0;

		while (1)
		{
			if (isStop()) 
			{
				printf("Test::run id:%d stop\n", m_id);
				break;
			}

			if (m_isPause)
			{
				printf("Test::run id:%d pause\n", m_id);

				m_waitCondition.wait();
				printf("Test::run id:%d resume\n", m_id);
			}

			printf("Test::run id:%d count:%d\n", m_id, m_count);
			m_count++;
			sleep(1);
		}

		printf("Test::run id:%d end\n", m_id);

		return 0;
	}
};

#define MAX_TEST_THREAD 3
int main(int /*argc*/, char** /*argv*/)
{
	Test testThread[MAX_TEST_THREAD];
	for (int i=0; i<MAX_TEST_THREAD; i++)
	{
		testThread[i].setId(i+1);
		testThread[i].start();
	}

	printf("command) [P]ause, [R]esume, [Q]uit\n");
	while(1)
	{
		char ch = kbhit();		
		if (ch == 0) continue;

		ch = getchar();
		
		if (ch == 'p' || ch == 'P') 
		{
			for (int i=0; i<MAX_TEST_THREAD; i++)
			{
				testThread[i].pause();
			}
		}
		else if (ch == 'r' || ch == 'R')
		{
			for (int i=0; i<MAX_TEST_THREAD; i++)
			{
				testThread[i].resume();
			}
		}
		else if (ch == 'q' || ch == 'Q')
		{
			printf("try to stop thread\n");
			for (int i=0; i<MAX_TEST_THREAD; i++)
			{
				testThread[i].resume();
				testThread[i].stop();
				testThread[i].wait();
				printf("%d thread count:%d\n", i, testThread[i].count());
			}
			break;
		}
	}

	printf("program end\n");

	return 0;
}

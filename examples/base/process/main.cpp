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


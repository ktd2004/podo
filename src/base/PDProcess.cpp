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
#include "PDProcess.h"
#include <errno.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <list>
#ifdef __APPLE__
#else
#include <wait.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "PDProcess_p.hpp"


namespace PD {

/**
 * \brief 생성자
 *
 * process와 양방향 통신을 하기위한 class
 */
Process::Process()
{
	d = new ProcessPrivate(this);
}

/**
 * \brief 소멸자
 */
Process::~Process()
{
	delete d;
}

/**
 * \brief command를 반환함
 *
 * \return command
 */
std::string Process::command() { return d->command; };

/**
 * \brief command를 설정
 *
 * \param cmd command
 */
void Process::setCommand(std::string cmd) { d->command = cmd; };

/**
 * \brief command를 실행
 *
 * \return 0:ok, -1:error
 */
int Process::start()
{
	if( d->command.empty())
	{
		//printf("Program Name Empty!!\n");
		return -1;
	}
	return start(d->command);
}

/**
 * \brief command를 실행
 *
 * \param cmd command
 *
 * \return 0:ok, -1:error
 */
int Process::start(std::string cmd)
{
	d->command = cmd;
	if( d->command.empty())
	{
		//printf("Program Name Empty!!\n");
		return -1;
	}
	//printf("Process::start(cmd):%s\n", cmd.c_str());
	
	d->initCommand();

	if( d->parseCmd(d->command) == -1 )
		return -1;
	if( d->runChild() != 0)
		return -1;
	return 0;
}

/**
 * \brief command를 실행하고 바로 종료함
 *
 * \param cmd command
 *
 * \return 0:ok, -1:error
 */
int Process::exec(std::string cmd)
{
	Process p;
	p.setCommand(cmd);
	return p.start();
}

/**
 * \brief PID를 읽어옴
 *
 * \return pid
 */
int Process::pid() { return d->pid; }

/**
 * \brief 실행된 command를 종료시킴
 */
void Process::kill() 
{
	if( d->pid == -1 )
		return;
	::kill(d->pid, SIGKILL); 
}

} //namespace PD 




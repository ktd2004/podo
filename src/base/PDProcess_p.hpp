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
#ifndef _PDPROCESS_P_H_
#define _PDPROCESS_P_H_

namespace PD {

class ProcessPrivate
{
public:
	Process* parent;
	int pid;
	int readPid;
	bool pipeCheck;
	bool wildCardsCheck;
	std::string command;
	std::string inFile;
	std::string outFile;
	PD::String::StringList arguments;

public:
	ProcessPrivate(Process* p)
	{
		parent = p;
		pid = -1;
		readPid = -1;
		pipeCheck = false;
		wildCardsCheck = false;
		arguments.clear();
	}

	int parseCmd(std::string cmd)
	{
		bool redirectCheck = false;
		PD::String::StringList tempArguments;

		arguments = PD::String::split(cmd, " ");
		PD::String::StringList::iterator it;
		it = arguments.begin();

		while( it != arguments.end())
		{
			if( strchr((*it).c_str(), '*') != NULL || 
					strchr((*it).c_str(), '?') != NULL )
			{
				wildCardsCheck = true;
			}

			if( (*it) == "<")
			{
				if( it+1 == arguments.end() )
				{
					//printf( "Redirection(<) file name missing\n");
					return -1;
				}
				inFile = *(it+1);
				++it;	
				redirectCheck= true;
			}
			if( (*it) == ">")
			{
				if( it+1 == arguments.end() )
				{
					//printf( "Redirection(>) file name missing\n");
					return -1;
				}
				outFile = *(it+1);
				++it;	
				redirectCheck= true;
			}
			if( (*it) == "|" )
				pipeCheck = true;

			if( redirectCheck )
				it++;
			else
			{
				tempArguments.push_back((*it));
				it++;
			}
		}
		arguments.clear();
		arguments = tempArguments;
		return 0;	
	}


	void initCommand()
	{
		pid = -1;
		readPid = -1;
		arguments.clear();
		inFile.clear();
		outFile.clear();
	}

	int runChild()
	{
		int pipeStdOut[2];
		int pipestdErr[2];

		if (pipe(pipeStdOut) == -1 || pipe(pipestdErr) == -1)
		{
			//printf("failed to open pipe!");
			return -1;
		}
		if ((pid = fork()) == 0) 
		{
			FILE *fp = 0;
			if (outFile != "") // > redirection일때 화일을 열어서 stdout으로 열어준다.
			{	
				if ( (fp = freopen(outFile.c_str(), "w", stdout)) == NULL)
				{
					//printf("redirect outfile error!\n");
					return -1;
				}
			} 
			if (inFile != "")	// < redirection일때 화일을 열어서 stdin으로 열어준다.
			{
				if ( (fp = freopen(inFile.c_str(),"r", stdin)) == NULL)
				{
					//printf("redirect infile error!\n");
					return -1;
				}
				dup2(pipeStdOut[Process::WritePipe], fileno(stdout));
				dup2(pipestdErr[Process::WritePipe], fileno(stderr));
			}
			if( outFile == "" && inFile == "")
			{
				dup2(pipeStdOut[Process::WritePipe], fileno(stdout));
				dup2(pipestdErr[Process::WritePipe], fileno(stderr));
			}

			close(pipeStdOut[Process::ReadPipe]);
			close(pipeStdOut[Process::WritePipe]);
			close(pipestdErr[Process::ReadPipe]);
			close(pipestdErr[Process::WritePipe]);

			if( pipeCheck )
			{
				//printf("PD::Process::runChild() pipeCheck True!!\n");

				//if (system(command.c_str()) == -1)
				//	printf("failed to system('%s')\n", command.c_str());
				if( outFile != "" || inFile != "" )
					fclose(fp);
				exit(0);
			}
			else if( wildCardsCheck )
			{
				//if (system(command.c_str()) == -1)
				//	printf("failed to system('%s')\n", command.c_str());

				//printf("Process::runChild() wildCardsCheck True!!\n");

				if( outFile != "" || inFile != "" )
					fclose(fp);
				exit(0);
			}
			else
			{
				char *argv[arguments.size()+1];
				int i = 0;
				PD::String::StringList::iterator it;
				it = arguments.begin();
				while( it != arguments.end())
				{
					argv[i++] = (char*)(*it).c_str();
					it++;
				}
				argv[i] = (char*)0;

				if (execvp(argv[0], argv) == -1)
				{
					if( outFile != "" || inFile != "" )
						fclose(fp);
					//printf("execvp error! - no such file?\n");
					exit(-1);
				}
				fclose(fp);	
			}
		}


		int status;

		close(pipeStdOut[Process::WritePipe]);
		close(pipestdErr[Process::WritePipe]);

		readPid = fork();
		if( readPid == 0)
		{
			char buf;
			int ret;
			std::string temp;

			while(1)
			{
				ret = read(pipeStdOut[Process::ReadPipe], &buf, sizeof(buf));
				if( ret == 0 )
					break;
				fflush(stdout);
				//printf("%c", buf);
				temp = temp + buf;
				if( buf == '\n' )
				{
					parent->readStdOut.emit(temp);
					temp = "";
				}
			}
			exit(1);
		}
		else
		{
			char buf;
			int ret;
			std::string temp;

			while(1)
			{
				ret = read(pipestdErr[Process::ReadPipe], &buf, sizeof(buf));
				if( ret == 0 )
					break;
				fflush(stdout);
				//printf("%c", buf);

				temp = temp + buf;
				if( buf == '\n' )
				{
					parent->readStdErr.emit(temp);
					temp = "";
				}
			}
		}
		close(pipeStdOut[Process::ReadPipe]);
		close(pipestdErr[Process::ReadPipe]);

		waitpid(readPid, 0, 0);
		waitpid(pid, &status, 0);

		pid = -1;
		pipeCheck = false;
		wildCardsCheck = false;

		int retV=0;

		if(WIFEXITED(status))
		{
			//printf("Process::runChild Normal exited, status: %d\n", 
			//		WEXITSTATUS(status));
			retV=WEXITSTATUS(status);
		}
		else if(WIFSIGNALED(status))
		{
			//printf("Process::runChild killed by signal: %d  errno: %d\n",
			//		WTERMSIG(status), errno);
			retV=WTERMSIG(status);
		}
		else if(WIFSTOPPED(status))
		{
			//printf("Process::runChild stopped by signal: %d  errno: %d\n", 
			//		WSTOPSIG(status), errno);
			retV=WSTOPSIG(status);
		}
		#if 0 // undefined gcc 3.4.3
		else if(WIFCONTINUED(status))
		{
			//printf("Process::runChild still work\n");
		}
		#endif
		else
		{
			printf("Process::runChild status was else(unknown)\n");
		}	
		return retV;
	}
};

} //namespace PD 
#endif

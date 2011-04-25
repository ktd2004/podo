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
#include "PDAbstractSocket.h"
#include "PDAbstractSocket_p.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#ifndef WIN32
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <signal.h>
#endif

#include <fcntl.h>
 
namespace PD {

void ignore_sigpipe()
{
#ifndef WIN32
	static int ignore_sigpipe_flag = 1;
	if (ignore_sigpipe_flag)
	{
		ignore_sigpipe_flag = 0;
		struct sigaction noaction;
		memset(&noaction, 0, sizeof(noaction));
		noaction.sa_handler = SIG_IGN;
		::sigaction(SIGPIPE, &noaction, 0);
	}
#endif
}

AbstractSocket::AbstractSocket(SocketType type)
{
	d = new AbstractSocketPrivate(type);
	create();
}

AbstractSocket::AbstractSocket(int sock, SocketType type)
{
	d = new AbstractSocketPrivate(sock, type);
}

AbstractSocket::~AbstractSocket()
{
	close();
	delete d;
}

int AbstractSocket::create()
{
	if (d->socketDescriptor != -1) return 0;

	int domain = PF_INET;
	int type = SOCK_STREAM;

	if (d->socketType == UdpSocket) type = SOCK_DGRAM;
	else if (d->socketType == UdsSocket) 
	{
		domain = AF_UNIX;
	}

	int fd = (int)socket(domain, type, 0);
	if (fd == -1) return -1;

#ifndef WIN32
	::fcntl(fd, F_SETFD, FD_CLOEXEC);
#endif

	setSocketDescriptor(fd);
	
	return 0;
}

void AbstractSocket::setBlocking(bool f)
{
	int sockfd = socketDescriptor();
#ifndef WIN32
	int flags = fcntl(sockfd, F_GETFL, 0);
	if (!f) fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
	else fcntl(sockfd, F_SETFL, flags ^ O_NONBLOCK);
#else
	int nonblocking =1;
	if (f) nonblocking = 0;

	if (ioctlsocket(sockfd,FIONBIO, (u_long*)&nonblocking) == SOCKET_ERROR)  
	{
		close();
		return;
	}
#endif	
}

bool AbstractSocket::bind()
{
	if (isClosed()) 
	{
		//printf("AbstractSocket::bind not opened socket\n");
		return false;
	}

	// Reuse Address
	if (d->socketType == TcpSocket)
	{
		int opt = 1;
#ifndef WIN32
		setsockopt(socketDescriptor(), SOL_SOCKET, SO_REUSEADDR, 
			&opt, sizeof(opt));
#else
		setsockopt(socketDescriptor(), SOL_SOCKET, SO_REUSEADDR, 
			 (const char *)&opt, sizeof(opt));
#endif
	}

	int retn = -1;
	if (d->socketType == UdsSocket)
	{
#ifndef WIN32
		sockaddr_un addr;
		memset(&addr, 0, sizeof(sockaddr_un));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, "/tmp/.kosocket");

		retn = ::bind(socketDescriptor(), (sockaddr*)&addr, sizeof(addr));
#else
		// TODO:...
#endif
	}
	else
	{
		sockaddr_in addr;
		memset(&addr, 0, sizeof(sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port());

		retn = ::bind(socketDescriptor(), (sockaddr*)&addr, sizeof(addr));
	}

	if (retn == -1)
	{
		//printf("TcpSock::listen failed to bind\n");
		return false;
	}

	return true;
}

bool AbstractSocket::listen()
{
	if (isClosed()) 
	{
		//printf("AbstractSocket::bind not opened socket\n");
		return false;
	}

	int backlog = 0;
	if (::listen(socketDescriptor(), backlog) == -1)
	{
		//printf("AbstractSocket::listen failed to listen\n");
		return false;
	}

	return true;
}

void AbstractSocket::setTimeout(int sec, int usec/*=0*/)
{
	d->timeout = sec;
	d->timeoutUsec = usec;
}

int AbstractSocket::timeout() { return d->timeout; }

void AbstractSocket::setHost(const char* host) { d->host = host; }
void AbstractSocket::setPort(int port) { d->port = port; }

const char* AbstractSocket::host() { return d->host.c_str(); }
int AbstractSocket::port() { return d->port; }

int AbstractSocket::timeoutProcess(bool read/*=true*/)
{
	if (d->timeout == 0) return 0;

	struct timeval t;
	fd_set readfds;

 	t.tv_sec = d->timeout;
	t.tv_usec = d->timeoutUsec;

	FD_ZERO (&readfds);
	FD_SET (socketDescriptor(), &readfds);

	int n = 0;
	do {
		if (read)
			n = ::select (socketDescriptor() + 1, &readfds, 0, 0, &t);
		else
			n = ::select (socketDescriptor() + 1, 0, &readfds, 0, &t);
	} while  (n == -1 && errno == EINTR);

	if (n == -1) 
		return -1;
	if (n == 0) 
		return -2;

	return 0;
}

void AbstractSocket::close()
{
	if (socketDescriptor() == -1) return;

#ifndef WIN32
	shutdown(socketDescriptor(), SHUT_RDWR);
	::close(socketDescriptor());
#else
	closesocket(socketDescriptor());
	//WSACleanup();
#endif
	setSocketDescriptor(-1);
}

bool AbstractSocket::isClosed() { return (d->socketDescriptor == -1); }

AbstractSocket::SocketType AbstractSocket::socketType() { return d->socketType; }

int AbstractSocket::socketDescriptor() { return d->socketDescriptor; }
void AbstractSocket::setSocketDescriptor(int sd) { d->socketDescriptor = sd; }



int AbstractSocket::bytesAvailable()
{
	int availBytes = 0;
#ifndef WIN32
	if (ioctl(socketDescriptor(),FIONREAD, &availBytes) != 0)
	{
		//printf("AbstractSocket::bytesAvailable errno:%d\n", errno);
		return -1;
	}
#else
	if (ioctlsocket(socketDescriptor(),FIONREAD, (u_long*)&availBytes) != 0)
	{
		return -1;
	}
#endif

	return availBytes;
}

} // namespace PD {

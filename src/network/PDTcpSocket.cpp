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
#include "PDTcpSocket.h"
#ifndef WIN32
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/time.h>

#else
#include "PDNetError.h"
#include <io.h>
#endif


#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>



namespace PD {


class TcpSocketPrivate
{
public:
	bool connected;

public:
	TcpSocketPrivate()
	{
		connected = false;
	}
};

TcpSocket::TcpSocket() : AbstractSocket(AbstractSocket::TcpSocket)
{
	d = new TcpSocketPrivate;
}

TcpSocket::TcpSocket(int sock) : AbstractSocket(sock, AbstractSocket::TcpSocket)
{
	d = new TcpSocketPrivate;
}

TcpSocket::~TcpSocket()
{
	delete d;
}

bool TcpSocket::connected() { return d->connected; }

int TcpSocket::accept()
{

	int tp = timeoutProcess();
	if (tp < 0) 
	{
		//printf("TcpSocket::accept timeout : %d\n", tp);
		return tp;
	}

    int n;
	sockaddr_in addr;
	int addrSize = sizeof(addr);

    do {
#ifndef WIN32
        n = ::accept(socketDescriptor(), (sockaddr*)&addr, 
			(socklen_t*)&addrSize);
#else
		 n = ::accept(socketDescriptor(), (sockaddr*)&addr, 
			(int*)&addrSize);
#endif

		
    } while(n == -1 && errno == EINTR);

	setHost( inet_ntoa(addr.sin_addr) );
	setPort( ntohs(addr.sin_port) );


    return n;
}

/**
 * \brief sendPacket
 * \param packet
 * \param packetSize
 * \return -1:error -2:timeout -3:disconnected
 */
int TcpSocket::sendPacket(const char* packet, size_t packetSize)
{
	if (socketDescriptor() == -1) return -1;

    //printf("TcpSocket::sendPacket request sendSize:%d\n", packetSize);

	ignore_sigpipe();

    size_t writeSize = 4096;
    if (packetSize < writeSize)
    	writeSize = packetSize;

    size_t written = 0;
    size_t remain = packetSize;

    while ( written < packetSize)
    {
        if (remain > 4096) 
        	writeSize = 4096;
        else 
        	writeSize = remain;

		//printf("TcpSocket::sendPacket write %d bytes(fd:%d)\n", 
		//	writeSize, socketDescriptor());
#ifndef WIN32
        int n = ::write(socketDescriptor(), &packet[written], writeSize);
#else
		int n = ::send(socketDescriptor(), &packet[written], writeSize, 0);
#endif
		if (n == 0)
		{
            //printf("TcpSocket::sendPacket disconnected written:%d\n", 
			//	written);
			close();
			return -3;
		}
        else if (n < 0)
        {
			if (errno == EWOULDBLOCK || errno == EINTR) 
			{
			#ifdef WIN32
				Sleep(1);
			#else
				usleep(1000);
			#endif
			//	printf("TcpSocket::sendPacket sockfd:%d "
			//		"errno:%d EWOULDBLOCK\n",
			//		socketDescriptor(), errno);
				continue;
			}
			else if (errno == ETIMEDOUT)
			{
				//printf("TcpSocket::sendPacket sockfd:%d ETIMEDOUT written:%d\n",
				//	socketDescriptor(), written);
				//close();
				return -2;
			}
			#if 0
			else if (errno == EPIPE)
			{
				printf("TcpSocket::sendPacket sockfd:%d packetSize:%d\n",
					socketDescriptor(), packetSize);
				printf("TcpSocket::sendPacket sockfd:%d EPIPE written:%d\n",
					socketDescriptor(), written);
				continue;
			}
			#endif

            //printf("TcpSocket::sendPacket sockfd:%d Failed to send:%d error:%d "
			//	"written:%d\n",
             //   socketDescriptor(), n, errno, written);
			close();
			return -1;
		}
		remain -= n;
		written += n;
		//printf("TcpSocket::sendPacket written %d byte(s)\n", written);
	}
	return written;
}

/**
 * \brief recvPacket
 * \param packet
 * \param packetSize
 * \return -1:error -2:timeout -3:disconnected
 */
int TcpSocket::recvPacket(char* packet, size_t packetSize)
{
	if (socketDescriptor() == -1) return -1;

    //printf("TcpSocket::recvPacket request recvSize:%d\n", packetSize);

    size_t readSize = 4096;
    if (packetSize < readSize) 
    	readSize = packetSize;

    size_t read = 0;
    size_t remain = packetSize;
    while ( read < packetSize)
    {
        int tp = timeoutProcess();
        if (tp < 0)
        {
			//printf("TcpSocket::recvPacket sockfd:%d packetSize:%d\n",
			//	socketDescriptor(), packetSize);
            //printf("TcpSocket::recvPacket sockfd:%d timeout:%d read:%d\n", 
			//	socketDescriptor(), tp, read);
			//close();
            return -2;
        }

        if ((size_t)readSize > remain) 
        	readSize = remain;

#ifndef WIN32
        int n = ::read(socketDescriptor(), &packet[read], readSize);
#else
		int n = ::recv(socketDescriptor(), &packet[read], readSize, 0);
#endif
       	if ( n == 0)
		{
            //printf("TcpSocket::recvPacket sockfd:%d disconnected read:%d\n",
			//	socketDescriptor(), read);
			close();
			if( read == 0 ) return -3;
			return read;
		}
        else if (n < 0)
        {
			if (errno == EWOULDBLOCK || errno == EINTR) 
			{
			#ifdef WIN32
				Sleep(1);
			#else
				usleep(1000);
			#endif
				//printf("TcpSocket::recvPacket sockfd:%d EWOULDBLOCK\n",
				//		socketDescriptor());
				continue;
			}
			else if (errno == ETIMEDOUT)
			{
				//printf("TcpSocket::recvPacket sockfd:%d packetSize:%d\n",
				//	socketDescriptor(), packetSize);
				//printf("TcpSocket::recvPacket sockfd:%d ETIMEDOUT read:%d\n",
				//	socketDescriptor(), read);
				//close();
				return -2;
			}

            //printf("TcpSocket::recvPacket Failed to read %d errno:%d "
			//	"read:%d\n", 
			//	n, errno, read);
			close();
            return -1;
		}

        remain -= n;
        read += n;

        //printf("TcpSocket::recvPacket %d byte(s) read\n", read);
    }

	//printf("TcpSocket::recvPacket() read = %d\n", read);
    return read;

}

/**
 * \brief 
 * \param host
 * \param port
 *
 * \return 0:ok -1:error -2:timeout
 */
int TcpSocket::connect(const char* host, int port)
{
	int sockfd = socketDescriptor();

	fd_set rset, wset;
	int flags=0;
	int n = 0;
	int error=0;
	int len;
	
	struct timeval tval;

	struct addrinfo hints, *res, *ressave;
    int ret = 0;
    memset(&hints, 0x00, sizeof(hints));
    hints.ai_family = PF_INET;
    hints.ai_socktype = SOCK_STREAM;

	if (timeout())
	{
#ifndef WIN32
		flags = fcntl(sockfd, F_GETFL, 0); 
		fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
#else
		int nonblocking =1;
		if (ioctlsocket(sockfd,FIONBIO, (u_long*)&nonblocking) == SOCKET_ERROR) 	
		{
			close();
			return -1;
		}
#endif
	}

	char portStr[1024];
	sprintf(portStr, "%d", port);
	if ( 0 != (ret = getaddrinfo(host, portStr, &hints, &res)) )
    {
		close();
        //fprintf(stderr, "%s", gai_strerror(ret));
        return -1;
    }

    ressave = res;

	n = ::connect(sockfd, res->ai_addr, res->ai_addrlen);
	//printf("TcpSocket::connect sockfd:%d n:%d\n", sockfd, n);
	freeaddrinfo(ressave);
	if(n < 0)
	{
#ifdef WIN32
        errno = WSAGetLastError();
#endif
		if (errno != EINPROGRESS && errno!= EWOULDBLOCK)
		{
			close();
			//printf("TcpSocket::connect sockfd:%d connect error:%d\n", 
			//	socketDescriptor(), n);
			return -1;
		}

		//printf("TcpSocket::connect sockfd:%d errno:%d\n",
		//	sockfd, errno);
	}
	else if(n == 0)
	{
		if (timeout())
		{
#ifndef WIN32
			fcntl(sockfd, F_SETFL, flags);
#else
			int nonblocking =0;
			if (ioctlsocket(sockfd,FIONBIO,(u_long*)&nonblocking) == SOCKET_ERROR)
			{
				close();
				return -1;
			}
#endif
		}

		//printf("TcpSocket::connect sockfd:%d connected...1\n", sockfd);
		d->connected = true;
		return 0;
	}

	if (timeout())
	{
		FD_ZERO(&rset);
		FD_SET(sockfd, &rset);
		wset = rset;
		tval.tv_sec = timeout();
		tval.tv_usec = 0;

		int selectRetn = select(sockfd + 1, &rset, &wset, 
			NULL, timeout() ? &tval : NULL);
		//printf("TcpSocket::connect sockfd:%d selectRetn:%d\n",
		//	sockfd, selectRetn);
		if (selectRetn == 0) 
		{
			//printf("TcpSocket::connect sockfd:%d select error(time out)\n",
			//	socketDescriptor());
			close();
			return -2;
		}
		else if (selectRetn < 0)
		{
			//printf("TcpSocket::connect sockfd:%d select error n:%d\n",
			//	socketDescriptor(), selectRetn);
			close();
			return -2;
		}

		if(FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) 
		{
			len = sizeof(error);
			if(getsockopt(sockfd, SOL_SOCKET, 
				SO_ERROR, (char*)&error, 
				(socklen_t*)&len) < 0) 
			{
				close();
				//printf("getsockopt error\n");
				return -1;
			}

			if (error)
			{
				close();
				//printf("TcpSocket::connect sockfd:%d error\n", sockfd);
				return -1;
			}
		}
		else
		{
			close();
			//printf("select error : sockfd not set\n");
			return -1;
		}

#ifndef WIN32
		fcntl(sockfd, F_SETFL, flags);
#else
		int nonblocking =0;
		if (ioctlsocket(sockfd,FIONBIO,(u_long*)&nonblocking) == SOCKET_ERROR)
		{
			close();
			return -1;
		}
#endif
	}

	//printf("TcpSocket::connect sockfd:%d connected...2\n", sockfd);
	d->connected = true;
	return 0; 
}

void TcpSocket::disconnect()
{
	close();
	d->connected = false;
}
} //namespace PD {

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
#include "PDUdpSocket.h"
#ifndef WIN32
#include <arpa/inet.h>
#include <netdb.h>
#endif
#include <stdio.h>
#include <string.h>
 
namespace PD {

UdpSocket::UdpSocket() : AbstractSocket(AbstractSocket::UdpSocket)
{
}

UdpSocket::UdpSocket(int sock) : AbstractSocket(sock, AbstractSocket::UdpSocket)
{
}

void UdpSocket::enableBroadcast()
{
	int one=1;
   	setsockopt(socketDescriptor(),SOL_SOCKET,SO_BROADCAST,(const char*)&one,sizeof(one));
}

/**
 * \brief sendPacket
 * \param packet
 * \param packetSize
 * \return -1:error
 */
int UdpSocket::sendBroadcast(const char* packet, size_t packetSize, int port)
{
	if (socketDescriptor() == -1) 
	{
		//printf("UdpSocket::sendBroadcast() socketDescriptor() Error!\n");
		return -1;
	}
	
	ignore_sigpipe();

	enableBroadcast();

	sockaddr_in sin;
	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	int n = ::sendto(socketDescriptor(), 
		packet, packetSize, 0, (sockaddr*)&sin, sizeof(sin));
	return n;
}

/**
 * \brief sendPacket
 * \param packet
 * \param packetSize
 * \return -1:error
 */
int UdpSocket::sendPacket(const char* packet, size_t packetSize,
	std::string host, int port)
{
	if (socketDescriptor() == -1) 
	{
		//printf("UdpSocket::sendPacket() socketDescriptor() Error!\n");
		return -1;
	}
	
	ignore_sigpipe();

	int ret = 0;
	struct addrinfo hints, *res, *ressave;
    memset(&hints, 0x00, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;

    //std::string tempPort = StringUtil::number(port);

	char tempPort[1024];
	snprintf(tempPort, sizeof(tempPort), "%d", port);
    if ( 0 != (ret = getaddrinfo(host.c_str(), tempPort, 
 		&hints, &res)) )
    {
        //printf("UdpSocket::sendPacket %s\n", gai_strerror(ret));
        return -1;
    }
	ressave = res;
	
	if ( !res )
	{
		freeaddrinfo(ressave);
        return -1;
	}

	ret = ::sendto(socketDescriptor(), packet, packetSize, 0, 
									res->ai_addr, res->ai_addrlen);
	freeaddrinfo(ressave);
	return ret;
}

int UdpSocket::recvPacket(char* packet, size_t packetSize,
	std::string& host, int& port)
{
	if (socketDescriptor() == -1) 
	{
		//printf("UdpSocket::recvPacket() socketDescriptor() Error!\n");
		return -1;
	}

	sockaddr_in sin;
	size_t sinSize = sizeof(sin);
	
#ifndef WIN32	
	int ret = ::recvfrom(socketDescriptor(), packet, packetSize,0,
								(sockaddr*)&sin, (socklen_t*)&sinSize);
#else
	int ret = ::recvfrom(socketDescriptor(), packet, packetSize,0,
								(sockaddr*)&sin, (int*)&sinSize);
#endif //#ifndef WIN32
	host = inet_ntoa(sin.sin_addr);
	port = ntohs(sin.sin_port);
	
	return ret;
}

bool UdpSocket::isReadable(unsigned long dwTimeout)
{
	timeval timeout;
	timeout.tv_sec = dwTimeout / 1000;
	timeout.tv_usec = dwTimeout % 1000;
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(socketDescriptor(), &fds);

	int ret = select(socketDescriptor()+1, &fds, NULL, NULL, &timeout);

	// ----------------------
	// ??È¯?? ????
	// ------ ---------------
	// -1     ?À·? ?ß»? 
	// 0      timeout(5??)
	// 1      descriptor ??È­
	// ----------------------
	if( ret == 0 || ret == -1 )
		return false;

	return true;
}

} //namespace PD {

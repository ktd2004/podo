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
#ifndef _PDABSTRACTSOCKET_H_
#define _PDABSTRACTSOCKET_H_

#ifndef WIN32
#include <sys/socket.h>
#else
#include <winsock2.h>
#include <Ws2tcpip.h>
#endif

#include <string>

namespace PD {

class AbstractSocketPrivate;

/**
 * \defgroup network
 */

/**
 * \brief Tcp, Udp Socket의 추상화 Class
 * \ingroup network
 */
class AbstractSocket
{
public:
	enum SocketType
	{
		TcpSocket=0,
		UdpSocket,
		UdsSocket
	};

private:
	AbstractSocketPrivate* d;

public:
	AbstractSocket(SocketType type);
	AbstractSocket(int sock, SocketType type);

	virtual ~AbstractSocket();

	void close();
	bool isClosed();

	int create();

	SocketType socketType();

	int socketDescriptor();
	void setSocketDescriptor(int sd);

	void setTimeout(int sec, int usec=0);
	int timeout();

	void setHost(const char* host);
	void setPort(int port);

	const char* host();
	int port();

	void setBlocking(bool f);

	int bytesAvailable();

	bool bind();
	bool listen();

	int timeoutProcess(bool read=true);	
};

extern void ignore_sigpipe();

} // namespace PD {

#endif

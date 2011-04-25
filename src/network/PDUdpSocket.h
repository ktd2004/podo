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
#ifndef _PDUDPSOCKET_H_
#define _PDUDPSOCKET_H_

#include "PDAbstractSocket.h"

namespace PD {

/**
 * \brief UdpSocket
 * \ingroup network
 */
class UdpSocket : public AbstractSocket
{
public:;
	UdpSocket();
	UdpSocket(int sock);

	bool isReadable(unsigned long dwTimeout);
	void enableBroadcast();

	int sendBroadcast(const char* packet, size_t packetSize, int port);
	int sendPacket(const char* packet, size_t packetSize, 
		std::string host, int port);
	int recvPacket(char* packet, size_t packetSize, 
		std::string& host, int& port);
};

} //namespace PD {

#endif

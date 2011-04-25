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
#include <stdio.h>
#include <stdlib.h>
#include <network/PDUdpSocket.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage: %s [port]\n", argv[0]);
		return -1;
	}

	std::string host = "127.0.0.1";
	int port = atoi(argv[1]);

	PD::UdpSocket udp;
	udp.setHost(host.c_str());
	udp.setPort(port);
	if (!udp.bind())
	{
		printf("Failed to bind\n");
		return -1;
	}

	char sendData[4];
	sendData[0] = 0x78;
	sendData[1] = 0x56;
	sendData[2] = 0x34;
	sendData[3] = 0x12;

	char recvData[4];

	while(1)
	{
		usleep(0);

		int n = udp.recvPacket((char*)&recvData, sizeof(recvData), host, port);
		printf("udpserver receive %d bytes from %s:%d\n",
			n, host.c_str(), port);

		n = udp.sendPacket((char*)&sendData, sizeof(sendData), host, port);
		printf("udpserver sent %d bytes to %s:%d\n", 
			n, host.c_str(), port);
	}

	return 0;
}

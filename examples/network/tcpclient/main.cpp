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
#include <network/PDTcpSocket.h>
#include <base/PDString.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {   
    	printf("usage: %s [host] [port]\n", argv[0]);
        return -1; 
    }   

    std::string host(argv[1]);

    bool f = true;
    int port = (int)PD::String::toNumber(argv[2], 10, &f);

	PD::TcpSocket sock;
	if (sock.connect(host.c_str(), port) == -1)
	{
		printf("failed to connect '%s:%d'\n", host.c_str(), port);
		return -1;
	}
	printf("connected.\n");

	std::string cmd = "GET / HTTP/1.1\r\n\r\n";
	sock.sendPacket(cmd.c_str(), cmd.size());

	char buf[1024];
	int n = sock.recvPacket(buf, sizeof(buf));
	if (n == -1)
	{
		printf("failed to receive n:%d\n", n);
		return -1;
	}
	printf("%s", buf);

	return 0;
}

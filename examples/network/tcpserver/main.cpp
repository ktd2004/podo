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
#include <network/PDTcpServer.h>
#include <base/PDString.h>

class Server : public PD::TcpServer
{
public:
	PD::TcpServerClient* newConnection(int socket);
	void clientProcess(PD::TcpServerClient* client);
};

PD::TcpServerClient* Server::newConnection(int socket)
{
	printf("Server::newConnection socket: %d\n", socket);
	PD::TcpServerClient* client = new PD::TcpServerClient(this, socket);
	if (client == 0)
	{
		printf("Server::newConnection failed to accept\n");
		return 0;
	}

	printf("Server::newConnection %s:%d\n", sock()->host(), sock()->port());

	client->socket()->setTimeout(5);
	client->socket()->setHost(sock()->host());
	client->socket()->setPort(sock()->port());

	return client;
}

void Server::clientProcess(PD::TcpServerClient* client)
{
	char buf[1];
	std::string msg = "Hello\n";

	while(1)
	{
		int retn = client->socket()->recvPacket(buf, sizeof(buf));
		if (retn == -1) 
		{
			printf("Server::clientProcess error\n");
			break;;
		}
		else if (retn == -2)
		{
			//timeout
			client->socket()->sendPacket(msg.c_str(), msg.size());
			printf("--> %s", msg.c_str());
			continue;
		}
		else if (retn == -3)
		{
			printf("disconnected\n");
			break;
		}

		printf("%s",buf);
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage: %s [port]\n", argv[0]);
		return -1;
	}

	bool f = true;
	int port = (int)PD::String::toNumber(argv[1], 10, &f);
	if (!f || port<1 || port>65535) 
	{
		printf("invalid port:%d\n", port);
		return -1;
	}

	Server server;
	if (!server.listen("127.0.0.1", port))
	{
		printf("failed to listen %d port\n", port);
		return -1;
	}

	while(1) 
	{
		sleep(1);
	}
	
	return 0;
}

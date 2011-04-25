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
#include "PDTcpServer.h"
#include "../base/PDMutexLocker.h"
#include "../base/PDFlagScoper.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <algorithm>

#ifndef WIN32
#include <unistd.h>
#else
#include <io.h>
#endif
 
namespace PD
{

class TcpServerClientPrivate
{
public:
	PD::TcpSocket* sock;
	TcpServer* server;
	int oldSockFd;

public:
	TcpServerClientPrivate(TcpServer* _server, int _sock) : server(_server)
	{
		sock = new PD::TcpSocket(_sock);
		oldSockFd = _sock;
	}

	~TcpServerClientPrivate()
	{
		if (sock) { sock->close(); delete sock; sock = NULL; }
	}

};

TcpServerClient::TcpServerClient(TcpServer* server, int sock) : Thread()
{
	d = new TcpServerClientPrivate(server, sock);
}

TcpServerClient::~TcpServerClient()
{
	//printf("TcpServerClient::~TcpServerClient sockfd:%d...START\n", d->oldSockFd);
	delete d;
	//printf("TcpServerClient::~TcpServerClient sockfd:%d...END\n", d->oldSockFd);
}

PD::TcpSocket* TcpServerClient::socket() { return d->sock; }
TcpServer* TcpServerClient::server() { return d->server; }

int TcpServerClient::oldSockFd() { return d->oldSockFd; }

bool TcpServerClient::isClose()
{
	if (d->sock && d->sock->socketDescriptor() == -1) return true;
	if (d->sock == NULL) return true;

	return false;
}

int TcpServerClient::run()
{
	assert(d->sock != 0);

	//int sock = d->sock->socketDescriptor();
	//printf("TcpServerClient::run sock:%d...START\n", sock); fflush(stdout);

	d->server->clientProcess(this);
	//printf("TcpServerClient::run sock:%d...1\n", sock); fflush(stdout);

#ifndef WIN32
	// avoid CLOSE_WAIT
	//shutdown(sock, SHUT_RDWR);
#endif
	if (d->sock) d->sock->close();
	//printf("TcpServerClient::run sock:%d...2\n", sock); fflush(stdout);
	//d->server->removeClient(this);

	//printf("TcpServerClient::run sock:%d...END\n", sock); fflush(stdout);

	return 0;
}


class TcpServerPrivate
{
public:
	int maxConnection;

	PD::TcpSocket* sock;

	PD::Mutex clientListMutex;
	bool useClientList;
	bool onDisconnecting;
	TcpServer::ClientList clientList;
	TcpServer::ClientList removeClientList;

public:
	TcpServerPrivate()
	{
		sock = 0;
		maxConnection = -1;

		useClientList = false;
		onDisconnecting = false;
	}
};



TcpServer::TcpServer(): Thread()
{
	d = new TcpServerPrivate;
}

TcpServer::~TcpServer()
{
	stop();
	wait();
	
	if (d->sock) 
	{
		delete d->sock;
		d->sock = 0;
	}

	disconnectAllCli();
}

PD::Mutex& TcpServer::clientListMutex() { return d->clientListMutex; }
bool& TcpServer::useClientList() { return d->useClientList; }
bool& TcpServer::onDisconnecting() { return d->onDisconnecting; }
TcpServer::ClientList& TcpServer::clientList() { return d->clientList; }
PD::TcpSocket* TcpServer::sock() { return d->sock; }

void TcpServer::setMaxConnection(int n) { d->maxConnection = n; }
int	TcpServer::maxConnection() { return d->maxConnection; } 

void TcpServer::stop()
{
	//printf("TcpServer::stop...START\n");
	Thread::stop();	
	//printf("TcpServer::stop...END\n");
}

void TcpServer::disconnectAllCli()
{
	//printf("TcpServer::disconnectAllCli...START %x\n", this);
	PD::MutexLocker ml(&d->clientListMutex);

	//if (useClientList())
	//	printf("***TcpServer::disconnectAllCli useClientList***\n\n\n");
	PD::FlagScoper fs(&d->onDisconnecting);

	ClientListIt it = d->clientList.begin();
	while (it != d->clientList.end())
	{
		TcpServerClient* client = *it;
		if (client)
		{
			client->stop();
			client->wait();
			//printf("TcpServer::disconnectAllCli sockfd:%d\n",
			//	client->oldSockFd());
			delete client;
		}

		it++;
	}
	d->clientList.clear();
	//printf("TcpServer::disconnectAllCli...END %x\n", this);
}

void TcpServer::chkDisconnectedCli()
{
	if (d->clientList.size() == 0) return;
	//if (d->removeClientList.size() == 0) return;
	//printf("TcpServer::chkDisconnectedCli...START\n");


	ClientList rList;
	ClientListIt it = d->clientList.begin();
	while (it != d->clientList.end())
	{
		TcpServerClient* client = *it;

		if (client && client->isClose())
		{
			rList.push_back(client);
		}

		it++;
	}

	if (rList.size() == 0) return;

	PD::MutexLocker ml(&d->clientListMutex);
	if (useClientList()) 
	{
		//printf("***TcpServer::chkDisconnectedCli useClientList***\n\n\n");
		return;
	}
	PD::FlagScoper fs(&d->onDisconnecting);

	//printf("TcpServer::chkDisconnectedCli...START %x\n", this);

	it = rList.begin();
	while (it != rList.end())
	{
		TcpServerClient* client = *it;

		if (client)
		{
			//printf("TcpServer::chkDisconnectedCli sockfd:%d\n",
			//	client->oldSockFd());
			client->stop();
			client->wait();
			d->clientList.remove(client);
			delete client;
		}

		it++;
	}

	//printf("TcpServer::chkDisconnectedCli...END %x\n", this);
}

TcpServer::ClientList TcpServer::removeClientList()
{
	PD::MutexLocker ml(&mutex());
	return d->removeClientList;
}

void TcpServer::deleteRemoveClient(TcpServerClient* s)
{
	if (s == 0) return;

	PD::MutexLocker ml(&mutex());
	d->removeClientList.remove(s);
}

TcpServerClient* TcpServer::findRemoveClient(TcpServerClient* s)
{
	if (s == 0) return 0;

	PD::MutexLocker ml(&mutex());

	ClientListIt removeIt = 
		std::find(d->removeClientList.begin(), d->removeClientList.end(), s);
	if (removeIt != d->removeClientList.end())
	{
		return *removeIt;
	}

	return 0;
}


void TcpServer::removeClient(TcpServerClient* s)
{
	if (s == 0) return;

	PD::MutexLocker ml(&mutex());
	d->removeClientList.push_back(s);
}

bool TcpServer::listen(const char* host, int port)
{
	if (d->sock)
	{
		d->sock->close();
		delete d->sock;
		d->sock = 0;
		disconnectAllCli();
	}

	d->sock = new PD::TcpSocket();

	d->sock->setTimeout(0, 0);

	d->sock->setHost(host);
	d->sock->setPort(port);

	if (!d->sock->bind())
	{
		//printf("TcpServer::listen failed to bind\n");
		return false;
	}

	if (!d->sock->listen())
	{
		//printf("TcpServer::listen failed to listen\n");
		delete d->sock; d->sock = NULL;
		return false;
	}

	//printf("TcpServer::listen %s:%d\n", host, port);

	start(LowestPriority);

	return true;
}

int TcpServer::curConnection()
{
	return d->clientList.size();
}

bool TcpServer::isAcceptClient()
{
	if (maxConnection() == -1) return true;

	//printf("TcpServer::isAcceptClient connect(cur:%d max:%d)\n", 
	//	curConnection()+1, maxConnection());
	if (curConnection() + 1 > maxConnection()) return false;

	return true;
}

int TcpServer::run()
{
	assert(d->sock != 0);
	//printf("TcpServer::run start\n"); fflush(stdout);

	while(1)
	{
		if (isStop()) 
		{
			//printf("TcpServer::run stop...2\n"); fflush(stdout);
			break;
		}

		//chkDisconnectedCli();

		serverProcess();

		int fd = d->sock->accept();	
		if (fd < 0) 
		{
#ifdef WIN32
			Sleep(0);
#else
			usleep(0);
#endif
			continue;
		}

		//printf("TcpServer::run incoming new client "
		//	"sockfd:%d peer(%s:%d)\n", fd, d->sock->host(), d->sock->port());

		TcpServerClient* c = newConnection(fd);
		if (c == NULL) 
		{
			//printf("TcpServer::run does not accept newConnection sockfd:%d\n", fd);
			//::close(fd);
			continue;
		}

		c->start(LowestPriority);

		PD::MutexLocker ml(&d->clientListMutex);
		d->clientList.push_back(c);

		//printf("TcpServer::run...2\n"); fflush(stdout);
	}
	
	//printf("TcpServer::run end\n"); fflush(stdout);
	return 0;
}

void TcpServer::clientProcess(TcpServerClient*) { }
void TcpServer::serverProcess() { }



} // namespace PD

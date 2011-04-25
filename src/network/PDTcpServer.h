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
#ifndef _PDTCPSERVER_H_
#define _PDTCPSERVER_H_

#include <list>
#include <assert.h>

#include "../base/PDMutex.h"
#include "../base/PDThread.h"
#include "PDTcpSocket.h"

namespace PD
{

class TcpServer;
class TcpServerClientPrivate;

/**
 * \brief tcp server client
 * \ingroup network
 */
class TcpServerClient : public Thread
{
private:
	TcpServerClientPrivate* d;

public:
	TcpServerClient(TcpServer* server, int sock);
	virtual ~TcpServerClient();

	PD::TcpSocket* socket();
	TcpServer* server();

	int oldSockFd();
	bool isClose();
	int run();
};

class TcpServerPrivate;
/**
 * \brief tcp server
 * \ingroup network
 */
class TcpServer : public PD::Thread
{
public:
	typedef std::list<TcpServerClient*> ClientList;
	typedef std::list<TcpServerClient*>::iterator ClientListIt;

private:
	TcpServerPrivate* d;

public:
	TcpServer();
	~TcpServer();

	PD::Mutex& clientListMutex();
	bool& useClientList();
	bool& onDisconnecting();
	ClientList& clientList();
	PD::TcpSocket* sock();

	void setMaxConnection(int n);
	int	maxConnection();

	virtual int curConnection();

	virtual void stop();
	bool listen(const char* host, int port);

	virtual bool isAcceptClient();

	int run();

	virtual TcpServerClient* newConnection(int socket) = 0;
	virtual void clientProcess(TcpServerClient*);
	virtual void serverProcess();

	virtual void disconnectAllCli();
	virtual void chkDisconnectedCli();

	ClientList removeClientList();
	void removeClient(TcpServerClient* s);
	TcpServerClient* findRemoveClient(TcpServerClient* s);
	void deleteRemoveClient(TcpServerClient* s);
};

} // namespace PD


#endif

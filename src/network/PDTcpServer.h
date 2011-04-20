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

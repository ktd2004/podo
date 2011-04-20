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

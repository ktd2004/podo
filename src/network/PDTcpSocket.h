#ifndef _PDTCPSOCKET_H_
#define _PDTCPSOCKET_H_

#include "PDAbstractSocket.h"
namespace PD {

class TcpSocketPrivate;

/**
 * \brief TcpSocket
 * \ingroup network
 */
class TcpSocket : public AbstractSocket
{
private:
	TcpSocketPrivate* d;

public:
	TcpSocket();
	TcpSocket(int sock);
	~TcpSocket();

	bool connected();

	int accept();
	int connect(const char *host, int port);
	void disconnect();
	
	int sendPacket(const char* packet, size_t packetSize);
	int recvPacket(char* packet, size_t packetSize);
};

} //namespace PD {

#endif

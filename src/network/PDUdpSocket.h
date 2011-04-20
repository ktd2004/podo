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

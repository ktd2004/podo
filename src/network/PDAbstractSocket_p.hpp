#ifndef _PDABSTRACTSOCKET_P_H_
#define _PDABSTRACTSOCKET_P_H_

namespace PD {

class AbstractSocketPrivate
{
public:
	std::string host;
	int port;

	AbstractSocket::SocketType socketType;
	int socketDescriptor;
	int timeout;
	int timeoutUsec;

public:
	AbstractSocketPrivate(AbstractSocket::SocketType _type)
	{
		socketDescriptor = -1;
		timeout = 0;
		timeoutUsec = 0;
		socketType = _type;
		port = 0;
	}

	AbstractSocketPrivate(int _sock, AbstractSocket::SocketType _type)
	{
		socketDescriptor = _sock;
		timeout = 0;
		timeoutUsec = 0;
		socketType = _type;
		port = 0;
	}
};

} // namespace PD {

#endif

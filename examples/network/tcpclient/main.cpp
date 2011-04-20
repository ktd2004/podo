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

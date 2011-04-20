#include <stdio.h>
#include <network/PDUdpSocket.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("usage: %s [host] [port]\n", argv[0]);
		return 0;
	}

	std::string host = argv[1];
	int port = atoi(argv[2]);

	PD::UdpSocket udp;
	udp.setHost(host.c_str());
	udp.setPort(port);

	char sendData[4];
	sendData[0] = 0x12;
	sendData[1] = 0x34;
	sendData[2] = 0x56;
	sendData[3] = 0x78;

	char recvData[4];

	while(1)
	{
		sleep(1);

		int n = udp.sendPacket((char*)&sendData, sizeof(sendData), host, port);
		if (n != sizeof(sendData)) continue;

		n = udp.recvPacket((char*)&recvData, sizeof(recvData), host, port);
		if (n != sizeof(recvData)) continue;

		printf("udpclient receive %d bytes from %s:%d\n", 
			n, host.c_str(), port);
		for (int i=0; i<n; i++) printf("%02X ", recvData[i]);
		printf("\n");
	}

	return 0;
}

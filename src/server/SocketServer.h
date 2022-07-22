#ifndef __SOCKETSERVER__
#define __SOCKETSERVER__
#include <netinet/in.h>

class SocketServer {
private:
	static const int PORT = 8080;
	int serverSocketFD, clientSocketFD;
	sockaddr_in servAddr, clientAddr;
	char buf[1024];
public:
	SocketServer();
	bool initSocket();
	void workThread();
	bool acceptSocket();
	void forkTest();
	~SocketServer();
};

#endif // !SOCKETSERVER
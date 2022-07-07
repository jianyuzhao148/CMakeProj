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
	bool acceptSocket();
	~SocketServer();
};
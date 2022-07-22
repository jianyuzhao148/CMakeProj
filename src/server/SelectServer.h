#ifndef __SELECTSERVER__
#define __SELECTSERVER__
#include <netinet/in.h>
class SelectServer {
private:
	static const int PORT = 8080;
	static const int BUFF_LEN = 1024;
	int svrSockFD, clientSockFD;
	sockaddr_in svrAddr, clientAddr;
public:
	void socketInit();
	void svrOnline();
};
#endif // !__SELECTSERVER__

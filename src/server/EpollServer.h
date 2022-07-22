#ifndef __EPOLLSERVER__
#define __EPOLLSERVER__
#include <sys/epoll.h>

class EpollServer {
private:
	static const long EPOLL_SIZE = 10000;
	int serverFD, clientFD, epollFD;
public:
	EpollServer();
	bool socketInit();
	bool epollListen();
};
#endif // !__EPOLLSERVER__

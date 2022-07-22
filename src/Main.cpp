#include "algorithm/BinarySearch.h"
#include "server/SocketServer.h"
#include "server/DBServer.h"
#include "server/EpollServer.h"
#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>
#include <pthread.h>
#include <sys/signal.h>
#include "server/MyString.h"
#include <bits/socket.h>
#include "server/SelectServer.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
	/*int *list = new int[6]{1, 5, 30, 33, 45, 201};
	BinarySearch *binarySearch = new BinarySearch();
	int index = binarySearch->allInclude(list, 6, 30);
	std::cout << index << std::endl;
	delete binarySearch;
	delete[] list;*/

	//SocketServer* socketServer = new SocketServer();

	//DBServer* dbServer = new DBServer();
	//if (dbServer->connectMysql()) {
	//	dbServer->excuteSQL("select * from user");
	//}
	//if (dbServer->connectRedis()) {
	//	dbServer->setString("name", "zhaojyu");
	//}

	//EpollServer* epollServer = new EpollServer();

	//pthread_t tid = pthread_self();
	//sigset_t mask;
	//sigemptyset(&mask);
	//sigaddset(&mask, SIGINT);
	//int ctid = pthread_sigmask(SIG_SETMASK, &mask, NULL);
	//printf("main %d,%d thread working!\n", tid, ctid);
	//sleep(10);
	//printf("main %d,%d thread will kill\n", tid, ctid);
	//return 0;

	//MyString* myString = new MyString("stest");
	//printf("%s", myString->GetCString());
	//MyString* myString2 = new MyString(*myString);
	//printf("%s", myString2->GetCString());
	//myString = myString;
	//printf("%s", myString->GetCString());
	//SelectServer* server = new SelectServer();
	//server->socketInit();
	//server->svrOnline();

	//以非阻塞模式、可读可写 模式打开文件
	//char buffer[2048];
	//bzero(&buffer, sizeof(buffer));
	//int fd = open("/home/zhaojyu/test", O_RDONLY | O_NONBLOCK);
	//int len = read(fd, &buffer, sizeof(buffer));
	//if (len >= 0) {
	//	printf("%d,%s\n", len, buffer);
	//}
	//else {
	//	printf("%d\n", errno);
	//}
	//close(fd);
}
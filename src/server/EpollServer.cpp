#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <string.h>
#include "EpollServer.h"
#include <errno.h>

EpollServer::EpollServer() {
	if (socketInit()) {
		epollListen();
	}
}

bool EpollServer::socketInit() {
	sockaddr_in serverAddr;
	if ((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Create Scoket Error!\n");
		return false;
	}
	int on = 1;
	if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
		perror("Socket Opt Error!\n");
		return false;
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(8080);

	if (bind(serverFD, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){
		printf("Scoket Bind Error!\n");
		return false;
	}

	if (listen(serverFD, 1000) == -1) {
		printf("Scoket Listen error!\n");
		return false;
	}
	return true;
}

bool EpollServer::epollListen() {
	sockaddr_in  clientAddr;
	epoll_event ev;
	epoll_event evs[EPOLL_SIZE];
	int okfd;
	char buff[1024];

	socklen_t len = sizeof(clientAddr);
	epollFD = epoll_create(EPOLL_SIZE);
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = serverFD;
	if (epoll_ctl(epollFD, EPOLL_CTL_ADD, serverFD, &ev) < 0) {
		printf("Epoll epoll_ctl error!\n");
		return false;
	}
	while (true) {
		if ((okfd = epoll_wait(epollFD, evs, EPOLL_SIZE, -1)) == -1) {
			printf("Epoll epoll_wait error! %d\n", errno);
			return false;
		}
		for (int i = 0; i < okfd; i++) {
			if (evs[i].data.fd == serverFD) {
				clientFD = accept(serverFD, (sockaddr*)&clientAddr, &len);
				ev.data.fd = clientFD;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epollFD, EPOLL_CTL_ADD, clientFD, &ev);
			}
			recv(evs[i].data.fd, buff, sizeof(buff), 0);
			printf("MSG: %s\n", buff);
			send(clientFD, buff, sizeof(buff), 0);
			epoll_ctl(epollFD, EPOLL_CTL_DEL, clientFD, &ev);
		}
	}
}
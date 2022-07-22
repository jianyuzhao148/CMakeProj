#include "SelectServer.h"
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>

void SelectServer::svrOnline() {
	int result = listen(svrSockFD, 5);
	assert(result >= 0);
	unsigned int clientSockLen = 0;
	int msgLen = 0;
	char buffer[BUFF_LEN];
	char response[] = "HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n"
		"<!DOCTYPE html>"
		"<html lang=\"zh-CN\">"
		"<head>"
		"<meta charset=\"utf-8\">"
		"<title>Hello World</title>"
		"<style>body {width: 35em;margin: 200px auto;font-family: Tahoma, Verdana, Arial, sans-serif;}"
		"</style>"
		"</head>"
		"<body>"
		"<h1>...</h>";
	"<p>This is a simple webserver<p>"
		"</body></html>\r\n";

	epoll_event events[10];
	int epollFD = epoll_create(5);
	
	while (true) {
		clientSockLen = sizeof(clientAddr);
		clientSockFD = accept(svrSockFD, (sockaddr*)&clientAddr, &clientSockLen);
		bzero(buffer, BUFF_LEN - 1);
		msgLen = recv(clientSockFD, buffer, BUFF_LEN - 1, 0);
		printf("MSG Leng is %d ,MSG is :\n %s", msgLen, buffer);
		send(clientSockFD, response, sizeof(response), 0);
		close(clientSockFD);
	}
	close(svrSockFD);
}

void SelectServer::socketInit() {
	bzero(&svrAddr, sizeof(svrAddr));
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(PORT);
	svrAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	svrSockFD = socket(AF_INET, SOCK_STREAM, 0);
	assert(svrSockFD >= 0);

	int result = bind(svrSockFD, (sockaddr*)&svrAddr, sizeof(svrAddr));
	assert(result >= 0);
}
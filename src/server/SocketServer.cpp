#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include "SocketServer.h"

bool SocketServer::initSocket() {
	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	serverSocketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (bind(serverSocketFD, (sockaddr*)&servAddr, sizeof(servAddr)) < 0 || listen(serverSocketFD, 20) < 0)
		return false;

	printf("Server Online ...\n");
	return true;
}

void* workThread(int clientFD) {
	char url[255];
	char buf[1024];
	//获取一行请求头
	int numchars = getHeaderLine(*clientFD, buf, sizeof(buf));
	int i = 0, j = 0;
	char method[255];
	//获取第一个space之前的字符串，就是请求方法
	while (!isspace(buf[j]) && (i < sizeof(method) - 1))
	{
		method[i] = buf[j];
		i++; j++;
	}
	method[i] = '\0';
	printf("Parse Request Method:%s\n", method);
	if (strcasecmp(method, "POST") && strcasecmp(method, "GET")) {
		printf("Error Method ,Nothing To Do!\n");
		return;
	}

	//解析POST请求
	if (strcasecmp(method, "POST") == 0) {
		printf("POST Method Do It!\n");
	}

	//解析URL
	//忽略space
	while (isspace(buf[j]) && (j < sizeof(buf) - 1)) {
		j++;
	}
	i = 0;
	while (!isspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf) - 1)) {
		url[i] = buf[j];
		i++; j++;
	}
	url[i] = '\0';

	printf("Parse URL:%s \n", url);

	//解析GET请求
	if (strcasecmp(method, "GET") == 0) {
		printf("GET Method Do It!\n");
		//制作响应头
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
			"<h1>...</h>"
			"<p>This is a simple webserver<p>"
			"</body></html>\r\n";

		send(clientFD, response, sizeof(response), 0);
	}
}

bool SocketServer::acceptSocket() {
	pthread_t newthread;

	while (true) {
		socklen_t  clientAddSize = sizeof(clientAddr);
		//获取客户端连接
		clientSocketFD = accept(serverSocketFD, (sockaddr*)&clientAddr, &clientAddSize);
		pthread_create(&newthread, NULL, workThread, clientSocketFD);


		close(clientSocketFD);
	}
}

int getHeaderLine(int sock, char* buf, int size) {
	int i = 0;
	char c = '\0';
	int n;

	//i在buf数组下标中（表示未越界）
	//c不为\n（http请求使用/r/n结尾 表示该行未结束）
	while ((i < size - 1) && (c != '\n'))
	{
		n = recv(sock, &c, 1, 0);//接收一个字符 存入c
		/* DEBUG printf("%02X\n", c); */
		if (n > 0)//接收成功
		{
			//printf("recv one char:%c\n", c);
			if (c == '\r')
			{
				n = recv(sock, &c, 1, MSG_PEEK);
				//printf("recv \\r recv one char:%c\n", c);
				/* DEBUG printf("%02X\n", c); */
				if ((n > 0) && (c == '\n')) {
					recv(sock, &c, 1, 0);
					//printf("recv \\r recv one char last:%c\n", c);
				}
				else
					c = '\n';
			}
			buf[i] = c;
			i++;
		}
		else
			c = '\n';
	}
	buf[i] = '\0';
	return i;
}

SocketServer::SocketServer() {
	if (!initSocket()) {
		printf("Error : Socket Server Init Faild\n");
		return;
	}
	acceptSocket();
}

SocketServer::~SocketServer() {

}
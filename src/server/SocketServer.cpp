#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include "SocketServer.h"
#include <errno.h>
#include <assert.h>
#include <sys/epoll.h>
int getHeaderLine(int sock, char* buf, int size);

bool SocketServer::initSocket() {
	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);//ת���ֽ���
	servAddr.sin_port = htons(PORT);

	serverSocketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (bind(serverSocketFD, (sockaddr*)&servAddr, sizeof(servAddr)) < 0 || listen(serverSocketFD, 20) < 0)
		return false;

	printf("Server Online ...\n");
	return true;
}

void SocketServer::workThread() {
	char url[255];
	char buf[1024];
	//��ȡһ������ͷ
	int numchars = getHeaderLine(clientSocketFD, buf, sizeof(buf));
	int i = 0, j = 0;
	char method[255];
	//��ȡ��һ��space֮ǰ���ַ������������󷽷�
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

	//����POST����
	if (strcasecmp(method, "POST") == 0) {
		printf("POST Method Do It!\n");
	}

	//����URL
	//����space
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

	//����GET����
	if (strcasecmp(method, "GET") == 0) {
		printf("GET Method Do It!\n");
		//������Ӧͷ
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

		send(clientSocketFD, response, sizeof(response), 0);
	}
	_exit(0);
}

bool SocketServer::acceptSocket() {
	pthread_t newthread;

	while (true) {
		socklen_t  clientAddSize = sizeof(clientAddr);
		//��ȡ�ͻ�������
		clientSocketFD = accept(serverSocketFD, (sockaddr*)&clientAddr, &clientAddSize);
		//int result = pthread_create(&newthread, NULL, workThread, &clientSocketFD);
		int pid = fork();//�����̲����ӽ��̣���ȡ�ӽ���pid
		if (pid == 0) {//���ӽ�����
			workThread();
		}
		else if (pid > 0) {//�ڸ�������
			close(clientSocketFD);
		}
		close(clientSocketFD);
	}
}

int getHeaderLine(int sock, char* buf, int size) {
	int i = 0;
	char c = '\0';
	int n;

	//i��buf�����±��У���ʾδԽ�磩
	//c��Ϊ\n��http����ʹ��/r/n��β ��ʾ����δ������
	while ((i < size - 1) && (c != '\n'))
	{
		n = recv(sock, &c, 1, 0);//����һ���ַ� ����c
		/* DEBUG printf("%02X\n", c); */
		if (n > 0)//���ճɹ�
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
	//forkTest();
}

void SocketServer::forkTest() {
	int childPid = fork();//ʹ��fork�����ӽ���
	printf("execute preccess \n");

	if (childPid == 0) {
		printf("main preccess \n");
	}
	else if (childPid > 0) {
		printf("child preccess\n");
	}
	else {
		printf("Fork Error \n");
	}
}

SocketServer::~SocketServer() {

}

bool stop = true;

void signalHandle(int sig) {
	std::cout << sig << std::endl;
	stop = false;
}

void initSocket() {
	signal(SIGTERM, signalHandle);//�źŴ�����
	int sockFD = socket(PF_INET, SOCK_STREAM, 0);
	assert(sockFD >= 0);
	sockaddr_in sockAddr;
	bzero(&sockAddr, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockAddr.sin_port = htons(8080);
	//inet_pton(AF_INET, "", &sockAddr.sin_addr);
	// ��socket��socket��ַ
	if (bind(sockFD, (const sockaddr*)&sockAddr, sizeof(sockAddr)) == -1) {
		std::cout << "Bind Socket Error:" << errno << std::endl;
	}
	if (listen(sockFD, 5) == -1) {
		std::cout << "Listen Socket Error:" << errno << std::endl;
	}
	std::cout << "Server Online" << std::endl;


	while (stop) {
		std::cout << "While Print..." << std::endl;
		sleep(1);
	}
	close(sockFD);
}

int main(int argc, char* argv[]) {
	int sockFD = socket(PF_INET, SOCK_STREAM, 0);
	assert(sockFD >= 0);
	sockaddr_in sockAddr;
	bzero(&sockAddr, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockAddr.sin_port = htons(8080);
	bind(sockFD, (sockaddr*)&sockAddr, sizeof(sockAddr));
	listen(sockFD, 5);
	sockaddr svrAddr;
	unsigned int addrLen2;
	getsockname(sockFD, &svrAddr, &addrLen2);
	std::cout << "Server Online" << svrAddr.sa_data << std::endl;
	sockaddr_in clientAddr;
	unsigned int addrLen = sizeof(clientAddr);
	int clienSockFD;
	int msgLen;
	while (true)
	{
		//��д����
		clienSockFD = accept(sockFD, (sockaddr*)&clientAddr, &addrLen);
		char buffer[1024];
		memset(buffer, '\0', 1024);
		msgLen = recv(clienSockFD, buffer, 1024 - 1, 0);
		printf("%d,%s", msgLen, buffer);
		memset(buffer, '\0', 1024);
		msgLen = recv(clienSockFD, buffer, 1024 - 1, MSG_OOB);
		printf("%d,%s", msgLen, buffer);
		close(clienSockFD);
	}
	close(sockFD);
	return 0;
}

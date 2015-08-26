#include <windows.h>
#include <cstdio>
#include <cstring>
#include "tcp_client.hpp"
	
int main()
{
	WSADATA wsadata;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (ret != NO_ERROR) {
		fprintf(stderr, "tcp client initialization failed: %d", ret);
		return -1;
	}
	
	rabbit::tcp_client client;
	client.connect("127.0.0.1", 65534);
	printf("tcp client connected...\n");
	int cur_time = 0;
	char msg[200];
	while (true) {
		sprintf(msg, "Hello server I am client! time: %d ", cur_time);
		printf("send message %s to server\n", msg);
		client.send((char*)msg, strlen(msg));
		cur_time += 1;
		Sleep(1000);
	}
	client.close();
	
	WSACleanup();
	return 0;
}

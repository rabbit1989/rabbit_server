#include <cstdio>
#include <cstring>
#include "tcp_client.hpp"
#if defined(WIN32)
	#include <windows.h>
#else
	#include <unistd.h>
#endif	

int main()
{

	#if defined(WIN32)
		WSADATA wsadata;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (ret != NO_ERROR) {
			fprintf(stderr, "tcp client initialization failed: %d", ret);
			return -1;
		}
	
	#endif
	
	rabbit::tcp_client client;
	client.connect("127.0.0.1", 65534);
	printf("tcp client connected...\n");
	int cur_time = 0;
	char msg[200];
	while (true) {
		sprintf(msg, "Hello server I am client! time: %d ", cur_time);
		fprintf(stderr, "send message %s to server\n", msg);
		client.send((char*)msg, strlen(msg));
		cur_time += 1;
		#if defined(WIN32)
			Sleep(1000);
		#else
			sleep(1);
		#endif
	}
	client.close();
	
	#if defined(WIN32)
		WSACleanup();
	#else
		sleep(1);
	#endif
	
	return 0;
}

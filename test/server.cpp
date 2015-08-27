#include "tcp_server.hpp"

int main(){

	#if defined(WIN32)
		WSADATA wsaData;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (ret != NO_ERROR) {
			fprintf(stderr, "winsock initialization failed: %d", ret);
		}
	#endif

	rabbit::tcp_server simple_server(10);
	simple_server.init("127.0.0.1", 65534);
	printf("tcp server started....\n");
	simple_server.run();
	simple_server.close();
	
	#if defined(WIN32)
		WSACleanup();
	#endif
	return 0;
}
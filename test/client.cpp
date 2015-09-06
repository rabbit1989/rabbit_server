#include <cstdio>
#include <cstring>

#include "tcp_client.hpp"
#include "env_init.hpp"

int main()
{

	// must be called before any operations
	init_env();

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
	
	//must be called when all operations finished
	destroy_env();

	return 0;
}

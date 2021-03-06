#include <cstdio>
#include <cstring>

#include "tcp_client.hpp"
#include "env_init.hpp"
#include "utils/sys_call_wrapper.hpp"

int main()
{

	// must be called before any operations
	rabbit::init_env();

	rabbit::tcp_client client;
	client.connect("127.0.0.1", 65534);
	printf("tcp client connected...\n");
	int cur_time = 0;
	char msg[200];
	while (true) {
		sprintf(msg, "Hello server I am client! time: %d ", cur_time);
		fprintf(stderr, "send message %s to server\n", msg);
		int bytes = client.send((char*)msg, strlen(msg));
		fprintf(stderr, "num bytes sent: %d\n", bytes);		
		cur_time += 1;
		rabbit::sleep(1000);
	}
	client.close();
	
	//must be called when all operations finished
	rabbit::destroy_env();

	return 0;
}


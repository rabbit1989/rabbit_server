#include <cstdio>

#include "tcp_server.hpp"
#include "env_init.hpp"

int main(){

	//must be called before any operations
	rabbit::init_env();

	rabbit::tcp_server simple_server(10);
	simple_server.init("127.0.0.1", 65534);
	printf("tcp server started....\n");
	simple_server.run();
	simple_server.close();
	
	//must be called when all operations finished
	rabbit::destroy_env();

	return 0;
}

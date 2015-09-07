#include "rpc_server.hpp"
#include "simple_coder.hpp"
#include "env_init.hpp"

int main(){
	env_init();
	
	rabbit::rpc_server server;
	rabbit::simlpe_coder *coder = new simple_coder;
	server.init("127.0.0.1", 12345);
	server.set_rpc_coder(simple_coder);
	server.run();

	env_destroy();
	return 0;	
}
#include "rpc/rpc_server.hpp"
#include "rpc/simple_coder.hpp"
#include "base/env_init.hpp"

int main(){
	rabbit::init_env();
	
	rabbit::rpc_server server;
	rabbit::simple_coder *coder = new rabbit::simple_coder;
	server.init("127.0.0.1", 12345);
	server.set_rpc_coder(coder);
	server.run();
	delete coder;
	rabbit::destroy_env();
	return 0;	
}

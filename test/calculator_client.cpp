#include "rpc/simple_channel.hpp"
#include "rpc/simple_coder.hpp"
#include "base/env_init.hpp"
#include "utils/sys_call_wrapper.hpp"

int main(){
	rabbit::init_env();

	rabbit::simple_channel client;
	rabbit::simple_coder *rpc_coder = new rabbit::simple_coder;
	client.init("127.0.0.1", 12345);
	client.set_rpc_coder(rpc_coder);
	for (int i = 0; i < 100; i++)
	{
		// the last number is the delimiter
		client.rpc_call("calculate_add", i, i, -1);
		client.rpc_response();
		rabbit::sleep(1000);	
	}
	delete rpc_coder;

	rabbit::destroy_env();
	
	return 0;
}

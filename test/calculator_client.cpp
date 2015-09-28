#include <cstdio>

#include "rpc/rpc_channel.hpp"
#include "rpc/simple_coder.hpp"
#include "base/env_init.hpp"
#include "utils/sys_call_wrapper.hpp"

int main(){
	rabbit::init_env();

	rabbit::rpc_channel client;
	rabbit::simple_coder *rpc_coder = new rabbit::simple_coder;
	client.init("127.0.0.1", 12345);
	client.set_rpc_coder(rpc_coder);
	for (int i = 0; i < 100; i++)
	{
		// the last number is the delimiter
		if (i % 2 == 0) {
			fprintf(stderr, "calculate add(%d, %d)...\n", i, 100-i);
			client.rpc_call("calculate_add", i, 100-i);
		}
		else {
			fprintf(stderr, "cal max(%d, %d)...\n", i, 100-i);
			client.rpc_call("cal_max", i, 100-i);
		}
		client.rpc_response();
		rabbit::sleep(1000);	
	}
	delete rpc_coder;

	rabbit::destroy_env();
	
	return 0;
}

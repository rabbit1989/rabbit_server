#if defined(WIN32)
	#include <windows.h>
#else
	#include <unistd.h>
#endif

#include "simple_channel.hpp"
#include "simple_coder.hpp"
#include "env_init.hpp"

int main(){
	env_init();

	rabbit::simple_channel client();
	rabbit::simple_coder *rpc_coder = new simple_coder;
	client.init("127.0.0.1", 12345);
	client.set_rpc_coder(rpc_coder);
	for (int i = 0; i < 100; i++)
	{
		client.rpc_call("calculate_add", i, i);
		client.rpc_response();
		
		#if defined(WIN32)
			Sleep(1000);
		#else
			sleep(1);
		#endif
	}
	delete simple_coder;
	env_destroy();
	
	return 0;
}
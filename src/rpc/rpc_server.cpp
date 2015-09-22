/********************************************************************************************
Copyright (C) rabbit1989 2015

https://github.com/rabbit1989/rabbit_server

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*******************************************************************************************
       					simple rpc server
*******************************************************************************************/
#include <cstdio>
#include <cstdlib>
#include "rpc_server.hpp"
#include "utils/sys_call_wrapper.hpp"
#include "rpc/simple_channel.hpp"

namespace rabbit{

const int MAX_NUM_CHANNEL = 50;

rpc_server::rpc_server(){
	_channel_list = (rpc_channel**)malloc(sizeof(rpc_channel*) * MAX_NUM_CHANNEL);
	_num_channel = 0;
}

rpc_server::~rpc_server() {
	if (_channel_list != 0) {
		for (int i = 0; i < _num_channel; i++) 
			delete _channel_list[i];
		free(_channel_list);
	}
	_server.close();
}

void rpc_server::init(const std::string &addr, const int port) {
	_server.init(addr, port);
}

void rpc_server::run() {
	while (true) {
		_server.loop();
		if (_server.has_new_connection()) {				
			add_channel(_server.get_new_connection());
		}
		for (int i = 0; i < _num_channel; i++) {			
			_channel_list[i]->rpc_response();
		}
		sleep(1000);
	}
}

void rpc_server::add_channel(const tcp_client& client) {
	if (_num_channel >= MAX_NUM_CHANNEL) {
		fprintf(stderr, "rpc_server::add_channel(): number of channel reaches maximum!!\n");
		return;
	}
	_channel_list[_num_channel] = new simple_channel;
	_channel_list[_num_channel]->set_client(client);
	_channel_list[_num_channel]->set_rpc_coder(_rpc_coder);
	_num_channel++;
}

void rpc_server::close() {
	_server.close();
	if (_channel_list != 0) {
		for (int i = 0; i < _num_channel; i++)
			_channel_list[i]->close();
	}

}

void rpc_server::set_rpc_coder(rpc_coder_base *rpc_coder) {
	_rpc_coder = rpc_coder;
}

}

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
       					implementation of a simple rpc channel
*******************************************************************************************/
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>

#include "rpc/rpc_channel.hpp"
#include "utils/type.hpp"
#include "rpc/rpc_commands.hpp"

namespace rabbit{

rpc_channel::rpc_channel():_buff_len(0){
	reg_rpc_commands();
};

rpc_channel::rpc_channel(tcp_client& client):_client(client), _buff_len(0){
	reg_rpc_commands();
};

rpc_channel::~rpc_channel(){
	std::map<std::string, rpc_command*>::iterator iter = _rc_map.begin();
	std::map<std::string, rpc_command*>::iterator it_end= _rc_map.end();
	for (;iter != it_end; iter++) {
		delete iter->second;
	}
};

void rpc_channel::reg_rpc_commands() {
	rpc_command *rc1 = new rc_calculate_add;
	_rc_map["calculate_add"] = rc1;

	rpc_command *rc2 = new rc_on_calculate_add;
	_rc_map["on_calculate_add"] = rc2;

	rpc_command *rc3 = new rc_cal_max;
	_rc_map["cal_max"] = rc3;

	rpc_command *rc4 = new rc_on_cal_max;
	_rc_map["on_cal_max"] = rc4;
}

void rpc_channel::init(const std::string& ip, int port){
	//configure network setting
	_client.connect(ip, port);	
}

void rpc_channel::push_rpc_args(){
	while (!_args_stack.empty()) {
		_args_stack.pop();
	}
}

void rpc_channel::rpc_response() {
	int num_bytes = _client.read(_read_buff + _buff_len, 300-_buff_len);
	_buff_len += num_bytes;
	if (_buff_len && _read_buff[0] == '#') {
		int i = 1;
		for (i = 1; i < _buff_len; i++)
			if (_read_buff[i] == '#')
				break;

		if (i != _buff_len) {
			std::vector<data_struct> para = _rpc_coder->decode(std::string(_read_buff+1, i-1));				
			std::string func_name = from_data_struct<std::string>(para[0]);
			std::vector<data_struct> para_list = std::vector<data_struct>(para.begin()+1, para.end());

			if (_rc_map.find(func_name) != _rc_map.end()) {
		//		fprintf(stderr, "rpc_channel::rpc_response(): rpc call %s find!\n", func_name.c_str());	
				_rc_map[func_name]->execute(para_list, this);
			}
			else {
				fprintf(stderr, "rpc_channel::rpc_response(): unknown rpc call: %s\n", func_name.c_str());
			}

			//move the rest data in _read_buff to the front
			for (int j = i+1; j < _buff_len; j++)
				_read_buff[j-i-1] = _read_buff[j];
			_buff_len -= (i+1);
		}
	}
}

void rpc_channel::set_rpc_coder(rpc_coder_base *coder) {
	_rpc_coder = coder;
}

void rpc_channel::set_client(const tcp_client &client) {
	_client = client;
}

void rpc_channel::close() {
	_client.close();
}

}

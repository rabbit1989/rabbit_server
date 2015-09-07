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
#include <pair>
#include <cstdlib>
#include "rpc_channel.hpp"

namespace rabbit{

void rpc_channel::init(const string ip, int port){
	_client.connect(ip, port);
}

void rpc_channel::rpc_call(const char* func_name, ...){
	va_list args;
    va_start(args, func_name);
    string msg = _rpc_coder->encode(args);
    _client.write(msg.c_str(), strlen(msg.c_str));
    va_end(args);
}

void rpc_channel::rpc_response() {
	int num_bytes = _client.read(_read_buff + _buff_len, 300-_buff_len);
	_buff_len += num_bytes;
	if (_read_buff[0] == '#') {
		int i = 1;
		for (i = 1; i < _buff_len; i++)
			if (_read_buff[i] == '#')
				break;
		if (i != _buff_len) {
			std::pair<std::string, std::vector<std::string> >para = _rpc_coder->decode(_read_buff+1, _read_buff+i);				
			std::string func_name = para.first;
			std::vector<std::string> para_list = para.second;			
			_func_map[func_name](this, atoi(para_list[0].c_str()), atoi(para_list[1].c_str());
			
			//move the rest data in _read_buff to the front
			for (int j = i+1; j < _buff_len; j++)
				_read_buff[j-i-1] = _read_buff[j];
			_buff_len -= (i+1);
		}
	}
}

void rpc_channel::register_func(std::string func_name, rpc_channel::func_ptr ptr){
	_func_map[func_name] = ptr;
}

void rpc_channel::set_rpc_coder(rpc_coder_base *coder) {
	_rpc_coder = coder;
}

void rpc_channel::set_client(tcp_client &client) {
	_client = client;
}
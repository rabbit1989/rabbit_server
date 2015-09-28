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
       						header of rpc channel
*******************************************************************************************/



#ifndef RPC_CHANNEL_HPP
#define RPC_CHANNEL_HPP

#include <map>
#include <string>
#include <stack>

#include "base/tcp_client.hpp"
#include "rpc/rpc_coder.hpp"
#include "utils/type.hpp"
#include "utils/uncopyable.hpp"

namespace rabbit{

class rpc_command;
class rpc_channel: uncopyable {
public:

	rpc_channel();
	rpc_channel(tcp_client& client);
	~rpc_channel();

	void init(const std::string&, int);
	void reg_rpc_commands();

	//call rpc method
	template<typename...args>
	void rpc_call(args...);

	//receive data and execute rpc method
	void rpc_response();
	
	void set_rpc_coder(rpc_coder_base*);
	
	void set_client(const tcp_client&);
	void close();

private:

	// use variadic template to push variable number of paramenters into stack
	template<typename T,  typename...args>
	void push_rpc_args(const T&, args...);
	void push_rpc_args();

private:
	tcp_client _client;
	std::map<std::string, rpc_command*> _rc_map;
	rpc_coder_base *_rpc_coder;	

	// rpc argument stack 
	std::stack<data_struct> _args_stack;

	//the buffer will be removed later
	char _read_buff[300];
	int _buff_len;
};

template<typename... args>
void rpc_channel::rpc_call(args... para){
	push_rpc_args(para...);
	std::string msg = _rpc_coder->encode(_args_stack);
    _client.write(msg.c_str(), msg.length());
}

template<typename T, typename... args>
void rpc_channel::push_rpc_args(const T& value, args... para){
	push_rpc_args(para...);
	_args_stack.push(to_data_struct(value));
}
}

#endif

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

namespace rabbit{

#include <map>
#include <string>

#include "uncopyable.hpp"
#include "tcp_client.hpp"
#include "rpc_coder.hpp"

class rpc_channel: uncopyable{
public:
	void init(const std::string, int);

	//call rpc method
	void rpc_call(const char*, ...);	
	
	//receive data and execute rpc method
	void rpc_response();
	
	//register rpc methods
	void register_func(const std::string);	

	void set_rpc_coder(rpc_coder_base*);
private:
	tcp_client _client;
	map<std::string, > _func_map;
	rpc_coder_base *_rpc_coder;
};

}

#endif
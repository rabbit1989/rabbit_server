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

#include "rpc_channel.hpp"

namespace rabbit{

void rpc_channel::init(const string ip, int port){
	_client.connect(ip, port);
}

void rpc_channel::rpc_call(const char* func_name, ...){
	va_list args;
    va_start(args, format_str);
    string msg = _rpc_coder->encode(args);
    _client.write(msg.c_str(), strlen(msg.c_str));
    va_end(args);
}

void rpc_channel::rpc_response() {

}

void rpc_channel::register_func(std::string func_name){

}

void rpc_channel::set_rpc_coder(rpc_coder_base *coder){
	_rpc_coder = coder;
}

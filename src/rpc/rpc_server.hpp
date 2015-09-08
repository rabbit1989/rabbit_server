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

#ifndef RPC_SERVER_HPP
#define RPC_SERVER_HPP

#include <string>

#include "rpc/rpc_channel.hpp"
#include "rpc/rpc_coder.hpp"
#include "base/tcp_server.hpp"
#include "utils/uncopyable.hpp"

namespace rabbit {

class rpc_server : public uncopyable {
public:
	rpc_server();
	virtual ~rpc_server();
	void init(const std::string&, const int);
	void run();
	void close();
	void add_channel(const tcp_client&);
	void set_rpc_coder(rpc_coder_base*);
private:
	rpc_channel **_channel_list;
	int _num_channel;
	tcp_server _server;
	rpc_coder_base* _rpc_coder;
};

}

#endif

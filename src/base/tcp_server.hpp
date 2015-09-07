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
       				header file of nonblocking tcp server
*******************************************************************************************/

#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "socket.hpp"

namespace rabbit{

class tcp_server: uncopyable{
public:
	tcp_server();
	tcp_server(int);
	virtual ~tcp_server();

	//initialize client data
	void init_clients(int);

	//the tcp server must be initialized before using
	void init(std::string, int);
	
	void run();
	void add_client(socket&);
	void close();
	bool has_new_connection();
	socket get_new_connection();
	void loop();
private:
	socket _socket;
	socket *_clients;
	int _num_max_clients;
	int _num_cur_clients;

	//this value is updated every time accept() is called,
	//it is set to true if new connection found, false otherwise
	bool _has_new_conn;
};

}

#endif

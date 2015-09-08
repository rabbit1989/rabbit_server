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
       				header file of nonblocking tcp client
*******************************************************************************************/

#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "base/socket.hpp"
#include <string>

namespace rabbit{

class tcp_client {
public:
	tcp_client();
	tcp_client(const tcp_client&);
	const tcp_client& operator=(const tcp_client&);
	virtual ~tcp_client();
	
	void connect(const std::string&, int);
	void close();

	//wrapper function of socket send
	ssize_t send(const char*, int);
	
	//wrapper function of socket recv	
	ssize_t recv(char*, int);	

	//sender write buffer to network
	ssize_t sendAll();

	//receive data from network and store in read buffer
	ssize_t recvAll();

	//copy data to write buffer
	ssize_t write(const char*, int);

	//copy data from read buffer
	ssize_t read(char*, int);

	socket get_socket() const;
	void set_socket(const socket&);
	
private:
	socket _socket;
	char *_read_buff;
	char *_write_buff;
	size_t _read_buff_size;
	size_t _write_buff_size;
};

}

#endif

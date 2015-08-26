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
       header of socket wrapper class: this class works on both 
       windows and unix-like platform
*******************************************************************************************/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#if defined(WIN32)
	#include <winsock2.h>
#else
	#include <sys/types.h>
    #include <unistd.h>
    #include <fcntl.h>
	#include <sys/socket.h>
    typedef int SOCKET
#endif

#include <string>
#include "uncopyable.hpp"

namespace rabbit{

typedef std::pair<std::string, u_int> sock_addr;
	
class socket{
public:
	socket(int, int, int);
	socket(SOCKET);
	socket(socket&);
	socket(){};
	socket& operator=(socket&);
	virtual ~socket();
	SOCKET accept(struct sockaddr*, int*);
	int listen(int);
	int bind(const struct sockaddr*, int);
	int	connect(const struct sockaddr*, int);
	ssize_t send(const char*, size_t, int);
	ssize_t recv(char*, size_t, int);
	int shutdown(int);
	int close();
	SOCKET get_fd();
	void set_fd(SOCKET);
	bool is_valid();

	//set socket to blocking/nonblocking mode
	//0 for blocking and 1 for nonblocking
	int set_nonblocking(u_long);
	
	//set err_code when error occurs
	void set_errno();
	
	//return the last error code
	int get_errno();
	
	const std::string& get_ip() const;
	const u_int get_port() const; 
	
	//return address pair()
	const sock_addr& get_addr() const;

private:
	sock_addr _addr;
	SOCKET _socket;
	int _state;
	int _err_code;
};

}

#endif
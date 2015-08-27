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
       implematation of socket wrapper class: this class works 
       on both windows and unix-like platform
*******************************************************************************************/

#include "socket.hpp"

namespace rabbit{

socket::socket(int socket_family, int socket_type, int protocol) {
	_socket = ::socket(socket_family, socket_type, protocol);
}

socket::socket(SOCKET sock) {
	_socket = sock;
}

socket::socket(const socket& sock) {
	_socket = sock.get_rawsocket();
//	sock.set_rawsocket(SOCKET_ERROR);
}

socket& socket::operator=(const socket& sock) {
	_socket = sock.get_rawsocket();
//	sock.set_rawsocket(SOCKET_ERROR);
	return *this;
}

//deconstructor does nothing
socket::~socket(){
	// sockaddr addr;
	// int addrlen;
	// int ret = getpeername(_socket, &addr, &addrlen);
	// if (ret == 0) {
	// 	shutdown(SD_BOTH);
	// 	close();
	// }
}

socket socket::accept(struct sockaddr *addr, int *addrlen) {
	SOCKET conn = ::accept(_socket, addr, addrlen);
	set_errno();
	return socket(conn);
}

int socket::listen(int backlog){
	int ret = ::listen(_socket, backlog);
	set_errno();
	return ret;
}

int socket::bind(const struct sockaddr *addr, int len) {
	int ret = ::bind(_socket, addr, len);
	set_errno();
	return ret;
}

int socket::connect(const struct sockaddr *addr, int len) {
	int ret = ::connect(_socket, addr, len);
	set_errno();
	return ret;
}

ssize_t socket::send(const char *buff, size_t len, int flag){
	ssize_t bytes_sent = ::send(_socket, buff, len, flag);
	set_errno();
	return bytes_sent;
}

ssize_t socket::recv(char *buff, size_t len, int flag){
	ssize_t bytes_recv = ::recv(_socket, buff, len, flag);
	set_errno();
	return bytes_recv;
}

int socket::shutdown(int how) {
	int ret = ::shutdown(_socket, how);
	set_errno();
	return ret;
}

int socket::close() {
	
	#if defined(WIN32)
		int ret = ::closesocket(_socket);
	#else
		int ret = ::close(_socket);
	#endif
	set_errno();
	return ret;
}

int socket::set_nonblocking(u_long mode) {
	int ret = 0;
	#if defined(WIN32)
		ret = ioctlsocket(_socket, FIONBIO, &mode);
	#else
		int flags = fcntl(_socket, F_GETFL, 0);
		if (flags >= 0) {
			flags = mode ? (flags|O_NONBLOCK) : (flags&~O_NONBLOCK);
			ret = fcntl(_scoket, F_SETFL, flags);
		}
	#endif
	set_errno();
	return ret;
}

SOCKET socket::get_rawsocket() const{
	return _socket;
}

void socket::set_rawsocket(SOCKET sock) {
	_socket = sock;
}

bool socket::is_valid() {
	return _socket != SOCKET_ERROR;
}

void socket::set_errno() {
	#if defined(WIN32)
		_err_code = WSAGetLastError();
	#else
		_err_code = errno;
	#endif	
}

int socket::get_errno(){
	return _err_code;
}

/*currently not available*/

// const string& socket::get_ip() {
// 	return _addr.first;
// }

// const uint socket::get_port() {
// 	return _addr.second;
// }

// const sock_addr& socket::get_addr() {
// 	return _addr;
// }

}

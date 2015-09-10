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
       			implementation of nonblocking tcp client
*******************************************************************************************/

#include <string>
#include <cstdio>

#include "tcp_client.hpp"

namespace rabbit{

int const BUFFER_SIZE = 1000;

tcp_client::tcp_client():
	_socket(AF_INET, SOCK_STREAM, 0),
	_read_buff(0),
	_write_buff(0),
	_read_buff_size(0),
	_write_buff_size(0)	
{}

tcp_client::~tcp_client() {
	if (_read_buff)
		delete[] _read_buff;
	if (_write_buff)
		delete[] _write_buff;
}

tcp_client::tcp_client(const tcp_client& client) {
	set_socket(client.get_socket());
}

const tcp_client& tcp_client::operator=(const tcp_client& client) {
	set_socket(client.get_socket());
}

void tcp_client::connect(const std::string& ip, int port){
	sockaddr_in addr;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	_socket.connect((SOCKADDR*)&addr, sizeof(SOCKADDR));
	_socket.set_nonblocking(1);
	_read_buff = new char[BUFFER_SIZE];
	_write_buff = new char[BUFFER_SIZE];
}

void tcp_client::close(){
	_socket.close();
}

ssize_t tcp_client::send(const char* data, int len) {
	return _socket.send(data, len, 0);
}

ssize_t tcp_client::recv(char *buff, int len) {
	return _socket.recv(buff, len, 0);
}

ssize_t tcp_client::send_all() {
	ssize_t num_bytes = 0;
	if (_write_buff_size > 0 && _write_buff) {
		num_bytes = send(_write_buff, _write_buff_size);
		if (num_bytes != -1) 
			_write_buff_size -= num_bytes; 	
	}
	return num_bytes;	
}

ssize_t tcp_client::recv_all() {
	ssize_t num_bytes = 0;
	if (_read_buff) {
		num_bytes = recv(_read_buff+_read_buff_size, BUFFER_SIZE-_read_buff_size);
		if (num_bytes != -1) {
			_read_buff_size += num_bytes;
		}
	}
	return num_bytes;
}

ssize_t tcp_client::write(const char*buffer, int len) {
	if (_write_buff == 0) {
		_write_buff = new char[BUFFER_SIZE];
	}
	send_all();
	ssize_t num_bytes = len > BUFFER_SIZE-_write_buff_size ? BUFFER_SIZE-_write_buff_size : len;
	for (ssize_t i = 0; i < num_bytes; i++)
		_write_buff[_write_buff_size++] = buffer[i];

	return num_bytes;
}

ssize_t tcp_client::read(char *buffer, int len) {
	if (_read_buff == 0) {
		_read_buff = new char[BUFFER_SIZE];
	}
	
	recv_all();
	ssize_t num_bytes = len > _read_buff_size ? _read_buff_size : len;
	for (ssize_t i = 0; i < num_bytes; i++)
		buffer[i] = _read_buff[i];

	//move the rest data in read buff to the front 
	for (ssize_t i = num_bytes; i < _read_buff_size; i++)
		_read_buff[i - num_bytes] = _read_buff[i];
	_read_buff_size -= num_bytes;
	return num_bytes;
}

socket tcp_client::get_socket() const{
	return _socket;
}

void tcp_client::set_socket(const socket & sock) {
	_socket = sock;
}

}

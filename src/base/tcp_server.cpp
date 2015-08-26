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
       			implementation of nonblocking tcp server
*******************************************************************************************/

#include "tcp_server.hpp"
#include <string>
#include <memory>

namespace rabbit{

int const BUFFER_SIZE = 200;


tcp_server::tcp_server(): 
	_socket(AF_INET, SOCK_STREAM, 0)
	{
		init_clients(DEFAULT_CLINET_NUM);
}

tcp_server::tcp_server(int num_clients):
	_socket(AF_INET, SOCK_STREAM, 0)
	{
		init_clients(num_clients);
}

tcp_server::~tcp_server(){
	_socket.close();
	delete[] _clients;
}

void tcp_server::init_clients(int num_clients) {
	_num_max_clients = num_clients; 
	_num_cur_clients = 0;
	_clients = new socket[num_clients];
}

void tcp_server::init(std::string ip, int port) {
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);
	_socket.bind((SOCKADDR*)&addr, sizeof(SOCKADDR));
	_socket.listen(_num_max_clients);
	_socket.set_nonblocking(1);
}

void tcp_server::add_client(socket& sock){
	if (_num_cur_clients >= _num_max_clients) {
		fprintf(stderr, "tcp_server: can not accept new connection! num of connect has reached limits!\n");
		return;
	}
	_clients[_num_cur_clients++].set_fd(sock.get_fd());
}

void tcp_server::close(){
	for (int i = 0; i < _num_cur_clients; i++)_clients[i].close();
	_socket.close();
}

void tcp_server::run(){
	char recv_buff[BUFFER_SIZE*5];
	char tmp_buff[BUFFER_SIZE];

	while (true){
		socket new_conn(_socket.accept(NULL, NULL));

		if (new_conn.is_valid() == true) {
			fprintf(stderr, "find new client!!\n");
			add_client(new_conn);
		}
		for (int i = _num_cur_clients-1; i >= 0; i--) {
			int num_recv_bytes = 0;
			while (true) {
				int num_bytes = _clients[i].recv(tmp_buff, sizeof(tmp_buff), 0);
				if (_clients[i].get_errno() == WSAEWOULDBLOCK) {
					if (num_recv_bytes > 0)
			 			process_data(recv_buff, num_recv_bytes);
			 		break;
			 	}
			 	append_buffer((char*)recv_buff, num_recv_bytes, (char*)tmp_buff, num_bytes);
			 	num_recv_bytes += num_bytes;
			 	fprintf(stderr, "num_recv_bytes: %d\n", num_recv_bytes);
			 }
		}
	}
}

void tcp_server::process_data(char data[], int num_bytes) {
	data[num_bytes] = 0;
	printf("%s\n", data);
}

void tcp_server::append_buffer(char *dst_buffer, int dst_len, char *src_buffer, int src_len) {
	memcpy(dst_buffer+dst_len, src_buffer, src_len);
}

}
#include <winsock2.h>
#include <string>
#include <memory>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int const BUFFER_SIZE = 200;

//TODO:
void process_data(char data[], int num_bytes) {
	data[num_bytes] = 0;
	printf("%s\n", data);
}

void append_buffer(char *dst_buffer, int dst_len, char *src_buffer, int src_len) {
	memcpy(dst_buffer+dst_len, src_buffer, src_len);
}

class tcp_server{
public:
	tcp_server();
	tcp_server(int);
	virtual ~tcp_server();
	void init(string, int);
	void run();
	void add_client(SOCKET&);
	void close();
private:
	SOCKET _socket;
	SOCKET *_clients;
	int _num_max_clients;
	int _num_cur_clients;
	std::string _ip;
	int _port;
};

tcp_server::tcp_server(){
	tcp_server(2);
}

tcp_server::tcp_server(int num_clients):
	_ip("0.0.0.0"), 
	_port(12345), 
	_num_max_clients(num_clients), 
	_num_cur_clients(0)
	{
	_clients = new SOCKET[num_clients];
}

tcp_server::~tcp_server(){
	closesocket(_socket);
	free(_clients);
}

void tcp_server::init(string ip, int port) {
	_ip = ip;
	_port = port;
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(_ip.c_str());
	addr.sin_port = htons(_port);
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	bind(_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	listen(_socket, _num_max_clients);
	u_long non_blocking = 1;
	ioctlsocket(_socket, FIONBIO, &non_blocking);
}

void tcp_server::add_client(SOCKET &socket){
	if (_num_cur_clients >= _num_max_clients) {
		fprintf(stderr, "tcp_server: can not accept new connection! num of connect has reached limits!\n");
		return;
	}
	_clients[_num_cur_clients++] = socket;
}

void tcp_server::close(){
	for (int i = 0; i < _num_cur_clients; i++)
		closesocket(_clients[i]);
	closesocket(_socket);
}

void tcp_server::run(){
	char recv_buff[BUFFER_SIZE*5];
	char tmp_buff[BUFFER_SIZE];

	while (true){
		SOCKET new_conn = accept(_socket, NULL, NULL);
		if (new_conn != SOCKET_ERROR) {
			add_client(new_conn);
		}
		for (int i = _num_cur_clients-1; i >= 0; i--) {
			SOCKET conn = _clients[i];
			int num_recv_bytes = 0;
			while (true) {
				int num_bytes = recv(conn, tmp_buff, sizeof(tmp_buff), 0);
				int ret = WSAGetLastError();
				fprintf(stderr, "errno: %d\n", ret);
				if (ret == WSAEWOULDBLOCK) {
					if (num_recv_bytes > 0)
			 			process_data(recv_buff, num_recv_bytes);
			 		break;
			 	}
			 	append_buffer((char*)recv_buff, num_recv_bytes, (char*)tmp_buff, num_bytes);
			 	num_recv_bytes += num_bytes;
			 }
		}
	}
}

int main(){
	
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != NO_ERROR) {
		fprintf(stderr, "winsock initialization failed: %d", ret);
	}

	tcp_server simple_server(10);
	simple_server.init("127.0.0.1", 65534);
	simple_server.run();
	simple_server.close();
	WSACleanup();
	return 0;
}
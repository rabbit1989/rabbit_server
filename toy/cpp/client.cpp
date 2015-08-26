#include <winsock2.h>
#include <windows.h>
#include <string>


#pragma commnet(lib "ws2_32.lib")


using namespace std;

int const BUFF_SIZE = 200;
	
class tcp_client{
public:
	tcp_client(){};
	~tcp_client(){};
	void connect(string, int);
	void close();
	void send(char*);
	char* recv();	

private:
	tcp_client(tcp_client&);
	tcp_client& operator=(tcp_client&);

private:
	string _ip;
	int _port;
	SOCKET _socket;
};

void tcp_client::connect(string ip, int port){
	_ip = ip;
	_port = port;
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	u_long non_blocking = 1;	
	ioctlsocket(_socket, FIONBIO, &non_blocking); 
	SOCKADDR_IN addr;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	::connect(_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
}

void tcp_client::close(){
	shutdown(_socket, SD_BOTH);
	closesocket(_socket);
}

void tcp_client::send(char* data) {
	::send(_socket, data, strlen(data), 0);
}

int main()
{
	WSADATA wsadata;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (ret != NO_ERROR) {
		fprintf(stderr, "tcp client initialization failed: %d", ret);
		return -1;
	}
	tcp_client client;
	client.connect("127.0.0.1", 65534);
	
	int cur_time = 0;
	char msg[BUFF_SIZE];
	while (true) {
		sprintf(msg, "Hello server I am client! time: %d ", cur_time);
		printf("send message %s to server\n", msg);
		client.send((char*)msg);
		cur_time += 1;
		Sleep(1000);
	}

	client.close();
	WSACleanup();
	return 0;
	}

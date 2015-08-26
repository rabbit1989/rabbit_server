import socket
import time

if __name__ == '__main__':
	socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socket.connect(('127.0.0.1', 65534))
	my_time = 0
	socket.setblocking(0)
	while True:
		print 'cur_time: %d' % my_time
	#	socket.send('hello I am client ' + str(my_time) + '\n')
		
		rpc_method = 'func1' if my_time % 10 == 0 else 'func2'
		try:
			socket.send(rpc_method + ' ')
		except:pass
		my_time += 1
		time.sleep(1)
	socket.close()


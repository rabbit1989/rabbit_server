import socket
import entity

def process_data(entity, data):
	func_list = data.split(' ')
	for func_name in func_list:
		if len(func_name) > 0 :
			func = getattr(entity, func_name)
			if not func:
				print 'function %s not found!' % func_name
				continue
			func()

if __name__ == '__main__':
	socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socket.bind(('127.0.0.1', 4000))
	socket.listen(0)
	socket.setblocking(0)
	entity = entity.entity()
	clients = {}
	while True:
		conn = None
		addr = None
		try:
			conn, addr = socket.accept()
		except:pass
		if conn:
			print 'find new connection'
			clients[addr[0]+str(addr[1])] = conn

		for client_id, client in clients.iteritems():
			data = ''
			while True:
				tmp_data = None
				try:
					tmp_data = client.recv(100)
				except:pass	
				if not tmp_data:
					process_data(entity, data)
					break	
				data = data + tmp_data
	
	socket.close()
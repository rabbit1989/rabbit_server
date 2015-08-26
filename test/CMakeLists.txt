project(rabbit_server)
set(SERVER_SRC 
	server.cpp
)

set(CLIENT_SRC
	client.cpp
)

add_executable(server ${SERVER_SRC})
set_target_properties(server PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(server LINK_PUBLIC server_lib)
target_link_libraries(server LINK_PUBLIC ws2_32)

add_executable(client ${CLIENT_SRC})
set_target_properties(client PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(client LINK_PUBLIC server_lib)
target_link_libraries(client LINK_PUBLIC ws2_32)

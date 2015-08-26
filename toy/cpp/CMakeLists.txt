project(rabbit_server)
set(SERVER_SRC 
	server.cpp
)

set(CLIENT_SRC
	client.cpp
)

add_executable(toy_server ${SERVER_SRC})
set_target_properties(toy_server PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(toy_server LINK_PUBLIC ws2_32)

add_executable(toy_client ${CLIENT_SRC})
set_target_properties(toy_client PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(toy_client LINK_PUBLIC ws2_32)
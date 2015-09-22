project(rabbit_server)
set(SERVER_SRC 
	server.cpp
)

set(CLIENT_SRC
	client.cpp
)

set(CAL_SERVER_SRC 
	calculator_server.cpp
)

set(CAL_CLIENT_SRC
	calculator_client.cpp
)

add_executable(server ${SERVER_SRC})
set_target_properties(server PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(server LINK_PUBLIC server_lib)
if(WIN32)
	target_link_libraries(server LINK_PUBLIC ws2_32)
endif(WIN32)

add_executable(client ${CLIENT_SRC})
set_target_properties(client PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(client LINK_PUBLIC server_lib)
if(WIN32)
	target_link_libraries(client LINK_PUBLIC ws2_32)
endif(WIN32)

add_executable(calculator_client ${CAL_CLIENT_SRC})
set_target_properties(calculator_client PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(calculator_client LINK_PUBLIC server_lib)
set_property(TARGET calculator_client PROPERTY CXX_STANDARD 11)
if(WIN32)
	target_link_libraries(calculator_client LINK_PUBLIC ws2_32)
endif(WIN32)

add_executable(calculator_server ${CAL_SERVER_SRC})
set_target_properties(calculator_server PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(calculator_server LINK_PUBLIC server_lib)
set_property(TARGET calculator_server PROPERTY CXX_STANDARD 11)
if(WIN32)
	target_link_libraries(calculator_server LINK_PUBLIC ws2_32)
endif(WIN32)
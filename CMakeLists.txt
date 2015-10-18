cmake_minimum_required(VERSION 2.8)

project (libnetk)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(netk STATIC src/add_list.c
		    	src/data.c
			src/del_list.c
			src/handle_poll.c
			src/list.c
			src/network.c
			src/network_client.c
			src/network_server.c
			src/ringbuffer.c
			src/utils.c
)

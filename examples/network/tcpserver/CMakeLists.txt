project( tcpserver )

include_directories( 
	../../../include 
)

link_libraries(pdnetwork pdbase pthread)

add_executable(tcpserver main.cpp)

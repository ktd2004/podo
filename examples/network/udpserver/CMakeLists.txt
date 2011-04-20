project( udpserver )

include_directories( 
	../../../include 
)

link_libraries(pdbase pdnetwork pthread)

add_executable(udpserver main.cpp)

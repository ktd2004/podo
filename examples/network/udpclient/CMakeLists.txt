project( blowfish )

include_directories( 
	../../../include 
)

link_libraries(pdbase pdnetwork pthread)

add_executable(udpclient main.cpp)

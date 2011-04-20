project( dir )

include_directories( 
	../../../include 
)

link_libraries(pdbase)

add_executable(dir main.cpp)

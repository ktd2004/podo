project( file )

include_directories( 
	../../../include 
)

link_libraries(pdbase)

add_executable(file main.cpp)

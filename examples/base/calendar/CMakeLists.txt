project( calendar )

include_directories( 
	../../../include 
)

link_libraries(pdbase)

add_executable(calendar main.cpp)

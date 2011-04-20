project( flagscoper )

include_directories( 
	../../../include 
)

link_libraries(pdbase)

add_executable(flagscoper main.cpp)

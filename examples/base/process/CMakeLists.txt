project( process )

include_directories( 
	../../../include 
)

link_libraries(pdbase pthread)

add_executable(process main.cpp)

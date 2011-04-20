project( thread )

include_directories( 
	../../../include 
)

link_libraries(pdbase pthread)

add_executable(thread main.cpp)

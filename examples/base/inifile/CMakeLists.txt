project( inifile )

include_directories( 
	${SDL_INCLUDE_DIR} 
	../../../src 
)

link_libraries(pdbase)

add_executable(inifile main.cpp)

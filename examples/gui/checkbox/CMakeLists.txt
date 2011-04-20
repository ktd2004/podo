project( checkbox )

find_package(SDL)
include_directories( 
	${SDL_INCLUDE_DIR}
	../../../include 
)

if(APPLE)
	link_directories(/opt/local/lib)
endif(APPLE)
link_libraries(pdgui pdbase)

add_executable(checkbox main.cpp)

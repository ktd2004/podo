project( dvr )

find_package(SDL)
include_directories( 
    ${SDL_INCLUDE_DIR}
	../../include 
)

if(APPLE)
	link_directories(/opt/local/lib)
endif(APPLE)
link_libraries(pdgui pdbase)


set(SRCS
	Screen.cpp
	StatusBar.cpp
	MenuFrm.cpp
	CameraFrm.cpp
	MainFrm.cpp
	main.cpp
)

add_executable(dvr ${SRCS})

project( phone )

find_package(SDL REQUIRED)
include_directories( 
    ${SDL_INCLUDE_DIR}
	../../include 
)

if(APPLE)
	link_directories(/opt/local/lib)
endif(APPLE)
link_libraries(pdgui pdbase)

set(SRCS
	Indicator.cpp
	Idle.cpp
	Launcher.cpp
	MainFrm.cpp
	main.cpp
)

add_executable(phone ${SRCS})

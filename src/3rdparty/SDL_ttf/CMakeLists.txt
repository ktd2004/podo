set(SRCS
	SDL_ttf.c          
)

find_package(SDL REQUIRED)
find_package(Freetype REQUIRED)
include_directories( 
	${SDL_INCLUDE_DIR} 
	${FREETYPE_INCLUDE_DIR_freetype2} 
	)

link_libraries(freetype)

set(LIBRARY_OUTPUT_PATH ../../../lib)
add_library(SDL_ttf SHARED ${SRCS})

install(TARGETS SDL_ttf DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

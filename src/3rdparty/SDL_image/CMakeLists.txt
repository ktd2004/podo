set(SRCS
	IMG.c          
	IMG_bmp.c  
	IMG_jpg.c  
	IMG_pcx.c  
	IMG_pnm.c  
	IMG_tif.c  
	IMG_xpm.c  
	IMG_xxx.c
	IMG_ImageIO.c  
	IMG_gif.c  
	IMG_lbm.c  
	IMG_png.c  
	IMG_tga.c  
	IMG_xcf.c  
	IMG_xv.c 
)

find_package(SDL REQUIRED)
include_directories( ${SDL_INCLUDE_DIR} )

set(LIBRARY_OUTPUT_PATH ../../../lib)
add_library(SDL_image SHARED ${SRCS})

install(TARGETS SDL_image DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

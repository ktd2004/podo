set(SRCS
	PDApp.cpp
	PDArrowXpm.cpp
	PDButton.cpp
	PDCalendarUI.cpp
	PDCheckBox.cpp
	PDColor.cpp
	PDDesktopWidget.cpp
	PDEvent.cpp
	PDFont.cpp
	PDFontDB.cpp
	PDImage.cpp
	PDLabel.cpp
	PDLang.cpp
	PDPainter.cpp
	PDPalette.cpp
	PDPoint.cpp
	PDPopupMenu.cpp
	PDRect.cpp
	PDSize.cpp
	PDSkin.cpp
	PDTableWidget.cpp
	PDTableWidgetItem.cpp
	PDTheme.cpp
	PDTimer.cpp
	PDWidget.cpp
)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
include_directories(${SDL_INCLUDE_DIR} ../../include)

if(APPLE)
	link_directories(/opt/local/lib)
	link_libraries(pdbase SDL SDL_ttf SDL_image SDLmain -Wl,-framework,Cocoa)
else(APPLE)
	link_libraries(pdbase SDL SDL_ttf SDL_image)
endif(APPLE)


set(LIBRARY_OUTPUT_PATH ../../lib)
add_library(pdgui SHARED ${SRCS})

set(SRCS
	PDObject.cpp
	PDString.cpp
	PDFile.cpp
	PDCalendar.cpp
	PDDateTime.cpp
	PDIniFile.cpp
	PDMutex.cpp
	PDMutexLocker.cpp
	PDWaitCondition.cpp
	PDThread.cpp
	PDDir.cpp
	PDProcess.cpp
	PDFlagScoper.cpp
)

set(LIBRARY_OUTPUT_PATH ../../lib)
include_directories(../../include)

link_libraries(pthread)

add_library(pdbase SHARED ${SRCS})

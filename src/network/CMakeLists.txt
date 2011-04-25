set(SRCS
	PDAbstractSocket.cpp
	PDTcpServer.cpp
	PDTcpSocket.cpp
	PDUdpSocket.cpp
)

set(LIBRARY_OUTPUT_PATH ../../lib)
link_libraries(pdbase)
add_library(pdnetwork SHARED ${SRCS})

install(TARGETS pdnetwork DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

set(SRCS
	PDAbstractSocket.cpp
	PDTcpServer.cpp
	PDTcpSocket.cpp
	PDUdpSocket.cpp
)

set(LIBRARY_OUTPUT_PATH ../../lib)
link_libraries(pdbase)
add_library(pdnetwork SHARED ${SRCS})

cmake_minimum_required(VERSION 3.0)
project(direcpp VERSION 0.2.1 DESCRIPTION "TNC handler library")
include(GNUInstallDirs)

add_library( ${PROJECT_NAME} SHARED
    src/ax25.cpp
    src/connect_serial.cpp
    src/connect_tcp.cpp
    src/direcpp.cpp
    src/kiss.cpp
    src/kiss_serial.cpp
    src/kisstcp.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION} 
    SOVERSION 1 
    PUBLIC_HEADER include/direcpp.hpp)

configure_file(direcpp.pc.in direcpp.pc @ONLY)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/direcpp.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
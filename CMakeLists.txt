cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER})

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

project(cppstr VERSION 1.0)
include(GNUInstallDirs)

add_library(cppstr
    cppstr.cpp
)

target_link_libraries(cppstr)

set_target_properties(cppstr PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cppstr PROPERTIES PUBLIC_HEADER cppstr.h)

include_directories("./")

install(TARGETS cppstr LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER})
add_compile_options("-Wall")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

project(cppstr VERSION 1.0)
include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(cppstr
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cppstr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sparam.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stringview.cpp
)

target_link_libraries(cppstr)

set_target_properties(cppstr PROPERTIES CXX_STANDARD 17)

set_target_properties(cppstr PROPERTIES VERSION ${PROJECT_VERSION})

target_sources(cppstr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(cppstr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS cppstr LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install (
    DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cppstr
    DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}
)

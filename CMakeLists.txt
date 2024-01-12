cmake_minimum_required(VERSION 3.5)
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER})
add_compile_options("-Wall")

# make uninstall
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

project(cppstr VERSION 1.0)
include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(header_path ${CMAKE_CURRENT_SOURCE_DIR}/include/cppstr)
set(header
    ${header_path}/cppstr.h
    ${header_path}/sparam.h
    ${header_path}/stringview.h
)

set(src_path ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(src
    ${src_path}/cppstr.cpp
    ${src_path}/sparam.cpp
    ${src_path}/stringview.cpp
)

set(lib_dest ${CMAKE_INSTALL_LIBDIR})
set(cppstr_install_cmakedir ${CMAKE_INSTALL_LIBDIR}/cmake/cppstr)

add_library(cppstr ${header} ${src})

set_target_properties(cppstr PROPERTIES CXX_STANDARD 17)
set_target_properties(cppstr PROPERTIES VERSION ${PROJECT_VERSION})

# this allows EXPORT
target_include_directories(cppstr PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
)

install(TARGETS cppstr EXPORT cppstr DESTINATION ${lib_dest} INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${header} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cppstr)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cppstr-config.cmake DESTINATION ${cppstr_install_cmakedir})
install(EXPORT cppstr DESTINATION ${cppstr_install_cmakedir})

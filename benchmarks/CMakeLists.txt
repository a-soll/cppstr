cmake_minimum_required(VERSION 3.5)

add_executable(alloc ${CMAKE_CURRENT_SOURCE_DIR}/allocations.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(alloc PRIVATE cppstr_lib)

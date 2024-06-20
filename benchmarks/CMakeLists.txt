cmake_minimum_required(VERSION 3.5)

add_executable(benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/allocations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/parameter.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(benchmarks PRIVATE cppstr)

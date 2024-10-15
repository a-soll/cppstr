cmake_minimum_required(VERSION 3.5)

add_executable(benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(benchmarks PRIVATE cppstr)

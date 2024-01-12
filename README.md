# cppstr

### Overview
This is a string library that allows for more freedom and is lighter weight than `std::string`. The goal of this library is:
1. Maintain the speed and simplicity of a simple C array but with C++ usability and convenience
2. Maintain as little overhead as possible
3. As close to full control as possible. You can modify in place as needed. `cppstr::string` will handle tracking length, allocated size, etc. Indexes can be modified just like they would be in a normal C array with additional functionality for inserting, appending, and cutting string short using `NULL` term.

It offers:
- more flexibility for modifying string contents in place
- automatic memory management. Use it just like you would `std::string`.
- useful functions for working with internal string contents.

### sparam
All functions take an `sparam`, which is a temporary string type that avoids the need to malloc, copy, or re-calculate length. `sparam` should not be used directly as there
is no ownership of the data. It is only used to allow flexibility for the `cppstr::string` member functions. Simply pass a `const char*`,
`std:string`, or `cppstr::string` and `sparam` will handle it from there.

### Building from source
To quickly build a release version, simply run `bin/build`. Passing `-i` will install the library to `/usr/local/lib`, but provide a path to install to if you want it elsewhere.

Alternatively, standard Cmake workflow:
```
mkdir build
cd build
cmake ..
make
```

### Using as Cmake dependency
To use this library as a Cmake dependency, you can either use `find_package(CPPSTR)` or `FetchContent` like below.

#### find_package()
```
find_package(CPPSTR REQUIRED)

# set the rpath for your executable
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_BUILD_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

add_executable(
    cppstr_test
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(cppstr_test CPPSTR)
```

#### FetchContent
```
include(FetchContent)

FetchContent_Declare(
    cppstr
    GIT_REPOSITORY https://github.com/a-soll/cppstr.git
    GIT_TAG main
)

FetchContent_MakeAvailable(cppstr)

add_executable(
    cppstr_test
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(cppstr_test cppstr)
```

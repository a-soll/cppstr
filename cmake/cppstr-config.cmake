find_path(CPPSTR_INCLUDE_DIR
          NAMES cppstr/cppstr.h)

find_library(CPPSTR_LIBRARY
             NAMES cppstr
             HINTS ${CPPSTR_LIBRARY_ROOT})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CPPSTR REQUIRED_VARS CPPSTR_LIBRARY CPPSTR_INCLUDE_DIR)

if(CPPSTR_FOUND)
    set(CPPSTR_LIBRARIES ${CPPSTR_LIBRARY})
    set(CPPSTR_INCLUDE_DIRS ${CPPSTR_INCLUDE_DIR})
    include_directories(${CPPSTR_INCLUDE_DIR})
endif()

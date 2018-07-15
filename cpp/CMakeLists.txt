
cmake_minimum_required (VERSION 2.6)
project (Plactic_Identities)



# The version number.
set (Plactic_Identities_VERSION_MAJOR 0)
set (Plactic_Identities_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/include/version.hpp.in"
  "${PROJECT_BINARY_DIR}/include/version.hpp"
  )



# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}/include")




include_directories("${PROJECT_BINARY_DIR}/src/tropical_elements")
add_subdirectory (src/tropical_elements)

# should we use our own math functions?
option (USE_DEBUGGING_UTILS
        "Use debugging utils." ON) 

# add the Debugging utilities to the library?
#
if (USE_DEBUGGING_UTILS)
  include_directories("${PROJECT_BINARY_DIR}/src/logger")
  add_subdirectory (src/logger)
  set (EXTRA_LIBS ${EXTRA_LIBS} Logger)
endif (USE_DEBUGGING_UTILS)








find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})



#install (TARGETS MathFunctions DESTINATION bin)
#install (FILES MathFunctions.h DESTINATION include)





add_executable(placid main.cc tests/tests.cc)

target_link_libraries (placid TropicalNumbers)
target_link_libraries (placid  ${EXTRA_LIBS})
target_link_libraries(placid ${GTEST_BOTH_LIBRARIES})

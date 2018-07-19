# Project name and CMake version requirements
cmake_minimum_required (VERSION 2.6)
project (Plactic_Identities)



# The version number.
set (Plactic_Identities_VERSION_MAJOR 0)
set (Plactic_Identities_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/include/version.hpp.in"
  "${PROJECT_BINARY_DIR}/include/version.hpp"
)



# add the include directory to the search path for include files
include_directories("${PROJECT_BINARY_DIR}/include")



# add the tropical elements path to the search path for include files
# load the cmake lists from that directory
include_directories("${PROJECT_BINARY_DIR}/src/tropical_elements")
add_subdirectory (src/tropical_elements)

# include_directories("${PROJECT_BINARY_DIR}/src")
# add_subdirectory (src/)


# whether using or not debugging utils
option (USE_DEBUGGING_UTILS
        "Use debugging utils." ON)

if (USE_DEBUGGING_UTILS)
  include_directories("${PROJECT_BINARY_DIR}/src/logger")
  add_subdirectory (src/logger)
  set (DBG_LIBS ${DBG_LIBS} Logger)
endif (USE_DEBUGGING_UTILS)







# include the gtest suite to allow unit tests
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})




# template for the installation commands
#install (TARGETS MathFunctions DESTINATION bin)
#install (FILES MathFunctions.h DESTINATION include)




# add executable
add_executable(placid main.cc tests/tests.cc tests/tropical_number_tests.cc)

# add required libraries
target_link_libraries (placid TropicalNumbers)
target_link_libraries (placid TropicalMatrices)
# target_link_libraries (placid AlgebraElements)


# add debugging libraries (if used)
target_link_libraries (placid  ${DBG_LIBS})

# add GTest libraries
target_link_libraries(placid ${GTEST_BOTH_LIBRARIES})

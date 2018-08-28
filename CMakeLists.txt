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



set(CMAKE_BUILD_TYPE Debug)

set (CMAKE_CXX_STANDARD 11)


# add the include directory to the search path for include files
include_directories("${PROJECT_BINARY_DIR}/include")




# add the tropical elements path to the search path for include files
# load the cmake lists from that directory
include_directories("${PROJECT_BINARY_DIR}/src/free_monoid")
add_subdirectory (src/free_monoid)

include_directories("${PROJECT_BINARY_DIR}/src/tropical_elements")
add_subdirectory (src/tropical_elements)

include_directories("${PROJECT_BINARY_DIR}/src/semistandard_tableaux")
add_subdirectory (src/semistandard_tableaux)

add_subdirectory (src/)





# template for the installation commands
#install (TARGETS MathFunctions DESTINATION bin)
#install (FILES MathFunctions.h DESTINATION include)




FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})



add_executable(sst_multiply sst_multiply_main.cc)
add_executable(test main.cc)



target_link_libraries(sst_multiply ${Boost_LIBRARIES})


# add required libraries
target_link_libraries (sst_multiply Utils)
target_link_libraries (sst_multiply FreeMonoid)
target_link_libraries (sst_multiply TropicalNumbers)
target_link_libraries (sst_multiply TropicalMatrices)
target_link_libraries (sst_multiply Tuples)
target_link_libraries (sst_multiply SemiStandardTableaux)

target_link_libraries (test Utils)
target_link_libraries (test FreeMonoid)
target_link_libraries (test TropicalNumbers)
target_link_libraries (test TropicalMatrices)
target_link_libraries (test Tuples)
target_link_libraries (test SemiStandardTableaux)







# Unit testing and debugging

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



# unit tests
add_executable(unit_tests unit_tests_main.cc tests/tropical_number_tests.cc tests/tropical_matrix_tests.cc tests/tuple_tests.cc tests/tableaux_entry_tests.cc tests/ordered_array_tests.cc tests/semistandard_tableaux_tests.cc tests/free_monoid_entry_tests.cc tests/free_monoid_element_tests.cc tests/pool_tests.cc tests/homomorphism_tests.cc tests/knuth_homomorphism_tests.cc tests/injectivity_test_tests.cc)


# add required libraries
target_link_libraries (unit_tests Utils)
target_link_libraries (unit_tests FreeMonoid)
target_link_libraries (unit_tests TropicalNumbers)
target_link_libraries (unit_tests TropicalMatrices)
target_link_libraries (unit_tests Tuples)
target_link_libraries (unit_tests SemiStandardTableaux)

# add debugging libraries (if used)
target_link_libraries (unit_tests  ${DBG_LIBS})

# add GTest libraries
target_link_libraries(unit_tests ${GTEST_BOTH_LIBRARIES})

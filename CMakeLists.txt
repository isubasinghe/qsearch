cmake_minimum_required(VERSION 3.13)
project(qsearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Ensure that folly was compiled with the same SIMD flags
# check here https://github.com/facebook/folly/blob/master/CMakeLists.txt
set(CMAKE_CXX_FLAGS "-Wall -Wextra --pedantic -mavx -mavx2 -msse2 -DSTATIC_SEARCH")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Boost REQUIRED)
find_package(folly REQUIRED)
find_package(Threads REQUIRED)
find_package(gflags REQUIRED)

set_and_check(FOLLY_INCLUDE_DIR /usr/local/include/folly)
set_and_check(FOLLY_CMAKE_DIR /usr/local/lib/cmake/folly)
if (NOT TARGET Folly::folly)
  include("${FOLLY_CMAKE_DIR}/folly-targets.cmake")
endif()


set(FOLLY_LIBRARIES Folly::folly)

if (NOT folly_FIND_QUIETLY)
  message(STATUS "Found folly: ${PACKAGE_PREFIX_DIR}")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/includes")

add_executable(qsearch main.cpp
  ./src/fst/fst.cpp
  ./src/fst/node.cpp
  ./src/docman/manager.cpp
  ./src/scorer/scorer.cpp
  ./src/scorer/tfidf.cpp
)

target_link_libraries(qsearch ${Boost_LIBRARIES} ${FOLLY_LIBRARIES})
cmake_minimum_required(VERSION 3.13)
project(qsearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Ensure that folly was compiled with the same SIMD flags
# check here https://github.com/facebook/folly/blob/master/CMakeLists.txt
set(CMAKE_CXX_FLAGS "-Wall -Wextra --pedantic -mavx -mavx2 -msse2 -DSTATIC_SEARCH -O3")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

list(APPEND LINK_LIBS "")

find_package(Boost REQUIRED)
find_package(folly REQUIRED)
find_package(Threads REQUIRED)
find_package(gflags REQUIRED)
find_package(GooglePerftools)
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)


# <FOLLY>
set_and_check(FOLLY_INCLUDE_DIR /usr/local/include/folly)
set_and_check(FOLLY_CMAKE_DIR /usr/local/lib/cmake/folly)
if (NOT TARGET Folly::folly)
  include("${FOLLY_CMAKE_DIR}/folly-targets.cmake")
endif()


set(FOLLY_LIBRARIES Folly::folly)

if (NOT folly_FIND_QUIETLY)
  message(STATUS "Found folly: ${PACKAGE_PREFIX_DIR}")
endif()
# </FOLLY>


# <GPERFTOOLS>
if (GOOGLE_PERFTOOLS_FOUND)
  include_directories(${GOOGLE_PERFTOOLS_INCLUDE_DIRS})
  list(APPEND LINK_LIBS ${GOOGLE_PERFTOOLS_LIBRARIES})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free")
endif()
# </GPERFTOOLS>

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/includes")

add_executable(qsearch main.cpp
  ./src/fst/fst.cpp
  ./src/fst/node.cpp
  ./src/fst/edge.cpp
  ./src/scorer/scorer.cpp
  ./src/scorer/tfidf.cpp
  ./src/docman/manager.cpp
  ./src/docman/batchinsert.cpp
  ./src/server/server.cpp
  ./src/raft/raft.cpp
)

list(APPEND LINK_LIBS ${Boost_LIBRARIES}
${FOLLY_LIBRARIES}
${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
cpprestsdk::cpprest
)

target_link_libraries(
  qsearch
  ${LINK_LIBS}
  )
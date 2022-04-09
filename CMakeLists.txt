cmake_minimum_required(VERSION 3.16)

project(mxdemon CXX C)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fno-math-errno -march=native -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CUDA_FLAGS_RELEASE "-O3 -DNDEBUG")

find_package(SFML COMPONENTS graphics window system)

add_subdirectory(src)


#####################################################
# GTest, find system first, download if necessary
#####################################################
find_package(GTest)

if (NOT GTest_FOUND)
  message(STATUS "Configure GTest from github")

  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
  )

  # Check if population has already been performed
  FetchContent_GetProperties(googletest)
  if(NOT googletest_POPULATED)
    message(STATUS "Downloading GTest from github")
    # Fetch the content using previously declared details
    FetchContent_Populate(googletest)

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Bring the populated content into the build
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  endif()
endif()

if (NOT TARGET GTest::gtest_main)
    message("Target GTest:: stuff MISSING")
endif()

add_subdirectory(test)

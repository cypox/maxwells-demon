cmake_minimum_required(VERSION 3.16)

project(mxdemon CXX C)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fno-math-errno -march=native -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CUDA_FLAGS_RELEASE "-O3 -DNDEBUG")

find_package(SFML COMPONENTS graphics window system)

add_subdirectory(src)

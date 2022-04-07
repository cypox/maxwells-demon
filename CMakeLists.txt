cmake_minimum_required(VERSION 3.16)

project(mxdemon CXX C)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fno-math-errno -march=native -DNDEBUG")
set(CMAKE_CUDA_FLAGS_RELEASE "-O3 -DNDEBUG")

add_subdirectory(src)

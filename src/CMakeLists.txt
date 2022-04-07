set(SOURCES main.cpp)
add_executable(mxdemon ${SOURCES})
target_include_directories(mxdemon PRIVATE ${PROJECT_SOURCE_DIR}/include)

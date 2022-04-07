set(SOURCES main.cpp)

add_executable(mxdemon.bin ${SOURCES})

target_include_directories(mxdemon.bin PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(mxdemon.bin sfml-graphics)

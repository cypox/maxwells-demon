set(SOURCES main.cpp)

add_executable(mxdemon.bin ${SOURCES})

target_link_libraries(mxdemon.bin sfml-graphics)

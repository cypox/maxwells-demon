set(UNIT_TESTS main.cpp)

add_executable(unit_tests.bin ${UNIT_TESTS})

target_include_directories(unit_tests.bin PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(unit_tests.bin PRIVATE ${PROJECT_SOURCE_DIR}/test/include)

#target_link_libraries(unit_tests.bin sfml-graphics)
target_link_libraries(unit_tests.bin PRIVATE GTest::gtest_main)
add_test(NAME UnitTests COMMAND unit_tests.bin)

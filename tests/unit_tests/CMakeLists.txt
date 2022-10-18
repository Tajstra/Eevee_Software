# test files:
target_sources(${EXECUTABLE_NAME} PRIVATE "test.cpp")

target_link_libraries(${EXECUTABLE_NAME} -lgtest -lgtest_main)

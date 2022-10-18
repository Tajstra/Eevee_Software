# Add main file for integration tests:
target_sources(${EXECUTABLE_NAME} PRIVATE "main.cpp")

# test files:
target_sources(${EXECUTABLE_NAME} PRIVATE "test.cpp")

target_link_libraries(${EXECUTABLE_NAME} -lgtest)

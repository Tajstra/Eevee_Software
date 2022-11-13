# test files:
target_sources(
  ${EXECUTABLE_NAME}
  PRIVATE "test.cpp" "quadcopter_shape_x_test.cpp"
          "${CMAKE_SOURCE_DIR}/sources/sim/plant_model/quadcopter_shape_x.cpp"
          "integrator_test.cpp" "../utils/logger_csv.cpp" "logger_csv_test.cpp")

target_include_directories(${EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_SOURCE_DIR}/tests)

target_link_libraries(${EXECUTABLE_NAME} -lgtest -lgtest_main)

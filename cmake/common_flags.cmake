if(${BUILD_TYPE} STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g -gdwarf-2")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -gdwarf-2 -g")

elseif(${BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

elseif(${BUILD_TYPE} STREQUAL "")
  message(SEND_ERROR "Please specify the build type using '-DBUILD_TYPE=build_type'")

else()
  message(SEND_ERROR "Build type '${BUILD_TYPE}' does not exist")

endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-volatile") # -fno-exceptions

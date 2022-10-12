# Define toolchain:
# System Generic - no OS bare-metal application
set(CMAKE_SYSTEM_NAME Generic)

# Setup arm processor and gcc toolchain
set(CMAKE_SYSTEM_PROCESSOR arm)
# set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
# set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
# set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

# The toolchain prefix for all toolchain executables
set(CROSS_COMPILE arm-none-eabi-)

set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc "--specs=nano.specs")
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++ "--specs=nano.specs")
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_LINKER ${CROSS_COMPILE}ld)

set(CMAKE_AR ${CROSS_COMPILE}ar)
set(CMAKE_OBJCOPY ${CROSS_COMPILE}objcopy
    CACHE FILEPATH "The toolchain objcopy command" FORCE)
set(CMAKE_OBJDUMP ${CROSS_COMPILE}objdump)

# When trying to link cross compiled test program, error occurs, so setting test compilation to static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Set the CMAKE C flags (which should also be used by the assembler!)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m4")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=fpv4-sp-d16")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mtune=cortex-m4")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_HAL_DRIVER")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTM32F411xE")

# Set CXX flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-m4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=fpv4-sp-d16")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=cortex-m4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthumb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_HAL_DRIVER")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTM32F411xE")

#  Cache the flags for use
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "CFLAGS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "CXXFLAGS")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "")

# Linker flags
add_link_options("SHELL:-T ${CMAKE_SOURCE_DIR}/sources/mcal/cubemx/STM32F411VETx_FLASH.ld")

macro(add_arm_executable target_name)

# Output files
set(elf_file ${target_name}.elf)
set(hex_file ${target_name}.hex)
set(bin_file ${target_name}.bin)

add_executable(${elf_file} ${ARGN})
target_link_options(${elf_file} PRIVATE --specs=nosys.specs)

#generate hex file
add_custom_command(
	OUTPUT ${hex_file}

	COMMAND
		${CMAKE_OBJCOPY} -O ihex ${elf_file} ${hex_file}

	DEPENDS ${elf_file}
)

#generate bin file
add_custom_command(
	OUTPUT ${bin_file}

	COMMAND
		${CMAKE_OBJCOPY} -O binary ${elf_file} ${bin_file}

	DEPENDS ${elf_file}
)

endmacro(add_arm_executable)


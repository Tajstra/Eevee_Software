cmake_path(
  SET free_rtos_source
  "${CMAKE_SOURCE_DIR}/sources/eevee/FreeRTOSv202112.00/FreeRTOS/Source")

target_sources(
  free_rtos PRIVATE
  ${free_rtos_source}/croutine.c
  ${free_rtos_source}/event_groups.c
  ${free_rtos_source}/list.c
  ${free_rtos_source}/queue.c
  ${free_rtos_source}/stream_buffer.c
  ${free_rtos_source}/tasks.c
  ${free_rtos_source}/timers.c
  ${free_rtos_source}/portable/MemMang/heap_1.c)

target_include_directories(
  free_rtos PRIVATE "${free_rtos_source}/include")

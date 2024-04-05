cmake_minimum_required(VERSION 3.16)
project("cpu-emulator" VERSION 0.0.1)

set(BUILD_NAME emulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_subdirectory(external/fmt)

set(SOURCE_FILES
  src/main.cpp
  )

add_executable(${BUILD_NAME} ${SOURCE_FILES})
target_link_libraries(${BUILD_NAME} PRIVATE
  fmt
  )
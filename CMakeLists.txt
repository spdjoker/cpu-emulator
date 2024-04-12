cmake_minimum_required(VERSION 3.16)
project("cpu-emulator" VERSION 0.0.1)

set(BUILD_NAME emulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(external/fmt)
set(glew-cmake_BUILD_SHARED OFF)
add_subdirectory(external/glew)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
add_subdirectory(external/glfw)
set(GLM_BUILD_TESTS OFF)
set(GLM_BUILD_INSTALL OFF)
add_subdirectory(external/glm)

include_directories(src)

set(TEST_NAMES
  test_glfw
  test_imgui
  )

set(JKR_FILES
  # src/jkr/cmd_options.h
  # src/jkr/generic.hpp

  src/jkr/core/window.cpp
  src/jkr/core/window.hpp

  src/jkr/editor/ui.cpp
  src/jkr/editor/ui.hpp
  )

set(IMGUI_FILES
  # Source
  src/imgui/imconfig.h
  src/imgui/imgui.cpp
  src/imgui/imgui.h
  src/imgui/imgui_demo.cpp
  src/imgui/imgui_draw.cpp
  src/imgui/imgui_internal.h
  src/imgui/imgui_tables.cpp
  src/imgui/imgui_widgets.cpp
  src/imgui/imstb_rectpack.h
  src/imgui/imstb_textedit.h
  src/imgui/imstb_truetype.h
  # Backends
  src/imgui/backends/imgui_impl_glfw.cpp
  src/imgui/backends/imgui_impl_glfw.h
  src/imgui/backends/imgui_impl_opengl3.cpp
  src/imgui/backends/imgui_impl_opengl3.h
  src/imgui/backends/imgui_impl_opengl3_loader.h
  )

foreach(TEST_NAME ${TEST_NAMES})

  add_executable(${TEST_NAME} 
    ${IMGUI_FILES}
    ${JKR_FILES} 
    src/test/${TEST_NAME}.cpp 
    )

  target_link_libraries(${TEST_NAME} PUBLIC
    libglew_static
    ${OPENGL_LIBRARIES}
    fmt
    glfw
    glm
    )
endforeach()

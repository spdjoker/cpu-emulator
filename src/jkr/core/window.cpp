#include "jkr/core/window.hpp"

#include <fmt/core.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace jkr {

unsigned int glfw_window_count = 0;

void WindowProps::enable(Option o) {
  flags |= (int)o;
}

void WindowProps::disable(Option o) {
  flags &= ~((int)o);
}

bool WindowProps::has(Option o) const {
  return (flags & ((int)o)) == (int)o;
}

Window::Window(const WindowProps& props, GLFWwindow* window) {
  m_props = props;
  p_glfw_window = window;
}

Window::~Window() {
  destroy();
}

Window Window::Create(const WindowProps& props) {
  if (!glfw_window_count) {
    if (!glfwInit()) {
      fmt::println(stderr, "Failed to initialize GLFW");
      return Window(props);
    }
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
  }

  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, props.has(WindowProps::OPT_TRANSPARENT_FRAMEBUFFER));
  glfwWindowHint(GLFW_RESIZABLE, props.has(WindowProps::OPT_RESIZABLE));
  glfwWindowHint(GLFW_VISIBLE, props.has(WindowProps::OPT_VISIBLE));
  glfwWindowHint(GLFW_DECORATED, props.has(WindowProps::OPT_DECORATED));
  glfwWindowHint(GLFW_AUTO_ICONIFY, props.has(WindowProps::OPT_AUTO_ICONIFY));
  glfwWindowHint(GLFW_FLOATING, props.has(WindowProps::OPT_FLOATING));
  glfwWindowHint(GLFW_MAXIMIZED, props.has(WindowProps::OPT_MAXIMIZED));
  glfwWindowHint(GLFW_CENTER_CURSOR, props.has(WindowProps::OPT_CENTER_CURSOR));
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, props.has(WindowProps::OPT_FOCUS_ON_SHOW));
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, props.has(WindowProps::OPT_SCALE_TO_MONITOR));
  glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, props.has(WindowProps::OPT_SCALE_FRAMEBUFFER));
  glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, props.has(WindowProps::OPT_MOUSE_PASSTHROUGH));

  GLFWwindow* glfw_window = glfwCreateWindow(props.size.x, props.size.y, props.title.c_str(), NULL, NULL);
  if (!glfw_window) {
    fmt::println(stderr, "Failed to create a GLFW window");
    if (!glfw_window_count)
      glfwTerminate();
    return Window(props);
  }

  glfw_window_count++;

  return Window(props, glfw_window);
}

Window::Window(const Window& win) {
  p_glfw_window = win.p_glfw_window;
  m_props = win.m_props;
}

void Window::destroy() {
  if (!p_glfw_window) return;

  glfwDestroyWindow(p_glfw_window);
  p_glfw_window = nullptr;
  glfw_window_count--;

  if (!glfw_window_count)
    glfwTerminate();
}

void Window::close() {
  glfwSetWindowShouldClose(p_glfw_window, true);
}

void Window::clear_color_buffer() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap_buffers() {
  glfwSwapBuffers(p_glfw_window);
}

void Window::poll_events() {
  glfwPollEvents();
}

void Window::make_context_current() {
  glfwMakeContextCurrent(p_glfw_window);
  glClearColor(
    m_props.clear_color.r, 
    m_props.clear_color.g, 
    m_props.clear_color.b, 
    m_props.clear_color.a
    );
}

bool Window::is_valid() const {
  return p_glfw_window;
}

bool Window::is_closing() const {
  return glfwWindowShouldClose(p_glfw_window);
}

bool Window::is_context_current() const {
  return glfwGetCurrentContext() == p_glfw_window;
}

const glm::vec4& Window::get_clear_color() const {
  return m_props.clear_color;
}

void Window::set_clear_color(const glm::vec4& color) {
  m_props.clear_color = color;
} 

GLFWwindow* Window::glfw_window() {
  return p_glfw_window;
}

}

#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct GLFWwindow;

namespace jkr {

struct WindowProps {
  std::string title = "New Window";
  glm::uvec2 size = {800u, 600u};
  glm::vec4 clear_color = {0.0f, 0.18f, 0.12f, 1.0f};

  enum Option {
    OPT_RESIZABLE                = 1,
    OPT_VISIBLE                  = 1 << 1,
    OPT_DECORATED                = 1 << 2,
    OPT_FOCUSED                  = 1 << 3,
    OPT_AUTO_ICONIFY             = 1 << 4,
    OPT_FLOATING                 = 1 << 5,
    OPT_MAXIMIZED                = 1 << 6,
    OPT_CENTER_CURSOR            = 1 << 7,
    OPT_TRANSPARENT_FRAMEBUFFER  = 1 << 8, 
    OPT_FOCUS_ON_SHOW            = 1 << 9, 
    OPT_SCALE_TO_MONITOR         = 1 << 10,
    OPT_SCALE_FRAMEBUFFER        = 1 << 11,
    OPT_MOUSE_PASSTHROUGH        = 1 << 12,
  };

  void enable(Option o);
  void disable(Option o);
  bool has(Option o) const;

private:
  int flags 
  = OPT_RESIZABLE | OPT_VISIBLE | OPT_DECORATED 
  | OPT_FOCUSED | OPT_AUTO_ICONIFY | OPT_CENTER_CURSOR 
  | OPT_FOCUS_ON_SHOW | OPT_SCALE_FRAMEBUFFER;
};

class Window {
  GLFWwindow* p_glfw_window;
  WindowProps m_props;

  Window(const WindowProps& props, GLFWwindow* window = nullptr);

public:
  Window(const Window& win);
  ~Window();

  static Window Create(const WindowProps& props = WindowProps());
  void destroy();
  
  void close();
  void clear_color_buffer();
  void swap_buffers();
  void poll_events();
  void make_context_current();

  bool is_valid() const;
  bool is_closing() const;
  bool is_context_current() const;

  const glm::vec4& get_clear_color() const;
  void set_clear_color(const glm::vec4& color);

  // replace when making ImGUI wrapper
  GLFWwindow* glfw_window();
};

}
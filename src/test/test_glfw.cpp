#include "fmt/base.h"
#include "jkr/core/input.hpp"
#include "jkr/core/window.hpp"
#include <fmt/core.h>

int main() {
  jkr::WindowProps props;
  props.clear_color = {1.0f, 0.0f, 0.0f, 1.0f};

  jkr::Window win = jkr::Window::Create(props);
  if (!win.is_valid()) return 1;

  while (!win.is_closing()) {
    win.make_context_current();
    win.clear_color_buffer();

    if (win.input().on_key_down(jkr::key::ESCAPE)) {
      win.close();
    }

    // Render stuff here

    win.swap_buffers();
    win.poll_events();
  }

  win.destroy();

  return 0;
} 

#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "jkr/core/window.hpp"
#include "jkr/editor/ui.hpp"

int main() {
  jkr::WindowProps props;
  props.enable(jkr::WindowProps::OPT_MAXIMIZED);

  jkr::Window window = jkr::Window::Create(props);
  if (!window.is_valid())
    return 1;

  // Initializing ImGui
  window.make_context_current();
  jkr::editor::ui::create(window);

  glfwSwapInterval(1);

  // fmt::println("{}", window.is_context_current());

  while (!window.is_closing()) {
    window.clear_color_buffer();
    
    if (!jkr::editor::ui::capturing_mouse()) {
      // Ignore mouse over ImGui elements
    }

    if (window.input().on_key_down(jkr::key::ESCAPE)) {
      window.close();
    }

    // Regular Updates
    // Render Objects
    
    // Render the Editor UI
    jkr::editor::ui::render();

    // Display GLFW framebuffer and poll events
    window.swap_buffers();
    window.poll_events();

    if (jkr::editor::ui::check_action(jkr::editor::ui::ActionFlags_CloseWindow)) {
      window.close();
    }
  }

  jkr::editor::ui::destroy();
  window.destroy();

  return 0;
} 

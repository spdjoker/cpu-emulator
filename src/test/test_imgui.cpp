#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "jkr/core/window.hpp"
#include "jkr/editor/ui.hpp"

void key_callback(GLFWwindow* window, int key, int, int action, int) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
  jkr::WindowProps props;
  props.enable(jkr::WindowProps::OPT_MAXIMIZED);
  // props.enable(jkr::WindowProps::OPT_TRANSPARENT_FRAMEBUFFER);
  // props.disable(jkr::WindowProps::OPT_RESIZABLE);
  // props.disable(jkr::WindowProps::OPT_DECORATED);

  jkr::Window window = jkr::Window::Create(props);
  if (!window.is_valid())
    return 1;

  glfwSetKeyCallback(window.glfw_window(), key_callback);

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
    
    // Render the Editor UI
    jkr::editor::ui::render();

    // Regular Updates
    // Render Objects

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

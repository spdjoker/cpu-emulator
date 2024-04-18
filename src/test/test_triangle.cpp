#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fmt/core.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "fmt/base.h"
#include "jkr/core/window.hpp"
#include "jkr/editor/ui.hpp"
#include "jkr/graphics/primitives.hpp"
#include "jkr/graphics/shader.hpp"

namespace jkrg = jkr::graphics;

int main() {
  jkr::WindowProps props;
  props.enable(jkr::WindowProps::OPT_MAXIMIZED);

  jkr::Window window = jkr::Window::Create(props);
  if (!window.is_valid())
    return 1;

  // Initializing ImGui
  window.make_context_current();

  if (glewInit() != GLEW_OK) {
    fmt::println("Failed to initialize GLEW.");
    window.destroy();
    return 1;
  }

  fmt::println("CREATING SHADER... ");
  jkr::graphics::Shader shader("res/test.vert", "res/test.frag");
  fmt::println("SUCCESS!");

  std::vector<float> vertices = {
    0.0f, 0.0f, 0.0f,
    0.5, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f
  };
  std::vector<unsigned int> indices = {1, 2, 3};

  jkrg::vao_t vao;
  jkrg::vbo_t vbo;
  jkrg::ibo_t ibo;
  jkrg::vao::create(vao);
  jkrg::vao::bind(vao);
  jkrg::vbo::create(vbo, vertices);
  jkrg::vao::link_attribute(0, 3, jkrg::dtype::FLOAT, 3 * sizeof(float), nullptr);
  jkrg::ibo::create(ibo, indices);

  glfwSwapInterval(1);
  jkr::editor::ui::create(window);

  while (!window.is_closing()) {
    window.clear_color_buffer();
    
    // if (!jkr::editor::ui::capturing_mouse()) {
    //   // Ignore mouse over ImGui elements
    // }

    if (window.input().on_key_down(jkr::key::ESCAPE)) {
      window.close();
    }

    // Regular Updates
    // Render Objects
    shader.activate();
    jkrg::vao::draw_triangles(vao, indices.size());
    
    // Render the Editor UI
    jkr::editor::ui::render();

    // Display GLFW framebuffer and poll events
    window.swap_buffers();
    window.poll_events();

    if (jkr::editor::ui::check_action(jkr::editor::ui::ActionFlags_CloseWindow)) {
      window.close();
    }
  }

  fmt::println("Cleaning IBO...");
  jkrg::ibo::destroy(ibo);
  fmt::println("Cleaning VBO...");
  jkrg::vbo::destroy(vbo);
  fmt::println("Cleaning VAO...");
  jkrg::vao::destroy(vao);
  fmt::println("Cleaning UI...");
  jkr::editor::ui::destroy();

  fmt::println("Cleaning window...");
  window.destroy();
  fmt::println("Closed...");

  return 0;
} 

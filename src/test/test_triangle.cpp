#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fmt/core.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "fmt/base.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/vector_float3.hpp"
#include "jkr/component/transform.hpp"
#include "jkr/core/window.hpp"
#include "jkr/editor/ui.hpp"
#include "jkr/graphics/primitives.hpp"
#include "jkr/graphics/shader.hpp"

namespace jkrc = jkr::component;
namespace jkrg = jkr::graphics;

struct vertex_t {
  glm::vec3 position;
  glm::vec3 color;
};

int main() {
  jkr::WindowProps props;

  jkr::Window window = jkr::Window::create(props);
  if (!window.is_valid())
    return 1;

  // Initializing ImGui
  window.make_context_current();

  if (!jkr::Window::enable_opengl_features()) {
    fmt::println("Failed to initialize GLEW.");
    window.destroy();
    return 1;
  }

  jkrg::Shader shader("res/test.vert", "res/test.frag");
  jkrg::uniform_t u_mat4_projection = shader.get_uniform("mat4_projection");
  jkrg::uniform_t u_mat4_view = shader.get_uniform("mat4_view");
  jkrg::uniform_t u_mat4_model = shader.get_uniform("mat4_model");

  std::vector<vertex_t> vertices = {
    {{0.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f}},
    {{0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f}},
    {{1.0f,0.0f,0.0f}, {0.0f,0.0f,1.0f}}
  };
  std::vector<unsigned int> indices = {0, 1, 2};

  jkrg::vao_t vao;
  jkrg::vbo_t vbo;
  jkrg::ibo_t ibo;
  jkrg::vao::create(vao);
  jkrg::vao::bind(vao);
  jkrg::vbo::create<vertex_t>(vbo, vertices);
  jkrg::vao::link_attribute(0, 3, jkrg::dtype::FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, position));
  jkrg::vao::link_attribute(1, 3, jkrg::dtype::FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, color));
  jkrg::ibo::create(ibo, indices);

  glfwSwapInterval(1);
  jkr::editor::ui::create(window);

  glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 mat4_view = glm::lookAt(camera_pos, camera_target, camera_up);
  glm::mat4 mat4_proj = glm::perspective(glm::radians(70.0f), ((float)props.size.x) / props.size.y, 0.1f, 100.0f);

  jkrc::Transform transform({1,0,0});

  while (!window.is_closing()) {
    window.clear_color_buffer();
    
    if (window.input().on_key_down(jkr::key::ESCAPE)) {
      window.close();
    }

    // Render Objects
    shader.activate();
    shader.set_uniform_mat4(u_mat4_projection, mat4_proj);
    shader.set_uniform_mat4(u_mat4_view, mat4_view);
    shader.set_uniform_mat4(u_mat4_model, transform.get_matrix());
    jkrg::vao::draw_triangles(vao, indices.size());
    
    // Render the Editor UI
    transform.update();
    jkr::editor::ui::render(transform);

    // Display GLFW framebuffer and poll events
    window.swap_buffers();
    window.poll_events();

    if (jkr::editor::ui::check_action(jkr::editor::ui::ActionFlags_CloseWindow)) {
      window.close();
    }
  }

  jkrg::ibo::destroy(ibo);
  jkrg::vbo::destroy(vbo);
  jkrg::vao::destroy(vao);
  jkr::editor::ui::destroy();

  window.destroy();

  return 0;
} 

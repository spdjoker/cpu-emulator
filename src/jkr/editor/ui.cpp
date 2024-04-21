#include "./ui.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "jkr/component/transform.hpp"
#include <string>

namespace jkr::editor::ui {

ActionFlags action_flags;
GLFWwindow* editor_window = nullptr;

bool show_inspector = true;
 
bool create(Window& window) {
  if (editor_window)
    return false;

  IMGUI_CHECKVERSION();
  if (!ImGui::CreateContext())
    return false;

  // IO Handling + Config Flags
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  //
  // Customizing Style
  ImGui::StyleColorsDark();

  // Initializing OpenGL/GLFW implementations of ImGui
  editor_window = window.glfw_window();
  if (!ImGui_ImplGlfw_InitForOpenGL(editor_window, true))
    goto clean_context;
  if (!ImGui_ImplOpenGL3_Init("#version 330"))
    goto clean_backend;
  return true;

// Any cleaning for if backend fails to initialize
clean_backend:
  ImGui_ImplGlfw_Shutdown();
clean_context:
  ImGui::DestroyContext();
  return false;
};

void destroy() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  editor_window = nullptr;
}

void render(component::Transform& transform) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Render UI Elements
  render_dock_space();

  if (show_inspector) {
    if (ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoCollapse)) {
      transform.render_inspector_view();
      ImGui::End();
    }
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

const std::string LABEL_PREFIX = "##";
std::string INSPECTOR_TABLE_PREFIX = "inspector-table";
std::string COL_PREFIX = "col-";

void field_input_float_element(const std::string& text, float &v) {
  ImGui::TableNextColumn();
  ImGui::PushItemWidth(-1);
  ImGui::InputFloat((LABEL_PREFIX + text).c_str(), &v);
  ImGui::PopItemWidth();
}

template <unsigned int n>
void field_input_float(const std::string& text, float values[n]) {
  ImGui::TableNextColumn();
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
  ImGui::TextUnformatted(text.c_str());

  ImGui::TableNextColumn();
  unsigned int i;
  if (ImGui::BeginTable((INSPECTOR_TABLE_PREFIX + std::to_string(n)).c_str(), n, ImGuiTableFlags_NoPadInnerX)) {
    for (i = 0; i < n; i++)
      ImGui::TableSetupColumn((COL_PREFIX + std::to_string(n)).c_str(), ImGuiTableColumnFlags_WidthStretch);

    for (i = 0; i < n; i++)
      field_input_float_element(text + std::to_string(n), values[i]);
    ImGui::EndTable();
  }
}

float pos[3] = {0.0f};
float rot[3] = {0.0f};
float sca[3] = {1.0f, 1.0f, 1.0f};
float piv[3] = {0.0f};

void render_dock_space() {
  constexpr ImGuiWindowFlags win_flags
    = ImGuiWindowFlags_NoTitleBar
    | ImGuiWindowFlags_NoDocking
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_NoMove
    | ImGuiWindowFlags_NoBringToFrontOnFocus
    | ImGuiWindowFlags_NoNavFocus
    | ImGuiWindowFlags_MenuBar
    | ImGuiWindowFlags_NoBackground;

  constexpr ImGuiDockNodeFlags dockspace_flags 
    = ImGuiDockNodeFlags_PassthruCentralNode;

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("DockSpace", nullptr, win_flags);
  ImGui::PopStyleVar(3);

  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  ImGui::BeginMenuBar();
  if (ImGui::BeginMenu("File")) { 
    if (ImGui::MenuItem("Open File")) {
      // Open File Viewer
    }
    if (ImGui::MenuItem("Close Program", "Esc")) {
      action_flags |= ActionFlags_CloseWindow;
    }
    ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Tools")) {
    ImGui::MenuItem("Inspector", NULL, &show_inspector);
    ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Help")) { 
    if (ImGui::MenuItem("WIP")) {
      // Open File Viewer
    }
    ImGui::EndMenu();
  }
  ImGui::EndMenuBar();

  ImGui::DockSpaceOverViewport(viewport, dockspace_flags);
  ImGui::End();
}

bool check_action(ActionFlags flags) {
  return (action_flags & flags) == flags;
}

bool capturing_mouse() {
  return ImGui::GetIO().WantCaptureMouse;
}

bool capturing_keyboard() {
  return ImGui::GetIO().WantCaptureKeyboard;
}

}

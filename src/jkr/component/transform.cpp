#include "./transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "fmt/base.h"
#include "glm/common.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "imgui/imgui.h"

namespace jkr::component {

  constexpr glm::vec3 ROTATION_MODULO = glm::vec3(360.0f, 360.0f, 360.0f);

  Transform::Transform(
    const glm::vec3& position, 
    const glm::vec3& rotation, 
    const glm::vec3& scale, 
    const glm::vec3& pivot
  ) 
  : vec3_pos(position)
  , vec3_rot(glm::mod(rotation, ROTATION_MODULO))
  , vec3_sca(scale)
  , vec3_piv(pivot) 
  , quat_rot(glm::radians(vec3_rot))
  {
    recalculate();
  }

  void Transform::recalculate() {
    // mat4_model = glm::translate(glm::mat4(1.0f), vec3_pos + vec3_piv);
    mat4_model = glm::translate(glm::mat4(1.0f), vec3_pos);
    mat4_model *= glm::mat4_cast(quat_rot);
    mat4_model = glm::scale(mat4_model, vec3_sca);
    mat4_model = glm::translate(mat4_model, -vec3_piv);
    flags.process_signal_flags();
  }

  void Transform::update() {
    if (flags.has_signal_flags()) {
      recalculate();
      return;
    }
    flags.clear_event_flags();
  }
  
  const char* TRANSFORM_INPUT_LABELS[4][4] = {
    {"position", "##trans-pos-x", "##trans-pos-y", "##trans-pos-z"}, 
    {"rotation", "##trans-rot-x", "##trans-rot-y", "##trans-rot-z"}, 
    {"scale", "##trans-sca-x", "##trans-sca-y", "##trans-sca-z"}, 
    {"pivot", "##trans-piv-x", "##trans-piv-y", "##trans-piv-z"}, 
  };

  void add_field_vec3(unsigned int id, glm::vec3& vec) {
    ImGui::TableNextColumn();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
    ImGui::TextUnformatted(TRANSFORM_INPUT_LABELS[id][0]);
    ImGui::TableNextColumn();
    if (ImGui::BeginTable("inspector-table-sub-3", 3, ImGuiTableFlags_NoPadInnerX)) {
      ImGui::TableSetupColumn("inspector-table-sub-3-0", ImGuiTableColumnFlags_WidthStretch);
      ImGui::TableSetupColumn("inspector-table-sub-3-1", ImGuiTableColumnFlags_WidthStretch);
      ImGui::TableSetupColumn("inspector-table-sub-3-2", ImGuiTableColumnFlags_WidthStretch);
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(-1);
      ImGui::InputFloat(TRANSFORM_INPUT_LABELS[id][1], &vec.x);
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(-1);
      ImGui::InputFloat(TRANSFORM_INPUT_LABELS[id][2], &vec.y);
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(-1);
      ImGui::InputFloat(TRANSFORM_INPUT_LABELS[id][3], &vec.z);
      ImGui::PopItemWidth();
      ImGui::EndTable();
    }
  }

  void Transform::render_inspector_view() {
    if (ImGui::CollapsingHeader("Transform")) {
      if (ImGui::BeginTable("inspector-table-2", 2)) {
        ImGui::TableSetupColumn("inspector-table-2-0", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("inspector-table-2-1", ImGuiTableColumnFlags_WidthStretch);

        glm::vec3 vec3_tmp = vec3_pos;
        add_field_vec3(0, vec3_tmp);
        if (vec3_tmp != vec3_pos)
          set_position(vec3_tmp);

        vec3_tmp = vec3_rot;
        add_field_vec3(1, vec3_tmp);
        if (vec3_tmp != vec3_rot)
          set_rotation(vec3_tmp);

        vec3_tmp = vec3_sca;
        add_field_vec3(2, vec3_tmp);
        if (vec3_tmp != vec3_sca)
          set_scale(vec3_tmp);

        vec3_tmp = vec3_piv;
        add_field_vec3(3, vec3_tmp);
        if (vec3_tmp != vec3_piv)
          set_pivot(vec3_tmp);

        ImGui::EndTable();
      }
    }
  }

  void Transform::translate(const glm::vec3& t) {
    flags.set_signal_flags(SIGNAL_POSITION);
    vec3_pos += t;
  }

  void Transform::rotate(const glm::vec3& r) {
    set_rotation(vec3_rot + r);
  }

  void Transform::scale(float s) {
    flags.set_signal_flags(SIGNAL_SCALE);
    vec3_sca += s;
  }

  void Transform::set_position(const glm::vec3& value) { 
    flags.set_signal_flags(SIGNAL_POSITION);
    vec3_pos = value; 
  }

  void Transform::set_rotation(const glm::vec3& value) { 
    flags.set_signal_flags(SIGNAL_ROTATION);
    vec3_rot = glm::mod(value, ROTATION_MODULO);
    quat_rot = glm::quat(glm::radians(vec3_rot));
    fmt::println("[Quaternion] x:{}, y:{}, z:{}, w:{}", quat_rot.x, quat_rot.y, quat_rot.z, quat_rot.w);
  }

  void Transform::set_rotation(const glm::quat& value) { 
    flags.set_signal_flags(SIGNAL_ROTATION);
    vec3_rot = glm::degrees(glm::eulerAngles(value)); 
    quat_rot = value;
  }

  void Transform::set_scale(const glm::vec3& value) { 
    flags.set_signal_flags(SIGNAL_SCALE);
    vec3_sca = value; 
  }

  void Transform::set_pivot(const glm::vec3& value) { 
    flags.set_signal_flags(SIGNAL_PIVOT);
    vec3_piv = value; 
  }
}
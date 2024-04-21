#pragma once

// Generates a model matrix from:
//  translation : vec3
//  rotation    : quaternion
//  scale       : vec3
//  pivot       : vec3

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/vector_float3.hpp"
#include "jkr/utils/flags.hpp"

namespace jkr::component {

  class Transform {
    glm::vec3 vec3_pos;
    glm::vec3 vec3_rot;
    glm::vec3 vec3_sca;
    glm::vec3 vec3_piv;
    glm::quat quat_rot;
    glm::mat4 mat4_model;
    utils::flags8 flags;

    enum EVENT_FLAGS {
      SIGNAL_POSITION   = 0b1,
      SIGNAL_ROTATION   = 0b10,
      SIGNAL_SCALE      = 0b100,
      SIGNAL_PIVOT      = 0b1000,
    };

    void recalculate();
  public:
    static constexpr glm::vec3 WORLD_RIGHT    = glm::vec3(1.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 WORLD_LEFT     = -WORLD_RIGHT;
    static constexpr glm::vec3 WORLD_UP       = glm::vec3(0.0f, 1.0f, 0.0f);
    static constexpr glm::vec3 WORLD_DOWN     = -WORLD_UP;
    static constexpr glm::vec3 WORLD_FORWARD  = glm::vec3(0.0f, 0.0f, 1.0f);
    static constexpr glm::vec3 WORLD_BACK     = -WORLD_FORWARD;

    Transform(
      const glm::vec3& position = glm::vec3(0.0f), 
      const glm::vec3& rotation = glm::vec3(0.0f),
      const glm::vec3& scale = glm::vec3(1.0f), 
      const glm::vec3& pivot = glm::vec3(0.0f)
      );

    void update();
    void render_inspector_view();

    void translate(const glm::vec3& t);
    void rotate(const glm::vec3& r);
    void scale(float s);
    void set_position(const glm::vec3& value);
    void set_rotation(const glm::vec3& value);
    void set_rotation(const glm::quat& value);
    void set_scale(const glm::vec3& value);
    void set_pivot(const glm::vec3& value);

    auto right() const { return quat_rot * WORLD_RIGHT; }
    auto up() const { return quat_rot * WORLD_UP; }
    auto forward() const { return quat_rot * WORLD_FORWARD; }
    const auto& get_position() const { return vec3_pos; }
    const auto& get_rotation() const { return vec3_rot; }
    const auto& get_scale() const { return vec3_sca; }
    const auto& get_pivot() const { return vec3_piv; }
    const auto& get_quaternion() const { return quat_rot; }
    const auto& get_matrix() const { return mat4_model; }

    bool on_recalculation() const { return flags.has_event_flags(); }
    bool on_position_update() const { return flags.has_event_flags_any(SIGNAL_POSITION); }
    bool on_rotation_update() const { return flags.has_event_flags_any(SIGNAL_ROTATION); }
    bool on_scale_update() const { return flags.has_event_flags_any(SIGNAL_SCALE); }
    bool on_pivot_update() const { return flags.has_event_flags_any(SIGNAL_PIVOT); }

  };

}
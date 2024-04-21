#version 330 core

layout (location = 0) in vec3 loc_pos;
layout (location = 1) in vec3 loc_color;

uniform mat4 mat4_projection;
uniform mat4 mat4_view;
uniform mat4 mat4_model;

out vec4 vertex_color;

void main() {
  vertex_color = vec4(loc_color, 1.0);
  gl_Position = mat4_projection * mat4_view * mat4_model * vec4(loc_pos, 1.0);
}
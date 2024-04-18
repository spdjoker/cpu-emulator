#version 330 core

layout (location = 0) in vec3 loc_pos;
// layout (location = 1) in vec3 loc_color;

out vec3 vertex_color;

void main() {
  vertex_color = vec3(0.0, 1.0, 0.0);
  gl_Position = vec4(loc_pos, 1.0);
}
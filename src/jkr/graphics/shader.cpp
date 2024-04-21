#include "./shader.hpp"
#include "fmt/base.h"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

void compile_errors(unsigned int shader, const char *type) {
  GLint has_compiled;
  char log[1024];

  if (std::strcmp(type, "PROGRAM")) {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
    if (has_compiled == GL_FALSE) {
      glGetShaderInfoLog(shader, 1024, NULL, log);
      fmt::print("SHADER_COMPILATION_ERROR for : {}\n{}\n", type, log);
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &has_compiled);
    if (has_compiled == GL_FALSE) {
      glGetProgramInfoLog(shader, 1024, NULL, log);
      fmt::print("SHADER_LINKING_ERROR for : {}\n{}\n", type, log);
    }
  }
}


std::string get_file_contents(const char *filename) {
  std::ifstream input_file(filename, std::ios::binary);

  if (input_file) {
    std::string contents;
    input_file.seekg(0, std::ios::end);
    contents.resize(input_file.tellg());

    input_file.seekg(0, std::ios::beg);
    input_file.read(&contents[0], contents.size());
    input_file.close();

    return contents;
  }
  fmt::println("Failed to get file contents of shader: {}\n", filename);
  throw(errno);
}

namespace jkr::graphics {

  Shader::Shader(const char *vert_file, const char *frag_file) {
    // Read the files and store their contents
    std::string vert_code = get_file_contents(vert_file);
    std::string frag_code = get_file_contents(frag_file);

    // Converts the shader files into usable character strings
    const char *vert_source = vert_code.c_str();
    const char *frag_source = frag_code.c_str();

    fmt::println("Generating vertex shader '{}'...", vert_file);
    // Create the vertex shader and store the reference
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_source, NULL);
    glCompileShader(vert_shader);
    compile_errors(vert_shader, "VERTEX");

    fmt::println("Generating fragment shader '{}'...", frag_file);
    // Create the fragment shader and store the reference
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_source, NULL);
    glCompileShader(frag_shader);
    compile_errors(frag_shader, "FRAGMENT");

    fmt::println("Assembling shader program...");
    // Create the shader program and attach the shaders
    shader_id = glCreateProgram();
    glAttachShader(shader_id, vert_shader);
    glAttachShader(shader_id, frag_shader);
    glLinkProgram(shader_id);
    compile_errors(shader_id, "PROGRAM");

    // Delete the shaders
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
  }

  Shader::~Shader() {
    glDeleteShader(shader_id);
  }

  void Shader::activate() { glUseProgram(shader_id); }

  uniform_t Shader::get_uniform(const char* uniform_name) {
    return glGetUniformLocation(shader_id, uniform_name);
  }  

  void Shader::set_uniform_mat4(uniform_t loc, const glm::mat4& mat, bool transpose) {
    glUniformMatrix4fv(loc, 1, transpose, glm::value_ptr(mat));
  }
}

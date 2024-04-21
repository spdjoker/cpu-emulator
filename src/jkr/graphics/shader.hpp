#pragma once

#include "glm/fwd.hpp"
namespace jkr::graphics {

  using uniform_t = int;

  class Shader {
    unsigned int shader_id;

    public:
    Shader(const char* vert_file, const char* frag_file);
    ~Shader();

    void activate();

    uniform_t get_uniform(const char* uniform_name);
    void set_uniform_mat4(uniform_t loc, const glm::mat4& mat, bool transpose = false);
  };

}
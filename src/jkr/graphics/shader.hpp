#pragma once

namespace jkr::graphics {

  class Shader {
    unsigned int shader_id;

    public:
    Shader(const char* vert_file, const char* frag_file);
    ~Shader();

    void activate();
  };

}
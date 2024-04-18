#include "./primitives.hpp"
#include <GL/glew.h>

namespace jkr::graphics {
  
  namespace vao {
    void create(vao_t& out_vao) {
      glGenVertexArrays(1, &out_vao);
    }

    void destroy(vao_t& out_vao) {
      glDeleteVertexArrays(1, &out_vao);
      out_vao = 0;
    }

    void bind(vao_t vao) {
      glBindVertexArray(vao);
    }

    void unbind() {
      glBindVertexArray(0);
    }

    void link_attribute(uint_t layout, uint_t count, dtype_t type, int stride, void* offset, bool normalize) {
      glVertexAttribPointer(layout, count, type, normalize, stride, offset);
      glEnableVertexAttribArray(layout);
    }

    void draw_triangles(vao_t vao, uint_t num_indices) {
      bind(vao);
      glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
    }
  }

  namespace vbo {
    void create(vbo_t& out_vbo, const std::vector<float>& data) {
      glGenBuffers(1, &out_vbo);
      if (!out_vbo) return;
      glBindBuffer(GL_ARRAY_BUFFER, out_vbo);
      glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    }

    void destroy(vbo_t& out_vbo) {
      glDeleteBuffers(1, &out_vbo);
      out_vbo = 0;
    }

    void bind(vbo_t vbo) {
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }

    void unbind() {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
  }

  namespace ibo {
    void create(ibo_t& out_ibo, const std::vector<uint_t>& indices) {
      glGenBuffers(1, &out_ibo);
      if (!out_ibo) return;
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out_ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint_t), indices.data(), GL_STATIC_DRAW);
    }

    void destroy(ibo_t& out_ibo) {
      glDeleteBuffers(1, &out_ibo);
      out_ibo = 0;
    }

    void bind(ibo_t ibo) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    }

    void unbind() {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
  }

  namespace dtype {
    const uint_t BYTE = GL_BYTE;
    const uint_t FLOAT = GL_FLOAT;
    const uint_t INT = GL_INT;
    const uint_t UNSIGNED_INT = GL_UNSIGNED_INT;
  }

}

#pragma once

#include <vector>

namespace jkr::graphics {

  using uint_t = unsigned int;
  using vao_t = uint_t;
  using vbo_t = uint_t;
  using ibo_t = uint_t;
  using dtype_t = uint_t;

  // VAO
  namespace vao {
    void create(vao_t& out_vao);
    void destroy(vao_t& out_vao);
    void bind(vao_t vao);
    void unbind();

    // Links the bound VBO attribute to the bound VAO's layout
    // @param layout The attribute layout location in the VAO
    // @param components The number of components per attribute
    // @param type The data type of the attribute (e.g., )
    void link_attribute(uint_t layout, uint_t components, dtype_t type, int stride, void* offset, bool normalize = false);
    void draw_triangles(vao_t vao, uint_t num_indices);
  }

  // Vertex Buffer Object
  namespace vbo {
    // TODO: allow updating data using glBufferSubData() and glMapBuffer()
    void create(vbo_t& out_vbo, const void* data, unsigned int bytes);
    template <typename T>
    void create(vbo_t& out_vbo, const std::vector<T>& data) {
      create(out_vbo, data.data(), data.size() * sizeof(T));
    }
    // void create(vbo_t& out_vbo, const std::vector<float>& data);
    void destroy(vbo_t& out_vbo);
    void bind(vbo_t vbo);
    void unbind();
  }

  // Index Buffer Object
  namespace ibo {
    // TODO: allow updating data using glBufferSubData() and glMapBuffer()
    void create(ibo_t& out_ibo, const std::vector<uint_t>& indices);
    void destroy(ibo_t& out_ibo);
    void bind(ibo_t ibo);
    void unbind();
  }

  namespace dtype {
    extern const dtype_t BYTE;
    extern const dtype_t FLOAT;
    extern const dtype_t INT;
    extern const dtype_t UNSIGNED_INT;
    extern const dtype_t ARRAY_BUFFER;
  }
}

#pragma once

#include <string>

namespace jkr::editor {

class IView {
  virtual void draw() = 0;
};

void input_vec3(const char* view_name, const char* label, float* p);

};
#pragma once

#include "jkr/editor/view.hpp"

namespace jkr::editor::view {

class Inspector : IView {
  void draw() override;

  static bool section(const char* label);
};


}
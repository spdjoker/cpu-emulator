#pragma once

#include "jkr/core/window.hpp"
#include "jkr/component/transform.hpp"

namespace jkr::editor::ui {
  
using ActionFlags = int;
enum ActionFlags_ {
  ActionFlags_None = 0,
  ActionFlags_CloseWindow = 1
};

bool create(Window& window);
void destroy();

void render(component::Transform& transform);
void render_dock_space();
void render_inspector();

bool check_action(ActionFlags flags);
bool capturing_mouse();
bool capturing_keyboard();

}
#include "./input.hpp"

#include <GLFW/glfw3.h>

namespace jkr {

constexpr unsigned char KEYSTATE_PRESS  = 0b01;
constexpr unsigned char KEYSTATE_RELEASE = 0b10;
constexpr unsigned char KEYSTATE_INV_PRESS = ~KEYSTATE_PRESS;
constexpr unsigned char KEYSTATE_ACTION_BITS = 0b11;

Input::Input() : m_key_states(key::LAST + 1, 0) {}

void Input::set_key_down(key_t key) noexcept {
  m_key_states[key] |= KEYSTATE_PRESS;
}

void Input::set_key_up(key_t key) noexcept {
  m_key_states[key] &= KEYSTATE_INV_PRESS;
}

void Input::poll_events() {
  for (auto& key_state : m_key_states) {
    key_state = (key_state << 1) | (key_state & 1);
  }
}

bool Input::on_key_down(key_t key) const noexcept {
  return (m_key_states[key] & KEYSTATE_ACTION_BITS) == KEYSTATE_PRESS;
}

bool Input::on_key_up(key_t key) const noexcept {
  return (m_key_states[key] & KEYSTATE_ACTION_BITS) == KEYSTATE_RELEASE;
}

bool Input::on_key(key_t key) const noexcept {
  return m_key_states[key] & 1;
}

namespace key {
  const key_t SPACE = GLFW_KEY_SPACE; 
  const key_t APOSTROPHE = GLFW_KEY_APOSTROPHE; 
  const key_t COMMA = GLFW_KEY_COMMA; 
  const key_t MINUS = GLFW_KEY_MINUS; 
  const key_t PERIOD = GLFW_KEY_PERIOD; 
  const key_t SLASH = GLFW_KEY_SLASH; 

  const key_t ALPHA_0 = GLFW_KEY_0; 
  const key_t ALPHA_1 = GLFW_KEY_1; 
  const key_t ALPHA_2 = GLFW_KEY_2; 
  const key_t ALPHA_3 = GLFW_KEY_3; 
  const key_t ALPHA_4 = GLFW_KEY_4; 
  const key_t ALPHA_5 = GLFW_KEY_5; 
  const key_t ALPHA_6 = GLFW_KEY_6; 
  const key_t ALPHA_7 = GLFW_KEY_7; 
  const key_t ALPHA_8 = GLFW_KEY_8; 
  const key_t ALPHA_9 = GLFW_KEY_9; 

  const key_t SEMICOLON = GLFW_KEY_SEMICOLON; 
  const key_t EQUAL = GLFW_KEY_EQUAL; 

  // Alphabet
  const key_t A = GLFW_KEY_A; 
  const key_t B = GLFW_KEY_B; 
  const key_t C = GLFW_KEY_C; 
  const key_t D = GLFW_KEY_D; 
  const key_t E = GLFW_KEY_E; 
  const key_t F = GLFW_KEY_F; 
  const key_t G = GLFW_KEY_G; 
  const key_t H = GLFW_KEY_H; 
  const key_t I = GLFW_KEY_I; 
  const key_t J = GLFW_KEY_J; 
  const key_t K = GLFW_KEY_K; 
  const key_t L = GLFW_KEY_L; 
  const key_t M = GLFW_KEY_M; 
  const key_t N = GLFW_KEY_N; 
  const key_t O = GLFW_KEY_O; 
  const key_t P = GLFW_KEY_P; 
  const key_t Q = GLFW_KEY_Q; 
  const key_t R = GLFW_KEY_R; 
  const key_t S = GLFW_KEY_S; 
  const key_t T = GLFW_KEY_T; 
  const key_t U = GLFW_KEY_U; 
  const key_t V = GLFW_KEY_V; 
  const key_t W = GLFW_KEY_W; 
  const key_t X = GLFW_KEY_X; 
  const key_t Y = GLFW_KEY_Y; 
  const key_t Z = GLFW_KEY_Z; 

  const key_t LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET; 
  const key_t BACKSLASH = GLFW_KEY_BACKSLASH; 
  const key_t RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET; 
  const key_t GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT; 
  const key_t WORLD_1 = GLFW_KEY_WORLD_1; 
  const key_t WORLD_2 = GLFW_KEY_WORLD_2; 
  const key_t ESCAPE = GLFW_KEY_ESCAPE; 
  const key_t ENTER = GLFW_KEY_ENTER; 
  const key_t TAB = GLFW_KEY_TAB; 
  const key_t BACKSPACE = GLFW_KEY_BACKSPACE; 
  const key_t INSERT = GLFW_KEY_INSERT; 
  const key_t DELETE = GLFW_KEY_DELETE; 
  const key_t RIGHT = GLFW_KEY_RIGHT; 
  const key_t LEFT = GLFW_KEY_LEFT; 
  const key_t DOWN = GLFW_KEY_DOWN; 
  const key_t UP = GLFW_KEY_UP; 
  const key_t PAGE_UP = GLFW_KEY_PAGE_UP; 
  const key_t PAGE_DOWN = GLFW_KEY_PAGE_DOWN; 
  const key_t HOME = GLFW_KEY_HOME; 
  const key_t END = GLFW_KEY_END; 
  const key_t CAPS_LOCK = GLFW_KEY_CAPS_LOCK; 
  const key_t SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK; 
  const key_t NUM_LOCK = GLFW_KEY_NUM_LOCK; 
  const key_t PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN; 
  const key_t PAUSE = GLFW_KEY_PAUSE; 

  // F Keys
  const key_t F1 = GLFW_KEY_F1; 
  const key_t F2 = GLFW_KEY_F2; 
  const key_t F3 = GLFW_KEY_F3; 
  const key_t F4 = GLFW_KEY_F4; 
  const key_t F5 = GLFW_KEY_F5; 
  const key_t F6 = GLFW_KEY_F6; 
  const key_t F7 = GLFW_KEY_F7; 
  const key_t F8 = GLFW_KEY_F8; 
  const key_t F9 = GLFW_KEY_F9; 
  const key_t F10 = GLFW_KEY_F10; 
  const key_t F11 = GLFW_KEY_F11; 
  const key_t F12 = GLFW_KEY_F12; 
  const key_t F13 = GLFW_KEY_F13; 
  const key_t F14 = GLFW_KEY_F14; 
  const key_t F15 = GLFW_KEY_F15; 
  const key_t F16 = GLFW_KEY_F16; 
  const key_t F17 = GLFW_KEY_F17; 
  const key_t F18 = GLFW_KEY_F18; 
  const key_t F19 = GLFW_KEY_F19; 
  const key_t F20 = GLFW_KEY_F20; 
  const key_t F21 = GLFW_KEY_F21; 
  const key_t F22 = GLFW_KEY_F22; 
  const key_t F23 = GLFW_KEY_F23; 
  const key_t F24 = GLFW_KEY_F24; 
  const key_t F25 = GLFW_KEY_F25; 

  // Keypad
  const key_t KEYPAD_0 = GLFW_KEY_KP_0; 
  const key_t KEYPAD_1 = GLFW_KEY_KP_1; 
  const key_t KEYPAD_2 = GLFW_KEY_KP_2; 
  const key_t KEYPAD_3 = GLFW_KEY_KP_3; 
  const key_t KEYPAD_4 = GLFW_KEY_KP_4; 
  const key_t KEYPAD_5 = GLFW_KEY_KP_5; 
  const key_t KEYPAD_6 = GLFW_KEY_KP_6; 
  const key_t KEYPAD_7 = GLFW_KEY_KP_7; 
  const key_t KEYPAD_8 = GLFW_KEY_KP_8; 
  const key_t KEYPAD_9 = GLFW_KEY_KP_9; 

  const key_t KEYPAD_DECIMAL = GLFW_KEY_KP_DECIMAL; 
  const key_t KEYPAD_DIVIDE = GLFW_KEY_KP_DIVIDE; 
  const key_t KEYPAD_MULTIPLY = GLFW_KEY_KP_MULTIPLY; 
  const key_t KEYPAD_SUBTRACT = GLFW_KEY_KP_SUBTRACT; 
  const key_t KEYPAD_ADD = GLFW_KEY_KP_ADD; 
  const key_t KEYPAD_ENTER = GLFW_KEY_KP_ENTER; 
  const key_t KEYPAD_EQUAL = GLFW_KEY_KP_EQUAL; 

  // Mods
  const key_t LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT; 
  const key_t LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL; 
  const key_t LEFT_ALT = GLFW_KEY_LEFT_ALT; 
  const key_t LEFT_SUPER = GLFW_KEY_LEFT_SUPER; 
  const key_t RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT; 
  const key_t RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL; 
  const key_t RIGHT_ALT = GLFW_KEY_RIGHT_ALT; 
  const key_t RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER; 
  const key_t MENU = GLFW_KEY_MENU; 

  const key_t LAST = GLFW_KEY_LAST; 
};
}
#pragma once

#include <vector>
namespace jkr {

using key_t = unsigned int;

class Input {
  std::vector<unsigned char> m_key_states;

  public:
  Input();

  // Stages inputs, preparing for the next set of inputs
  void poll_events();

  void set_key_down(key_t key) noexcept;
  void set_key_up(key_t key) noexcept;

  // Returns true only on the frame where the key was pressed
  bool on_key_down(key_t key) const noexcept;
  // Returns true only on the frame where the key was released
  bool on_key_up(key_t key) const noexcept;
  // Returns true when the key is being held down
  bool on_key(key_t key) const noexcept;
};

namespace key {
  extern const key_t SPACE;
  extern const key_t APOSTROPHE;
  extern const key_t COMMA;
  extern const key_t MINUS;
  extern const key_t PERIOD;
  extern const key_t SLASH;

  extern const key_t ALPHA_0;
  extern const key_t ALPHA_1;
  extern const key_t ALPHA_2;
  extern const key_t ALPHA_3;
  extern const key_t ALPHA_4;
  extern const key_t ALPHA_5;
  extern const key_t ALPHA_6;
  extern const key_t ALPHA_7;
  extern const key_t ALPHA_8;
  extern const key_t ALPHA_9;

  extern const key_t SEMICOLON;
  extern const key_t EQUAL;

  // Alphabet
  extern const key_t A;
  extern const key_t B;
  extern const key_t C;
  extern const key_t D;
  extern const key_t E;
  extern const key_t F;
  extern const key_t G;
  extern const key_t H;
  extern const key_t I;
  extern const key_t J;
  extern const key_t K;
  extern const key_t L;
  extern const key_t M;
  extern const key_t N;
  extern const key_t O;
  extern const key_t P;
  extern const key_t Q;
  extern const key_t R;
  extern const key_t S;
  extern const key_t T;
  extern const key_t U;
  extern const key_t V;
  extern const key_t W;
  extern const key_t X;
  extern const key_t Y;
  extern const key_t Z;

  extern const key_t LEFT_BRACKET;
  extern const key_t BACKSLASH;
  extern const key_t RIGHT_BRACKET;
  extern const key_t GRAVE_ACCENT;
  extern const key_t WORLD_1;
  extern const key_t WORLD_2;
  extern const key_t ESCAPE;
  extern const key_t ENTER;
  extern const key_t TAB;
  extern const key_t BACKSPACE;
  extern const key_t INSERT;
  extern const key_t DELETE;
  extern const key_t RIGHT;
  extern const key_t LEFT;
  extern const key_t DOWN;
  extern const key_t UP;
  extern const key_t PAGE_UP;
  extern const key_t PAGE_DOWN;
  extern const key_t HOME;
  extern const key_t END;
  extern const key_t CAPS_LOCK;
  extern const key_t SCROLL_LOCK;
  extern const key_t NUM_LOCK;
  extern const key_t PRINT_SCREEN;
  extern const key_t PAUSE;

  // F Keys
  extern const key_t F1;
  extern const key_t F2;
  extern const key_t F3;
  extern const key_t F4;
  extern const key_t F5;
  extern const key_t F6;
  extern const key_t F7;
  extern const key_t F8;
  extern const key_t F9;
  extern const key_t F10;
  extern const key_t F11;
  extern const key_t F12;
  extern const key_t F13;
  extern const key_t F14;
  extern const key_t F15;
  extern const key_t F16;
  extern const key_t F17;
  extern const key_t F18;
  extern const key_t F19;
  extern const key_t F20;
  extern const key_t F21;
  extern const key_t F22;
  extern const key_t F23;
  extern const key_t F24;
  extern const key_t F25;

  // Keypad
  extern const key_t KEYPAD_0;
  extern const key_t KEYPAD_1;
  extern const key_t KEYPAD_2;
  extern const key_t KEYPAD_3;
  extern const key_t KEYPAD_4;
  extern const key_t KEYPAD_5;
  extern const key_t KEYPAD_6;
  extern const key_t KEYPAD_7;
  extern const key_t KEYPAD_8;
  extern const key_t KEYPAD_9;

  extern const key_t KEYPAD_DECIMAL;
  extern const key_t KEYPAD_DIVIDE;
  extern const key_t KEYPAD_MULTIPLY;
  extern const key_t KEYPAD_SUBTRACT;
  extern const key_t KEYPAD_ADD;
  extern const key_t KEYPAD_ENTER;
  extern const key_t KEYPAD_EQUAL;

  // Mods
  extern const key_t LEFT_SHIFT;
  extern const key_t LEFT_CONTROL;
  extern const key_t LEFT_ALT;
  extern const key_t LEFT_SUPER;
  extern const key_t RIGHT_SHIFT;
  extern const key_t RIGHT_CONTROL;
  extern const key_t RIGHT_ALT;
  extern const key_t RIGHT_SUPER;
  extern const key_t MENU;

  extern const key_t LAST;
};

}
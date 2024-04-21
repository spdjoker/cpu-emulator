#pragma once

template <typename T>
class tracker {
  T data;
  bool dirty;

public:
  tracker(const T& obj) : data(obj), dirty(false) {}

  void reset() { dirty = true; }
  bool is_dirty() const { return dirty; }

  operator const T&() const { return data; }

  tracker& operator =(const T& value) {
    dirty = true;
    data = value;
  }
};
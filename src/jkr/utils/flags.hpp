#pragma once

namespace jkr::utils {

  template<typename T>
  class flags {
    T signalFlags = 0;
    T eventFlags = 0;

  public:
    flags(T flags) : signalFlags(flags), eventFlags() {}
    flags() : signalFlags(), eventFlags() {}

    void set_signal_flags(T bits) { signalFlags |= bits; }
    void toggle_signal_flags(T bits) { signalFlags ^= bits; }
    void clear_event_flags() { eventFlags = 0; }
    void process_signal_flags() { 
      eventFlags = signalFlags;
      signalFlags = 0;
    }

    bool has_signal_flags() const { return signalFlags; }
    bool has_signal_flags_any(T bits) const { return signalFlags & bits; }
    bool has_signal_flags_all(T bits) const { return (signalFlags & bits) == bits; }

    bool has_event_flags() const { return eventFlags; }
    bool has_event_flags_any(T bits) const { return eventFlags & bits; }
    bool has_event_flags_all(T bits) const { return (eventFlags & bits) == bits; }
  };

  using flags8 = flags<unsigned char>;
  using flags16 = flags<unsigned short>;
  using flags32 = flags<unsigned int>;
  using flags64 = flags<unsigned long long>;

}
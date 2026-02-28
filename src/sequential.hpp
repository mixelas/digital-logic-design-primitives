#pragma once
#include "logic.hpp"
#include <cstdint>

namespace dldp {

// Simple edge-triggered D flip-flop (rising edge)
class DFlipFlop {
public:
  void set_d(Bit d) { d_ = d; }
  Bit q() const { return q_; }

  // Call on clock rising edge
  void tick(Bit rst=false) {
    if (rst) q_ = false;
    else q_ = d_;
  }

private:
  Bit d_ = false;
  Bit q_ = false;
};

// 4-bit synchronous up-counter
class Counter4 {
public:
  std::uint8_t q() const { return static_cast<std::uint8_t>(q_ & 0xF); }

  // rising edge
  void tick(Bit enable=true, Bit rst=false) {
    if (rst) q_ = 0;
    else if (enable) q_ = static_cast<std::uint8_t>((q_ + 1) & 0xF);
  }

private:
  std::uint8_t q_ = 0;
};

// Simple traffic light FSM: GREEN -> YELLOW -> RED -> GREEN ...
enum class Light { GREEN, YELLOW, RED };

class TrafficLightFSM {
public:
  Light state() const { return s_; }

  // One tick = one time step (you can interpret it as "N cycles" in docs)
  void tick(Bit rst=false) {
    if (rst) { s_ = Light::GREEN; return; }
    switch (s_) {
      case Light::GREEN:  s_ = Light::YELLOW; break;
      case Light::YELLOW: s_ = Light::RED;    break;
      case Light::RED:    s_ = Light::GREEN;  break;
    }
  }

private:
  Light s_ = Light::GREEN;
};

} // namespace dldp
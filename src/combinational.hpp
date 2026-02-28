#pragma once
#include "logic.hpp"
#include <cstdint>

namespace dldp {

// Half adder
inline HalfAdderOut half_adder(Bit a, Bit b) {
  return { XOR(a,b), AND(a,b) };
}

// Full adder
inline FullAdderOut full_adder(Bit a, Bit b, Bit cin) {
  Bit s1 = XOR(a,b);
  Bit sum = XOR(s1, cin);
  Bit carry = OR(AND(a,b), AND(s1, cin));
  return { sum, carry };
}

// 4-bit ripple-carry adder
struct Add4Out { std::uint8_t sum4; Bit carry_out; };

inline Add4Out ripple_add4(std::uint8_t a4, std::uint8_t b4, Bit cin=false) {
  std::uint8_t sum = 0;
  Bit c = cin;
  for (int i=0; i<4; ++i) {
    auto fo = full_adder(get_bit(a4,i), get_bit(b4,i), c);
    sum = static_cast<std::uint8_t>(set_bit(sum, i, fo.sum));
    c = fo.carry;
  }
  return { static_cast<std::uint8_t>(sum & 0xF), c };
}

// 2:1 mux
inline Bit mux2(Bit sel, Bit d0, Bit d1) {
  return sel ? d1 : d0;
}

// 3-to-8 decoder (one-hot)
inline std::uint8_t decoder3to8(std::uint8_t a3, Bit en=true) {
  if (!en) return 0;
  std::uint8_t idx = static_cast<std::uint8_t>(a3 & 0x7);
  return static_cast<std::uint8_t>(1U << idx);
}

} // namespace dldp
#pragma once
#include <cstdint>

namespace dldp {

using Bit = bool;

struct HalfAdderOut { Bit sum; Bit carry; };
struct FullAdderOut { Bit sum; Bit carry; };

inline Bit NOT(Bit a) { return !a; }
inline Bit AND(Bit a, Bit b) { return a && b; }
inline Bit OR(Bit a, Bit b) { return a || b; }
inline Bit XOR(Bit a, Bit b) { return a != b; }

// Helpers for packing/unpacking bits (LSB first)
inline Bit get_bit(std::uint32_t x, int i) { return (x >> i) & 1U; }
inline std::uint32_t set_bit(std::uint32_t x, int i, Bit b) {
  if (b) return x | (1U << i);
  return x & ~(1U << i);
}

} // namespace dldp
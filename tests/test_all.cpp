#include <cassert>
#include <cstdint>
#include "combinational.hpp"
#include "sequential.hpp"

using namespace dldp;

int main() {
  // Half adder
  {
    auto o = half_adder(false,false); assert(o.sum==0 && o.carry==0);
    o = half_adder(true,false);       assert(o.sum==1 && o.carry==0);
    o = half_adder(false,true);       assert(o.sum==1 && o.carry==0);
    o = half_adder(true,true);        assert(o.sum==0 && o.carry==1);
  }

  // Full adder quick check
  {
    auto o = full_adder(true,true,true); // 1+1+1=3
    assert(o.sum==1 && o.carry==1);
  }

  // Ripple add 4-bit
  {
    auto r = ripple_add4(0b0011, 0b0101, false); // 3+5=8
    assert(r.sum4 == 0b1000 && r.carry_out==0);

    r = ripple_add4(0b1111, 0b0001, false); // 15+1=16 -> sum=0 carry=1
    assert(r.sum4 == 0b0000 && r.carry_out==1);
  }

  // Mux
  {
    assert(mux2(false, 0, 1) == 0);
    assert(mux2(true,  0, 1) == 1);
  }

  // Decoder
  {
    assert(decoder3to8(0, true) == 0b00000001);
    assert(decoder3to8(7, true) == 0b10000000);
    assert(decoder3to8(3, false) == 0);
  }

  // DFF
  {
    DFlipFlop dff;
    dff.set_d(true);
    dff.tick(false);
    assert(dff.q() == true);
    dff.tick(true);
    assert(dff.q() == false);
  }

  // Counter
  {
    Counter4 c;
    c.tick(true,false); assert(c.q()==1);
    for(int i=0;i<14;i++) c.tick(true,false);
    assert(c.q()==15);
    c.tick(true,false); assert(c.q()==0); // wrap
  }

  // FSM
  {
    TrafficLightFSM f;
    assert(f.state() == Light::GREEN);
    f.tick(false); assert(f.state() == Light::YELLOW);
    f.tick(false); assert(f.state() == Light::RED);
    f.tick(false); assert(f.state() == Light::GREEN);
    f.tick(true);  assert(f.state() == Light::GREEN);
  }

  return 0;
}
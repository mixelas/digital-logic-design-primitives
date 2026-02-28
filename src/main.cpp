#include <iostream>
#include "combinational.hpp"
#include "sequential.hpp"

using namespace dldp;

int main() {
  auto r = ripple_add4(3, 5);
  std::cout << "3 + 5 = " << (int)r.sum4 << " carry=" << r.carry_out << "\n";

  Counter4 c;
  for (int i=0;i<6;i++){ c.tick(true,false); std::cout << "counter=" << (int)c.q() << "\n"; }

  TrafficLightFSM f;
  for (int i=0;i<5;i++){
    f.tick(false);
    std::cout << "fsm tick\n";
  }
}
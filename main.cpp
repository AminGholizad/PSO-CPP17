#include <iostream>
#include "pso.hpp"
#include <cmath>
const double pi = 3.1415926535897932385;
template<pso::ull N>
std::pair<double,double>cost_fcn(pso::vars<N> x){
  double s = 0.;
  double c = 0.;
  for (size_t i = 0; i < x.size(); i++) {
    s+=std::sin(x[i]*3);
    c+=std::sin(x[i]);
  }
  s=std::abs(s);
  c=std::abs(c/4-0.8);
  return std::make_pair(s,c);
}
int main(){
  const pso::ull Nvars = 4;
  const pso::ull Swarm_size = 100;
  pso::vars<Nvars> l{0,0,0,0};
  pso::vars<Nvars> u{pi/2,pi/2,pi/2,pi/2};
  auto p = pso::pso<Nvars,Swarm_size>(l,u,cost_fcn<Nvars>,2000);
  p.info();
  return 0;
}

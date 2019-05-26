#include <iostream>
#include "pso.hpp"
template<pso::ull N>
std::pair<double,double>cost_fcn(pso::vars<N> x){
  double s = 0.;
  double c = 0.;
  for (size_t i = 0; i < x.size(); i++) {
    s+=x[i]*x[i];
    c+=(x[i]>0)?x[i]:0;
  }
  return std::make_pair(s,c);
}
int main(){
  const pso::ull Nvars = 4;
  const pso::ull Swarm_size = 100;
  pso::vars<Nvars> l{-10.,-10.,-10.,-10.};
  pso::vars<Nvars> u{10.,10.,10.,10.};
  auto p = pso::pso<Nvars,Swarm_size>(l,u,cost_fcn<Nvars>);
  p.info();
  return 0;
}

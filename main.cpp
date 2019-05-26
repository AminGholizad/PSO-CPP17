#include <iostream>
#include "pso.hpp"
template<pso::ull N>
std::pair<double,double>cost_fcn(pso::arr<N> x){
  double s = 0.;
  double c = 0.;
  for (size_t i = 0; i < x.size(); i++) {
    s+=x[i]*x[i];
    c+=(x[i]>0)?x[i]:0;
  }
  return std::make_pair(s,c);
}
int main(){
  const pso::ull N = 4;
  const pso::ull S = 100;
  pso::arr<N> l{-10.,-10.,-10.,-10.};
  pso::arr<N> u{10.,10.,10.,10.};
  auto p = pso::pso<N,S>(l,u,cost_fcn<N>);
  p.info();
  return 0;
}

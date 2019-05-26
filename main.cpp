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
  double c[2] = {0.2,0.2};
  double w[2] = {0.1,0.01};
  const pso::ull N = 4;
  pso::arr<N> l{-10.,-10.,-10.,-10.};
  pso::arr<N> u{10.,10.,10.,10.};
  auto p = pso::pso<N,100>(l,u,cost_fcn<N>,500,100,c,w,0.1);
  p.info();
  return 0;
}

#include <iostream>
#include "pso.hpp"
template<ull N>
std::pair<double,double>cost_fcn(arr<N> x){
  double s = 0.;
  double c = 0.;
  for (size_t i = 0; i < x.size(); i++) {
    s-=x[i]*x[i];
    c+=(x[i]>0)?x[i]:0;
  }
  return std::make_pair(s,c);
}
int main(){
  double c[2] = {0.2,0.2};
  double w[2] = {0.1,0.01};
  const ull N = 3;
  arr<N> l{-10.,-10.,-10.};
  arr<N> u{10.,10.,10.};
  auto p = pso<N>(c,w,500,l,u,100,0.1,cost_fcn<N>);
  p.info();
  return 0;
}

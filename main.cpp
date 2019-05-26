#include <iostream>
#include "pso.hpp"
std::pair<double,double>cost_fcn(vec x){
  double s = 0.;
  double c = 0.;
  for (size_t i = 0; i < x.size(); i++) {
    s-=x[i]*x[i];
    c-=x[i];
  }
  c=(c>0)?c:0;
  return std::make_pair(s,c);
}
int main(){
  double c[2]={0.2,0.2};
  double w[2]={0.1,0.01};
  vec l{-10.,-10.};
  vec u{10.,10.};
  auto p = pso(c,w,1000,l,u,100,0.1,cost_fcn);
  p.info();
  return 0;
}

#include <iostream>
#include "pso.hpp"
pair<double,double>cost_fcn(vec x){
  double s = 0.;
  double c = 0.;
  for (size_t i = 0; i < x.size(); i++) {
    s+=x[i]*x[i];
    c+=x[i];
  }
  return make_pair(s,c);
}

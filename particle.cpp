#include "particle.hpp"
#include "rand.hpp"
inline Particle::Particle (vec l,vec u,prob problem):l{l},u{u} {
  for (size_t i = 0; i < l.size(); i++) x[i]=rand::unifrnd(l[i],u[i]);
  std::fill(v.begin(),v.begin()+x.size(),0);
  [cost,infeasablity]=problem(x);
  pBest=x;
  pBest_cost=cost;
  pBest_infeasablity=infeasablity;
};
inline Particle::update(double w,double[] c,double pm,Particle gBest,prob problem){
  updateV(w,c,gBest);
  updateX();
  [cost, infeasablity] = problem(x);
  Mutate(pm,problem);
  updatePbest();
}
inline Particle::updateV(double w,double[] c,Particle gBest){
  for (size_t i = 0; i < v.size(); i++) {
    v[i]=w*v[i]+c[0]*rand()*(pBest[i]-x[i])+c[1]*rand()*(gBest.x[i]-x[i]);
  }

}
inline Particle::updateX(){
  for (size_t i = 0; i < x.size(); i++) {
    x[i]+=v[i];
    if (x[i]>u[i] || x[i]<l[i]) x[i]-=2*v[i];
  }
}
inline Particle::Mutate(double pm,prob problem){
  if (rand()>pm) return;
  int j = randin(0,x.size());
  double dx=pm*(u(j)-l(j));
  double lb=max(x[j]-dx,l[j]);
  double ub=min(x[j]+dx,u[j]);
  auto X = x;
  X[j]=unifrnd(lb,ub);//todo
  auto [c,i] = problem(X);
  if (i < infeasablity && c < cost){
    x=X;
    cost = c;
    infeasablity = i;
  }
  else if (rand()<0.5){
    x=X;
    cost = c;
    infeasablity = i;
  }
}
inline Particle::updatePBest(){
  if (infeasablity<=pBest_infeasablity && cost<=pBest_cost){
    pBest=x;
    pBest_cost=cost;
    pBest_infeasablity=infeasablity;
  }
}

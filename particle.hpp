#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
#include <functional>
#include <limits>
#include <cmath>
#include "rand.hpp"
using vec=std::vector<double>;
using prob=std::function<std::pair<double,double>(vec)>;
class Particle {
  public:
    inline Particle() = default;
    inline Particle(Particle const&) = default;
    inline Particle(Particle&&) = default;
    inline Particle& operator=(Particle const&) = default;
    inline Particle& operator=(Particle&&) = default;
    inline Particle(vec l,vec u,const prob& problem):l{l},u{u} {
      for (size_t i = 0; i < l.size(); i++) x[i]=rnd::unifrnd(l[i],u[i]);
      std::fill(v.begin(),v.begin()+x.size(),0);
      std::tie(cost,infeasablity)=problem(x);
      pBest=x;
      pBest_cost=cost;
      pBest_infeasablity=infeasablity;
    }
    inline void update(const double w,const double c[],const double pm,const Particle& gBest,const prob& problem){
      updateV(w,c,gBest);
      updateX();
      std::tie(cost,infeasablity) = problem(x);
      Mutate(pm,problem);
      updatePBest();
    }
    inline void updateV(const double w,const double c[],const Particle& gBest){
      for (size_t i = 0; i < v.size(); i++) {
        v[i]=w*v[i]+c[0]*rnd::rand()*(pBest[i]-x[i])+c[1]*rnd::rand()*(gBest.x[i]-x[i]);
      }
    }
    inline void updateX(){
      for (size_t i = 0; i < x.size(); i++) {
        x[i]+=v[i];
        if (x[i]>u[i] || x[i]<l[i]){
          v[i]*=-1;
          x[i]+=2*v[i];
        }
      }
    }
    inline void updatePBest(){
      if ((infeasablity<=pBest_infeasablity) && (cost<pBest_cost)){
        pBest=x;
        pBest_cost=cost;
        pBest_infeasablity=infeasablity;
      }
    }
    inline void Mutate(const double pm,const prob& problem){
      if (rnd::rand()>pm) return;
      int j = rnd::unifrnd((size_t)0,x.size());
      double dx=pm*(u[j]-l[j]);
      double lb=std::max(x[j]-dx,l[j]);
      double ub=std::min(x[j]+dx,u[j]);
      auto X = x;
      X[j]=rnd::unifrnd(lb,ub);
      auto [c,i] = problem(X);
      if (i < infeasablity && c < cost){
        x[j]=X[j];
        cost = c;
        infeasablity = i;
      }
      else if (rnd::rand()<0.5){
        x[j]=X[j];
        cost = c;
        infeasablity = i;
      }
    }
    inline static Particle get_gBest(const std::vector<Particle>& swarm){
      return *std::min_element(swarm.begin(),swarm.end(),
                              [](const auto& a,const auto& b){
                                return ((a.infeasablity<=b.infeasablity) && (a.cost < b.cost));
                              });
    }
  private:
    vec l;
    vec u;
    vec x;
    vec v;
    double cost;
    double infeasablity;
    vec pBest;
    double pBest_cost;
    double pBest_infeasablity;
};
#endif //PARTICLE_H

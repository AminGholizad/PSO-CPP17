#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>
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
    inline Particle(const vec& l,const vec& u,const prob& problem):l{l},u{u} {
      for (size_t i = 0; i < l.size(); i++){
        x.push_back(rnd::unifrnd(l[i],u[i]));
        v.push_back(0.);
      }
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
          if (x[i]>u[i] || x[i]<l[i]){
            do {
              x[i]-=v[i];
              v[i]*=-0.5;
              x[i]+=v[i];
            } while(x[i]>u[i] || x[i]<l[i]);
          }
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
      size_t j = rnd::unifrnd((size_t)0,x.size());
      double dx=pm*(u[j]-l[j]);
      double lb=std::max(x[j]-dx,l[j]);
      double ub=std::min(x[j]+dx,u[j]);
      auto X = x;
      X[j]=rnd::unifrnd(lb,ub);
      auto [c,i] = problem(X);
      if ((i < infeasablity && c < cost) || (rnd::rand()<0.5)){
        x[j]=X[j];
        cost = c;
        infeasablity = i;
      }
    }
    inline bool dominates(const Particle& b)const&{
      return ((infeasablity<=b.infeasablity) && (cost < b.cost));
    }
    inline static Particle get_Best(const std::vector<Particle>& swarm){
      return *std::min_element(swarm.begin(),swarm.end(),
                              [](const auto& a,const auto& b){
                                return a.dominates(b);
                              });
    }
    inline void info() const&{
      std::cout << "info:\n";
      std::cout << "cost = " << cost << '\n';
      std::cout << "infeasablity = " << infeasablity << '\n';
      std::cout << "x:(";
      for (size_t i = 0; i < x.size()-1; i++) {
        std::cout << x[i] << ", ";
      }
      std::cout << *x.end() << ")\n";
      std::cout << "v:(";
      for (size_t i = 0; i < v.size()-1; i++) {
        std::cout << v[i] << ", ";
      }
      std::cout << *v.end() << ")\n";
      std::cout << "pBest:" << '\n';
      std::cout << "cost = " << pBest_cost << '\n';
      std::cout << "infeasablity = " << pBest_infeasablity << '\n';
      std::cout << "x:(";
      for (size_t i = 0; i < x.size()-1; i++) {
        std::cout << pBest[i] << ", ";
      }
      std::cout << *pBest.end() << ")\n";
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

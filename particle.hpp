#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>
#include <array>
#include <functional>
#include <limits>
#include "rand.hpp"
namespace pso {
  using ull=unsigned long long;
  template<ull N>
  using vars=std::array<double,N>;
  template<ull N>
  using Problem=std::function<std::pair<double,double>(vars<N>)>;
  template<ull N>
  class Particle {
    public:
      inline Particle() = default;
      inline Particle(Particle const&) = default;
      inline Particle(Particle&&) = default;
      inline Particle& operator=(Particle const&) = default;
      inline Particle& operator=(Particle&&) = default;
      inline Particle(const vars<N>& l,const vars<N>& u,const Problem<N>& problem):l{l},u{u} {
        for (size_t i = 0; i < l.size(); i++){
          x[i]=rnd::unifrnd(l[i],u[i]);
          v[i]=0.;
        }
        std::tie(cost,infeasablity)=problem(x);
        pBest=x;
        pBest_cost=cost;
        pBest_infeasablity=infeasablity;
      }
      inline void update(const Particle& gBest,const Problem<N>& problem,const double w=0.5,const std::array<double,2>& c={0.2,0.2},const double pm=0.1){
        updateV(gBest,w,c);
        updateX();
        std::tie(cost,infeasablity) = problem(x);
        Mutate(problem,pm);
        updatePBest();
      }
      inline bool dominates(const Particle& b)const&{
        return ((infeasablity<=b.infeasablity) && (cost < b.cost));
      }
      template <ull S>
      inline static Particle get_Best(const std::array<Particle,S>& swarm){
        return *std::min_element(swarm.begin(),swarm.end(),
                                [](const auto& a,const auto& b){
                                  return a.dominates(b);
                                });
      }
      inline void info() const&{
        std::cout << "particle info:\n";
        std::cout << "\tcost = " << cost << '\n';
        std::cout << "\tinfeasablity = " << infeasablity << '\n';
        std::cout << "\tx=(";
        for (size_t i = 0; i < x.size()-1; i++) {
          std::cout << x[i] << ", ";
        }
        std::cout << x.back() << ")\n";
        std::cout << "\tv=(";
        for (size_t i = 0; i < v.size()-1; i++) {
          std::cout << v[i] << ", ";
        }
        std::cout << v.back() << ")\n";
        std::cout << "\tpBest:" << '\n';
        std::cout << "\t\tcost = " << pBest_cost << '\n';
        std::cout << "\t\tinfeasablity = " << pBest_infeasablity << '\n';
        std::cout << "\t\tx=(";
        for (size_t i = 0; i < x.size()-1; i++) {
          std::cout << pBest[i] << ", ";
        }
        std::cout << pBest.back() << ")\n";
      }
    private:
      inline void updateV(const Particle& gBest,const double w=0.5,const std::array<double,2>& c={0.2,0.2}){
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
      inline void Mutate(const Problem<N>& problem,const double pm=0.1){
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
      vars<N> l;
      vars<N> u;
      vars<N> x;
      vars<N> v;
      double cost;
      double infeasablity;
      vars<N> pBest;
      double pBest_cost;
      double pBest_infeasablity;
  };
} /* pso */
#endif //PARTICLE_H

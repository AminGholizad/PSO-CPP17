#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
#include <functional>
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
    inline Particle (vec l,vec u,prob& problem);
    inline void update(double w,double c[],double pm,Particle gBest,prob& problem);
    inline void updateV(double w,double c[],Particle gBest);
    inline void updateX();
    inline void updatePBest();
    inline void Mutate(double pm,prob& problem);
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

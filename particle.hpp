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
    inline Particle(vec,vec,prob&);
    inline void update(double,double[],double,Particle,prob&);
    inline void updateV(double,double[],Particle);
    inline void updateX();
    inline void updatePBest();
    inline void Mutate(double,prob&);
    inline static Particle get_gBest(const std::vector<Particle>&);
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

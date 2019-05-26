#ifndef PSO_H
#define PSO_H
#include "particle.hpp"
Particle pso(double c[],double iw[],size_t max_iter,vec lower_bound,vec upper_bound,size_t swarm_size,double mu,prob& problem);
#endif //PSO_H

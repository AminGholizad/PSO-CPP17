#include "particle.hpp"
Particle pso(double c[],double iw[],size_t max_iter,vec lower_bound,vec upper_bound,size_t swarm_size,double mu,prob& problem){
  auto w = [&](size_t it){ return ((max_iter - it) - (iw[0] - iw[1]))/max_iter + iw[1];};
  auto pm = [&](size_t it){ return pow(1-(it-1)/(max_iter-1),(1/mu));};
  std::vector<Particle> swarm;
  for (size_t i = 0; i < swarm_size; i++)
    swarm.emplace_back(lower_bound,upper_bound,problem);
  Particle gBest;
  for (size_t i = 0; i < max_iter; i++) {
    gBest = Particle::get_Best(swarm);
    auto wc = w(i);
    auto pc = pm(i);
    for (size_t j = 0; j < swarm_size; j++) {
      swarm[j].update(wc,c,pc,gBest,problem);
    }
  }

  return gBest;
}

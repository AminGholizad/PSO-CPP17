Particle pso(double c[2],double iw[2],size_t max_iter,vec lower_bound,vec upper_bound,size_t swarm_size,double mu,const prob& problem){
  auto w = [&](size_t it){ return ((max_iter - it) - (iw[0] - iw[1]))/max_iter + iw[1];};
  auto pm = [&](size_t it){ return pow(1-(it-1)/(max_iter-1),(1/mu));};
  std::vector<Particle> swarm;
  for (size_t i = 0; i < swarm_size; i++)
    swarm.emplace_back(lower_bound,upper_bound,problem);
  auto gBest = swarm[0];
  for (size_t i = 0; i < max_iter; i++) {
    if (auto tmp = Particle::get_Best(swarm); tmp.dominates(gBest))
      gBest=tmp;
    auto wc = w(i);
    auto pc = pm(i);
    for (size_t j = 0; j < swarm_size; j++) {
      swarm[j].update(wc,c,pc,gBest,problem);
    }
  }

  return gBest;
}

#ifndef PARTICLE_H
#define PARTICLE_H
using vec=std::vector<double>;
using prob=std::function<std::pair<double,double>(vec)>;
class Particle {
  public:
    inline Particle() = default;
    inline Particle(Particle const&) = default;
    inline Particle(Particle&&) = default;
    inline Particle& operator=(Particle const&) = default;
    inline Particle& operator=(Particle&&) = default;
    inline Particle (vec l,vec u,prob problem);
    inline update(double w,double[] c,double pm,Particle gBest,prob problem);
    inline updateV(double w,double[] c,Particle gBest);
    inline updateX();
    inline updatePBest();
    inline Mutate(double pm,prob problem);
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

#ifndef PARTICLE_H
#define PARTICLE_H
class Particle {
  public:
    inline Particle() = default;
    inline Particle(Particle const&) = default;
    inline Particle(Particle&&) = default;
    inline Particle& operator=(Particle const&) = default;
    inline Particle& operator=(Particle&&) = default;
    inline Particle (/*arguments*/) {/*body*/};
  private:
    std::vector<double> x;
    std::vector<double> v;
};
#endif //PARTICLE_H

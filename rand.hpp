#ifndef RAND
#define RAND
#include <random>
#include <algorithm>
namespace rnd{
  std::mt19937& Generator();
  template <typename T> T unifrnd(T,T);
  double rand();
  template<typename Iter, typename RandomGenerator>
  Iter select_randomly(Iter, Iter, RandomGenerator&);
  template<typename Iter> Iter select_randomly(Iter, Iter);
}
#endif

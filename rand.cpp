#include "rand.hpp"
#include <random>
inline std::mt19937& rand::Generator(){
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return gen;
}
template <typename T>
inline T rand::unifrnd(T a,T b){
  if constexpr(std::is_integral_v<T>){
    std::uniform_int_distribution<T> dis(a, b);
    return dis(Generator());
  }
  else {
    std::uniform_real_distribution<T> dis(a, b);
    return dis(Generator());
  }
}
inline double rand::rand(){
  return unifrand(0.,1.);
}
template<typename Iter, typename RandomGenerator>
inline Iter rand::select_randomly(Iter start, Iter end, RandomGenerator& g=Generator()){
    std::uniform_int_distribution<int> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

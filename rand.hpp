#ifndef RAND
#define RAND
#include <random>
#include <algorithm>
namespace rnd{
  inline std::mt19937& Generator(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
  }
  template <typename T>
  inline T unifrnd(T a,T b){
    if constexpr(std::is_integral_v<T>){
      std::uniform_int_distribution<T> dis(a, b);
      return dis(Generator());
    }
    else {
      std::uniform_real_distribution<T> dis(a, b);
      return dis(Generator());
    }
  }
  inline double rand(){
    return unifrnd(0.,1.);
  }
}
#endif

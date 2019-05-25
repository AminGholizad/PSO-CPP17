#include "rand.hpp"
inline std::mt19937& rnd::Generator(){
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return gen;
}
template <typename T> inline T Rand::unifrnd(T a,T b){
  if constexpr(std::is_integral_v<T>){
    std::uniform_int_distribution<T> dis(a, b);
    return dis(Generator());
  }
  else {
    std::uniform_real_distribution<T> dis(a, b);
    return dis(Generator());
  }
}
inline double rnd::rand(){
  return unifrnd(0.,1.);
}
template<typename Iter, typename RandomGenerator>
inline Iter rnd::select_randomly(Iter start, Iter end, RandomGenerator& g){
    std::uniform_int_distribution<int> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}
template<typename Iter>
inline Iter rnd::select_randomly(Iter start, Iter end){
  return Rand::select_randomly(start,end,Generator());
}

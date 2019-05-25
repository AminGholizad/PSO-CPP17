#ifndef RAND
#define RAND
namespace rand{
std::mt19937& Generator();
template <typename T> T unifrand(T,T);
double rand();
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter, Iter, RandomGenerator&)
}
#endif

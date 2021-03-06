#ifndef PYTHONIC_MODULE_RANDOM_H
#define PYTHONIC_MODULE_RANDOM_H
#include <cstdlib>
#include <random>

namespace pythonic {
    namespace random {

        // Random generator, use Mersenne Twister to keep consistent with Python
        static std::mt19937 __random_generator;

        none_type seed(long s) { __random_generator.seed(s); return None; }
        none_type seed() { __random_generator.seed(time(nullptr)); return None; }

        double random() {
          static std::uniform_real_distribution<> uniform_distrib(0.0, 1.0);
          return uniform_distrib(__random_generator);
        }

        double gauss(double mu, double sigma) {
            return std::normal_distribution<>(mu, sigma)(__random_generator);
        }

        double uniform(double a, double b) {
            return a + (b-a)*random();
        }

        double expovariate(double l) {
            return std::exponential_distribution<>(l)(__random_generator);
        }

        long randrange(long stop) {
            return long(random() * stop);
        }
        long randrange(long start, long stop) {
            return start + long(random() * (stop - start));
        }
        long randrange(long start, long stop, long step) {
            return start + step * long((random() * (stop - start)) / std::abs(step));
        }
        PROXY(pythonic::random, randrange)

        template<class Iterable>
            core::list<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::iterator::value_type>
            sample(Iterable&& s, size_t k) {
                typedef typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::iterator::value_type value_type;
                core::list<value_type> tmp(s);
                std::vector<size_t> indices(tmp.size());
                std::iota(indices.begin(), indices.end(), 0);
                std::random_shuffle(indices.begin(), indices.end());
                core::list<value_type> out(k);
                for(size_t i=0; i<k; i++)
                    out[i] = tmp[ indices[i] ];
                return out;
            }

        PROXY(pythonic::random, seed);
        PROXY(pythonic::random, random);
        PROXY(pythonic::random, gauss);
        PROXY(pythonic::random, uniform);
        PROXY(pythonic::random, expovariate);
        PROXY(pythonic::random, sample);
    }
}

#endif

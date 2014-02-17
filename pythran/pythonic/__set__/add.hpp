#ifndef PYTHONIC_SET_ADD_HPP
#define PYTHONIC_SET_ADD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {

        template<class T, class F>
            void add(types::set<T> &s, F const& value) {
                s.add(value);
            }
        template<class T, class F>
            void add(types::set<T> &&s, F const& value) {
                // nothing have to be done as we work on rvalue
            }
        template<class F>
            void add(types::empty_set const&s, F const& value) {
                //nothing otherwise it should be a real set with nothing into
                // instead of an empty set
            }
        PROXY(pythonic::__set__, add);

    }

}

#endif


#ifndef __PLACID_FREE_MONOID_HOMOMORPHISM__
#define __PLACID_FREE_MONOID_HOMOMORPHISM__

#include "magma_element.hpp"
#include "free_monoid_element.hpp"
#include "tuple.hpp"

namespace __placid
{
  namespace free_monoid
  {
    template <typename T>
    struct homomorphism
    {
      // the element with index 0 corresponds to the identity for type T.
      T *    mapping;
      symbol rank;

      homomorphism (const T *elems, const symbol rank)
      {
        this->rank    = rank;
        this->mapping = new T[this->rank];
        for (symbol s = 0; s < rank; s++)
        {
          this->mapping[s] = elems[s];
        }
      }

      homomorphism (const tuple<T> &homomorphism_)
        : homomorphism (homomorphism_.elements, homomorphism_.arity)
      {
      }

      T
      get_val (const element &e) const
      {
        if (e.get_size () == 0)
        {
          return mapping[0];
        }

        T res = this->mapping[e.word[0].sym];

        for (size_t j = 1; j < e.word[0].count; j++)
        {
          res = res * this->mapping[e.word[0].sym];
        }

        for (size_t i = 1; i < e.length; i++)
        {
          for (size_t j = 0; j < e.word[i].count; j++)
          {
            res = res * this->mapping[e.word[i].sym];
          }
        }

        return res;
      }
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_HOMOMORPHISM__

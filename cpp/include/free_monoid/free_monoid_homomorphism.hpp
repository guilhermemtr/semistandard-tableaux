#ifndef __PLACID_FREE_MONOID_HOMOMORPHISM__
#define __PLACID_FREE_MONOID_HOMOMORPHISM__

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
      size_t length;

      homomorphism (const T *elems, const symbol rank)
      {
        assert (elems != NULL);

        this->length  = rank + 1;
        this->mapping = new T[this->length];
        for (symbol s = 0; s < this->length; s++)
        {
          this->mapping[s] = elems[s];
        }
      }

      homomorphism (const tuple<T> &tup)
        : homomorphism (tup.elements, tup.arity - 1)
      {
      }

      homomorphism (const homomorphism<T> &h)
        : homomorphism (h.mapping, h.length - 1)
      {
      }

      symbol
      max_rank () const
      {
        return this->length - 1;
      }

      T
      map (const element &e) const
      {
        if (e.get_size () == 0)
        {
          return mapping[0];
        }

        for (size_t i = 0; i < e.length; i++)
        {
          if (e.word[i].sym > this->max_rank ())
          {
            throw std::string ("word with invalid rank");
          }
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
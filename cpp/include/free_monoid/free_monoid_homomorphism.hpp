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
        this->length  = rank + 1;
        this->mapping = new T[this->rank];
        for (symbol s = 0; s < this->length; s++)
        {
          this->mapping[s] = elems[s];
        }
      }

      homomorphism (const tuple<T> &homomorphism_)
        : homomorphism (homomorphism_.elements, homomorphism_.arity)
      {
      }

      symbol
      max_rank() const
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
          if (e.word[i].sym > this->max_rank())
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

    /*    template <typename T>
    check_homomorphism_injectivity (homomorphism &h, pool<B> &o)
    {
      pool<T> =
      for (size_t i = 0; i < o.counter; i++)
      {
        this->add (h.map (o.elements[i]));
      }
      }*/


  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_HOMOMORPHISM__

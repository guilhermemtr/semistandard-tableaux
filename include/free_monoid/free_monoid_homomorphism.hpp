#ifndef __PLACID_FREE_MONOID_HOMOMORPHISM__
#define __PLACID_FREE_MONOID_HOMOMORPHISM__

#include "free_monoid_element.hpp"
#include "tuple.hpp"

namespace __placid
{
  namespace free_monoid
  {
    /**
     * This class defines a homomorphism from an alphabet of a free monoid to a
     * template type T. This class defines a homomorphism from an alphabet of a
     * free monoid to a template type T.
     */
    template <typename T>
    struct homomorphism
    {
      // the element with index 0 corresponds to the identity for type T.
      T *    mapping;    // !< the homomorphism.
      size_t length;     // !< the size of the alphabet.

      /** Creates an homomorphism given the map of the homomorphism and the rank
       * of the free group elements. Creates an homomorphism given the map of
       * the homomorphism and the rank of the free group elements.
       * @param [in] elems - the map.
       * @param [in] rank - the rank of the free group elements.
       */
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

      /** Creates an homomorphism given a tuple corresponding to the map of the
       * homomorphism and the rank of the free group elements. Creates an
       * homomorphism given a tuple corresponding to the map of the homomorphism
       * and the rank of the free group elements.
       * @param [in] tup - the map.
       */
      homomorphism (const tuple<T> &tup)
        : homomorphism (tup.elements, tup.arity - 1)
      {
      }

      /** Creates an homomorphism given a homomorphism.
       * Creates an homomorphism given a homomorphism.
       * @param [in] h - the homomorphism.
       */

      homomorphism (const homomorphism<T> &h)
        : homomorphism (h.mapping, h.length - 1)
      {
      }

      /** Gets the max rank of the free monoid.
       * Gets the max rank of the free monoid.
       * @return the max rank of the free monoid.
       */
      virtual symbol
      max_rank () const
      {
        return this->length - 1;
      }

      /** Gets the mapping from a word to the element mapped by the homomorphism.
       * Gets the mapping from a word to the element mapped by the homomorphism.
       * @param [in] e - the word to be mapped.
       * @return the mapped element.
       */
      virtual T
      operator() (const element &e) const
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

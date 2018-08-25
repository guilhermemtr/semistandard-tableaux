#ifndef __PLACID_FREE_MONOID_KNUTH_HOMOMORPHISM__
#define __PLACID_FREE_MONOID_KNUTH_HOMOMORPHISM__

#include "free_monoid_homomorphism.hpp"
#include "free_monoid_element.hpp"
#include "tuple.hpp"

namespace __placid
{
  namespace free_monoid
  {
    /**
     * This class is used to test if an homomorphism satisfies the Knuth
     * relations. This class is used to test if an homomorphism satisfies the
     * Knuth relations.
     */
    template <typename T>
    struct knuth_homomorphism : public homomorphism<T>
    {
      /** Creates a new Knuth homomorphism given the elements and the rank.
       * Creates a new Knuth homomorphism given the elements and the rank.
       * @param [in] elems - the map.
       * @param [in] rank - the rank of the free group elements.
       */
      knuth_homomorphism (const T *elems, const symbol rank)
        : homomorphism<T> (elems, rank)
      {
      }

      /** Creates a Knuth homomorphism given a tuple corresponding to the map of
       * the homomorphism and the rank of the free group elements. Creates a
       * Knuth homomorphism given a tuple corresponding to the map of the
       * homomorphism and the rank of the free group elements.
       * @param [in] homomorphism_ - the map.
       */
      knuth_homomorphism (const tuple<T> &homomorphism_)
        : homomorphism<T> (homomorphism_)
      {
      }

      /** Checks if both Knuth relations are satisfied.
       * Checks if both Knuth relations are satisfied.
       * @return whether the Knuth relations are satisfied.
       */
      bool
      knuth_relations_satisfied ()
      {
        return this->yzx_yxz_satisfied () && this->xzy_zxy_satisfied ();
      }

        private:
      /** Checks if the first Knuth relation is satisfied.
       * Checks if the first Knuth relation is satisfied.
       * @return whether the first Knuth relations is satisfied.
       */
      bool
      yzx_yxz_satisfied ()
      {
        for (symbol x = 1; x <= this->max_rank (); x++)
        {
          for (symbol y = x + 1; y <= this->max_rank (); y++)
          {
            for (symbol z = y; z <= this->max_rank (); z++)
            {
              T res_left =
                this->mapping[y] * this->mapping[z] * this->mapping[x];
              T res_right =
                this->mapping[y] * this->mapping[x] * this->mapping[z];
              if (res_left != res_right)
              {
                return false;
              }
            }
          }
        }

        return true;
      }

      /** Checks if the second Knuth relation is satisfied.
       * Checks if the second Knuth relation is satisfied.
       * @return whether the second Knuth relations is satisfied.
       */
      bool
      xzy_zxy_satisfied ()
      {
        for (symbol x = 1; x <= this->max_rank (); x++)
        {
          for (symbol y = x; y <= this->max_rank (); y++)
          {
            for (symbol z = y + 1; z <= this->max_rank (); z++)
            {
              T res_left =
                this->mapping[x] * this->mapping[z] * this->mapping[y];
              T res_right =
                this->mapping[z] * this->mapping[x] * this->mapping[y];
              if (res_left != res_right)
              {
                return false;
              }
            }
          }
        }

        return true;
      }
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_KNUTH_HOMOMORPHISM__

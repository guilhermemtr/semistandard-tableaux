#ifndef __PLACID_FREE_MONOID_KNUTH_HOMOMORPHISM__
#define __PLACID_FREE_MONOID_KNUTH_HOMOMORPHISM__

#include "free_monoid_element.hpp"
#include "tuple.hpp"

namespace __placid
{
  namespace free_monoid
  {
    template <typename T>
    struct knuth_homomorphism : public homomorphism<T>
    {
      knuth_homomorphism (const T *elems, const symbol rank)
        : homorphism (elems, rank)
      {
      }

      knuth_homomorphism (const tuple<T> &homomorphism_)
        : homomorphism (homomorphism_)
      {
      }

      bool
      knuth_relations_satisfied ()
      {
        return this->yzx_yxz_satisfied () && this->xzy_zxy_satisfied ();
      }

        private:
      bool
      yzx_yxz_satisfied ()
      {
        for (symbol x = 1; x < this->max_rank (); x++)
        {
          for (symbol y = x + 1; y < this->max_rank (); y++)
          {
            for (symbol z = y; z < this->max_rank (); z++)
            {
              T res_left  = mapping[y] * mapping[z] * mapping[x];
              T res_right = mapping[y] * mapping[x] * mapping[z];
              if (res_left != res_right)
              {
                return false;
              }
            }
          }
        }

        return true;
      }

      bool
      xzy_zxy_satisfied ()
      {
        for (symbol x = 1; x < this->max_rank (); x++)
        {
          for (symbol y = x; y < this->max_rank (); y++)
          {
            for (symbol z = y + 1; z < this->max_rank (); z++)
            {
              T res_left  = mapping[x] * mapping[z] * mapping[y];
              T res_right = mapping[z] * mapping[x] * mapping[y];
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

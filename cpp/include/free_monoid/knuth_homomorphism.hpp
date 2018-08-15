#ifndef __PLACID_FREE_MONOID_KNUTH_HOMOMORPHISM__
#define __PLACID_FREE_MONOID_KNUTH_HOMOMORPHISM__

#include "free_monoid_homomorphism.hpp"
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
        : homomorphism<T> (elems, rank)
      {
      }

      knuth_homomorphism (const tuple<T> &homomorphism_)
        : homomorphism<T> (homomorphism_)
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
              T res_left  = this->mapping[y] * this->mapping[z] * this->mapping[x];
              T res_right = this->mapping[y] * this->mapping[x] * this->mapping[z];
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
              T res_left  = this->mapping[x] * this->mapping[z] * this->mapping[y];
              T res_right = this->mapping[z] * this->mapping[x] * this->mapping[y];
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

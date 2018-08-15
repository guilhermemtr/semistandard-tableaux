#ifndef __PLACID_FACTOR_MONOID_ELEMENT_POOL__
#define __PLACID_FACTOR_MONOID_ELEMENT_POOL__


#include "magma_element.hpp"
#include "free_monoid/free_monoid_element.hpp"
#include "free_monoid/free_monoid_homomorphism.hpp"

namespace __placid
{
  namespace free_monoid
  {
    template <typename T>
    struct factor_element_pool
    {
      static const size_t default_size = (1 << 5);

      factor_element_pool (size_t size = default_size) : pool (size)
      {
      }

      factor_element_pool (factor_element_pool &o) : pool (o)
      {
      }

      ~factor_element_pool ()
      {
      }

      template <typename V>
      pool<V>
      get_homomorphic_image (free_monoid::homomorphism<V> h) const
      {
        pool<V> homomorphic_image;
        for (size_t i = 0; i < this->counter; i++)
        {
          homomorphic_image.add (h.map (this->elements[i].reading ()));
        }
        return homomorphic_image;
      }

      template <typename V>
      bool
      test_homomorphism_injectivity (free_monoid::homomorphism<V> h)
      {
        // the type of the elements of this pool MUST BE a subtype of
        // factor_monoid_element
        factor_element_pool<T> p = *this;
        p.remove_duplicates ();

        pool<V> homomorphic_image = this->get_homomorphic_image (h);
        homomorphic_image.remove_duplicates ();

        return homomorphic_image.counter == p.counter;
      }
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FACTOR_MONOID_ELEMENT_POOL__
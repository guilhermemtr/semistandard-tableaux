#ifndef __PLACID_FACTOR_MONOID_ELEMENT_POOL__
#define __PLACID_FACTOR_MONOID_ELEMENT_POOL__


#include "magma_element.hpp"
#include "free_monoid/free_monoid_element.hpp"

#include "magma_element_pool.hpp"

#include "free_monoid/free_monoid_homomorphism.hpp"

namespace __placid
{
  namespace free_monoid
  {
    /**
     * This class defines a pool of semigroup elements.
     * This class defines a pool of semigroup elements.
     */
    template <typename T>
    struct factor_element_pool : public pool<T>
    {
      static const size_t default_size =
        (1 << 5);    // !< the default size of the pool.

      /** Creates a new pool given a size.
       * Creates a new pool given a size.
       * @param [in] size - the size of the pool to be created.
       */
      factor_element_pool (size_t size = default_size) : pool<T> (size)
      {
      }

      /** Creates a new pool given another pool.
       * Creates a new pool given another pool.
       * @param [in] o - the other pool.
       */
      factor_element_pool (factor_element_pool<T> &o) : pool<T> (o)
      {
      }

      /** Destroys the pool.
       * Destroys the pool.
       */
      ~factor_element_pool ()
      {
      }

      /** Applies a homomorphism to the pool, creating a new one with the mapped
       * elements. Applies a homomorphism to the pool, creating a new one with
       * the mapped elements.
       * @param [in] h - the homomorphism.
       * @return the pool created with the mapped elements.
       */
      template <typename V>
      __placid::pool<V> &
      operator() (free_monoid::homomorphism<V> h) const
      {
        pool<V> *homomorphic_image = new pool<V> ();
        for (size_t i = 0; i < this->counter; i++)
        {
          homomorphic_image->add (h (this->elements[i].reading ()));
        }
        return *homomorphic_image;
      }

      /** Checks if the given homomorphism is injective.
       * Checks if the given homomorphism is injective, by mapping all elements
       * of the pool to a new pool and checking for repetitions.
       * @param [in] h - the homomorphism to be tested.
       * @return whether the homomorphism passed the test.
       */
      template <typename V>
      bool
      injective (free_monoid::homomorphism<V> h)
      {
        // the type of the elements of this pool MUST BE a subtype of
        // factor_monoid_element
        factor_element_pool<T> p = *this;
        p.remove_duplicates ();

        pool<V> homomorphic_image = this->operator() (h);
        homomorphic_image.remove_duplicates ();

        return homomorphic_image.counter == p.counter;
      }
    };

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FACTOR_MONOID_ELEMENT_POOL__

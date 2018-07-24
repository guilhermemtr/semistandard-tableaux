#ifndef __PLACID_FREE_MONOID__
#define __PLACID_FREE_MONOID__

#include <string>

#include "magma_element.hpp"

namespace __placid
{
  template <typename T>
  struct free_monoid : public magma_element<free_monoid<T>>
  {
    static const size_t default_size = (1 << 5);

    static const file_format plain_format      = 0;
    static const file_format compressed_format = 1;

    size_t length;
    T *    elements;

    /** Constructs a new free monoid.
     * Constructs a new free monoid.
     */
    free_monoid ()
    {
      this->length = default_size;
      this->elements = new T[this->length];
    }

    /** Constructs a new free monoid, from a given free monoid.
     * Constructs a new free monoid.
     */
    free_monoid ()
    {
      this->length = default_size;
      this->elements = new T[this->length];
    }

    /** Destroys a free monoid.
     * Destroys a free monoid.
     */
    virtual ~free_monoid ();

    free_monoid
    operator= (free_monoid o);

    bool
    operator== (free_monoid o);

    free_monoid operator* (free_monoid o);

    void
    read (FILE *f);

    void
    write (FILE *f, file_format format);
  };

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID__

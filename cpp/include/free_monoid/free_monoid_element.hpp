#ifndef __PLACID_FREE_MONOID__
#define __PLACID_FREE_MONOID__

#include <string>

#include "magma_element.hpp"

namespace __placid
{
  typedef uint64_t symbol;

  struct free_monoid_element : public magma_element<free_monoid_element>
  {
    static const size_t default_size = (1 << 5);

    static const file_format plain_format      = 0;
    static const file_format compressed_format = 1;

    size_t  length;
    symbol *elements;

    /** Constructs a new free monoid element.
     * Constructs a new free monoid element.
     */
    free_monoid_element (size_t len = default_size)
    {
      this->length   = default_size;
      this->elements = new symbol[this->length];
    }

    /** Constructs a new free monoid element, from a given free monoid element.
     * Constructs a new free monoid element, from a given free monoid element.
     * @param o the free monoid element.
     */
    free_monoid_element (free_monoid_element &o)
      : free_monoid_element (o.length)
    {
      for (size_t i = 0; i < this->length; i++)
      {
        this->elements[i] = o.elements[i];
      }
    }

    /** Destroys a free monoid.
     * Destroys a free monoid.
     */
    ~free_monoid_element ()
    {
      delete[] this->elements;
    }

    free_monoid_element
    operator= (free_monoid_element o)
    {
      delete[] this->elements;

      this->length   = o.length;
      this->elements = new symbol[this->length];
      for (size_t i = 0; i < this->length; i++)
      {
        this->elements[i] = o.elements[i];
      }
      return *this;
    }

    bool
    operator== (free_monoid_element o)
    {
      if (this->length != o.length)
      {
        return false;
      }

      bool equals = true;
      for (size_t i = 0; i < this->length; i++)
      {
        if (this->elements[i] != o.elements[i])
        {
          equals = false;
          break;
        }
      }

      return equals;
    }

    bool
    operator!= (free_monoid_element o)
    {
      return !(*this == o);
    }

    free_monoid_element operator* (free_monoid_element o)
    {
      free_monoid_element e (this->length + o.length);
      for (size_t i = 0; i < this->length; i++)
      {
        e.elements[i] = o.elements[i];
      }

      for (size_t i = 0; i < o.length; i++)
      {
        e.elements[i + this->length] = o.elements[i];
      }

      return e;
    }

    void
    read (FILE *f)
    {
    }

    void
    write (FILE *f, file_format format)
    {
    }
  };

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID__

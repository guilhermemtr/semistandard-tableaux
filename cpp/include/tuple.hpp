#ifndef __PLACID_TUPLE__
#define __PLACID_TUPLE__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>
#include <cctype>

#include "magma_element.hpp"

namespace __placid
{
  extern const std::string incompatible_tuple_arities_exception;

  template <typename T>
  struct tuple : public magma_element<tuple<T>>
  {
    size_t arity;
    T *    elements;

    /** Constructs a new tuple with the given arity.
     * Constructs a new tuple with the given arity.
     * @param arity the arity of the tuple.
     * @param elements the elements of the tuple.
     */
    tuple (size_t arity, T *elements)
    {
      this->arity    = arity;
      this->elements = new T[this->arity];
      for (size_t i = 0; i < this->arity; i++)
      {
        this->elements[i] = elements[i];
      }
    }

    /** Constructs a new tuple, from another tuple.
     * Constructs a new tuple, from another tuple.
     * @param tuple the tuple to be copied.
     */
    tuple (tuple<T> &tup) : tuple (tup.arity, tup.elements)
    {
    }

    /** Destroys a tuple.
     * Destroys a tuple.
     */
    virtual ~tuple ()
    {
      delete[] this->elements;
    }

    tuple<T>
    operator= (tuple<T> o)
    {
      if (this->arity != o.arity)
      {
        delete[] this->elements;
        this->arity    = o.arity;
        this->elements = new T[this->arity];
      }

      for (size_t i = 0; i < this->arity; i++)
      {
        this->elements[i] = o.elements[i];
      }

      return *this;
    }

    bool
    operator== (tuple<T> o)
    {
      if (this->arity != o.arity)
      {
        return false;
      }

      for (size_t i = 0; i < this->arity; i++)
      {
        if (this->elements[i] != o.elements[i])
        {
          return false;
        }
      }
      return true;
    }

    tuple<T> operator* (tuple<T> o)
    {
      if (this->arity != o.arity)
      {
        throw incompatible_tuple_arities_exception;
      }

      T *elements = new T[this->arity];

      for (size_t i = 0; i < this->arity; i++)
      {
        elements[i] = this->elements[i] * o.elements[i];
      }

      tuple<T> res (this->arity, elements);

      delete[] elements;

      return res;
    }

    void
    read (FILE *f)
    {
    }

    void
    read (std::string fn)
    {
    }

    void
    write (FILE *f, file_format format)
    {
    }

    void
    write (std::string fn, file_format format)
    {
    }
  };

}    // namespace __placid

#endif    // __PLACID_TUPLE__

#include "tuple.hpp"

#ifdef __PLACID_TUPLE__

namespace __placid
{
  const std::string incompatible_tuple_arities_exception =
    std::string ("Different tuple arities");

  tuple::tuple (size_t arity, T *elements)
  {
    this->arity    = arity;
    this->elements = new T[this->arity];
    for (size_t i = 0; i < this->arity; i++)
    {
      this->elements[i] = elements[i];
    }
  }

  tuple::tuple (tuple &tup) : tuple (tup.arity, tup.elements)
  {
  }

  tuple::~tuple ()
  {
    delete[] this->elements;
  }

  tuple
  tuple::operator= (tuple o)
  {
    if (this->arity != o.arity)
    {
      delete[] this->elements;
      this->elements = new tuple[this->arity];
    }

    this->arity = o.arity;

    for (size_t i = 0; i < this->arity; i++)
    {
      this->elements[i] = o.elements[i];
    }

    return *this;
  }

  bool
  tuple::operator== (tuple o)
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

  tuple tuple::operator* (tuple o)
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

    tuple res (this->arity, elements);

    delete[] elements;

    return res;
  }

  void
  tuple::read (FILE *f)
  {
  }

  void
  tropical_matrix::write (FILE *f)
  {
  }

}    // namespace __placid

#endif    // __PLACID_TUPLE__

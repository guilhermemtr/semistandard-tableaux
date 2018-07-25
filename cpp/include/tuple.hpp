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
  extern const std::string tuple_format_id;
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
    tuple (const tuple<T> &tup) : tuple (tup.arity, tup.elements)
    {
    }

    /** Destroys a tuple.
     * Destroys a tuple.
     */
    virtual ~tuple ()
    {
      delete[] this->elements;
    }

    tuple<T> &
    operator= (const tuple<T> &o)
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
    operator== (const tuple<T> &o) const
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

    tuple<T> operator* (const tuple<T> &o) const
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
      char format_id[256];
      if (fscanf (f, "%s", format_id) != 1)
      {
        throw invalid_file_format_exception;
      }

      if (strcmp (format_id, tuple_format_id.c_str ()) != 0)
      {
        throw invalid_file_format_exception;
      }

      size_t arity;

      if (fscanf (f, "%lu", &arity) != 1)
      {
        throw invalid_file_format_exception;
      }

      delete[] this->elements;
      this->arity = arity;

      this->elements = new T[this->arity];

      discard_line (f);
      read_data (f);
    }

    void
    write (FILE *f, file_format format)
    {
      if (f == NULL)
      {
        return;
      }

      fprintf (f, "%s\n", tuple_format_id.c_str ());

      fprintf (f, "%lu\n", this->arity);

      this->write_data (f, format);
    }

      private:
    void
    discard_line (FILE *f, size_t to_discard = 1)
    {
      char * tmp = NULL;
      size_t len = 0;
      for (size_t i = 0; i < to_discard; i++)
      {
        getline (&tmp, &len, f);
        free (tmp);
        tmp = NULL;
      }
    }

    void
    read_data (FILE *f)
    {
      for (size_t i = 1; i < this->arity; i++)
      {
        this->elements[i - 1].read (f);
        discard_line (f, 2);
      }
      this->elements[this->arity - 1].read (f);
    }

    void
    write_data (FILE *f, file_format format)
    {
      for (size_t i = 1; i < this->arity; i++)
      {
        elements[i - 1].write (f, format);
        fprintf (f, "\n,\n");
      }
      elements[this->arity - 1].write (f, format);
    }
  };

}    // namespace __placid

#endif    // __PLACID_TUPLE__

#ifndef __PLACID_TUPLE__
#define __PLACID_TUPLE__

#include <string>

#include <cstdint>
#include <cassert>
#include <cstring>
#include <cctype>

#include "magma_element.hpp"
#include "utils.hpp"

namespace __placid
{
  extern const std::string
    tuple_format_id;    // !< a constant defining the format of a tuple.
  extern const std::string
    incompatible_tuple_arities_exception;    // !< a constant defining an object
                                             // thrown when the arities of two
                                             // tuples being multiplied are
                                             // different.

  /**
   * This class defines a tuple element.
   * This class defines a tuple element.
   */
  template <typename T>
  struct tuple : public magma_element<tuple<T>>
  {
    size_t arity;       // !< the arity of the tuple
    T *    elements;    // !< the elements of the tuple

    /** Constructs a new tuple with the given arity.
     * Constructs a new tuple with the given arity.
     * @param [in] arity the arity of the tuple.
     * @param [in] elements the elements of the tuple.
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

    /** Constructs a new tuple with 0-arity.
     * Constructs a new tuple with 0-arity.
     */
    tuple ()
    {
      this->arity    = 0;
      this->elements = new T[this->arity];
    }

    /** Constructs a new tuple from another tuple.
     * Constructs a new tuple from another tuple.
     * @param [in] tuple the tuple to be copied.
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

    /** Returns a reference to the idx-th element of the tuple.
     * Returns a reference to the idx-th element of the tuple.
     * @param [in] idx the index of the element to be projected.
     * @return the reference to the projected element.
     */
    T &operator[] (size_t idx)
    {
      return this->elements[idx];
    }

    /** Returns the projection of the idx-th element of the tuple.
     * Returns the projection of the idx-th element of the tuple.
     * @param [in] idx the index of the element to be projected.
     * @return the projection.
     */
    const T &operator[] (size_t idx) const
    {
      return this->elements[idx];
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
      // The multiplication of tuples is the direct product
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
    write (FILE *f, file_format format) const
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
    /** Reads the tuple's elements from a file stream.
     * Reads the tuple's elements from a file stream.
     * @param [in] f - the file stream.
     */
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

    /** Writes the tuple's elements to a file stream.
     * Writes the tuple's elements to a file stream.
     * @param [in] f - the file stream.
     * @param [in] format - the file format to be used.
     */
    void
    write_data (FILE *f, file_format format) const
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

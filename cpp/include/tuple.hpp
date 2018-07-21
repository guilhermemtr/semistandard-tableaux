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
  struct tuple : public magma_element<tuple>
  {
    size_t arity;
    T *    elements;

    /** Constructs a new tuple with the given arity.
     * Constructs a new tuple with the given arity.
     * @param arity the arity of the tuple.
     * @param elements the elements of the tuple.
     */
    tuple (size_t arity, T *elements);

    /** Constructs a new tuple, from another tuple.
     * Constructs a new tuple, from another tuple.
     * @param tuple the tuple to be copied.
     */
    tuple (tuple &tup);

    /** Destroys a tuple.
     * Destroys a tuple.
     */
    virtual ~tuple ();

    tuple
    operator= (tuple o);

    bool
    operator== (tuple o);

    tuple operator* (tuple o);

    void
    read (FILE *f);

    void
    write (FILE *f);
  };

}    // namespace __placid

#endif    // __PLACID_TUPLE__

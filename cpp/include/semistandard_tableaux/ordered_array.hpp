#ifndef __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__
#define __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

#include "tableaux_entry.hpp"

namespace __placid
{
  struct tableaux_ordered_array
  {
    static const size_t default_size = (1 << 5);

    size_t size;       //!< true size of the ordered array.
    size_t counter;    //!< number of positions of the array used.
    //!< invariant: counter <= size.
    tableaux_cell *cells;    //!< array.

    tableaux_ordered_array (size_t size = default_size);

    tableaux_ordered_array (tableaux_ordered_array& o);

    virtual ~tableaux_ordered_array ();

    tableaux_ordered_array
    operator= (tableaux_ordered_array o);

    size_t
    get_size ();

    /*    void
    add (tableaux_cell *to_place,
         size_t         real_nr_to_place,
         tableaux_cell *replaced,
         size_t *       real_nr_replaced);*/

      private:
    
    void
    resize ();

    
  };
}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

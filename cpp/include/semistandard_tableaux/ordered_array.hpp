#ifndef __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__
#define __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

#include "tableaux_entry.hpp"

namespace __placid
{
  namespace semistandard_tableaux
  {
    struct ordered_array
    {
      static const size_t default_size = (1 << 5);

      size_t size;       //!< true size of the ordered array.
      size_t counter;    //!< number of positions of the array used.
      //!< invariant: counter <= size.
      entry *cells;    //!< array.

      ordered_array (size_t size = default_size);

      ordered_array (ordered_array &o);

      virtual ~ordered_array ();

      ordered_array
      operator= (ordered_array o);

      bool
      operator== (ordered_array o);

      bool
      operator!= (ordered_array o);

      size_t
      get_size ();

      void
      add (entry * to_place,
           size_t  real_nr_to_place,
           entry * replaced,
           size_t *real_nr_replaced);

      void
      write (FILE *f);

        private:
      void
      resize ();

      void
      compress ();

      size_t
      get_mid (entry_val val);

      void
      place_cell_mid (size_t *idx, entry to_place);

      void
      shift_cells_after_mid (size_t *  idx,
                             entry_len extra,
                             entry *   replaced,
                             size_t *  pos);

      void
      place_cell (entry to_place, entry *replaced, size_t *pos);
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

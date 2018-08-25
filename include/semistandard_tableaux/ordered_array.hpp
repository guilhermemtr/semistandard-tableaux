#ifndef __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__
#define __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

#include "tableaux_entry.hpp"

#include "config.hpp"

namespace __placid
{
  namespace semistandard_tableaux
  {
    /**
     * This class defines a row of a semistandard tableaux.
     * This class defines a row of a semistandard tableaux.
     */
    struct ordered_array
    {
      static const size_t default_size =
        (1 << 5);    // !< the default size of the ordered array.

      size_t size;       //!< true size of the ordered array.
      size_t counter;    //!< number of positions of the array used.
      //!< invariant: counter <= size.
      entry *cells;    //!< array.

      /** Creates a new row with the given size.
       * Creates a new row with the given size.
       * @param [in] size - the size of the row to be created.
       */
      ordered_array (size_t size = default_size);

      /** Creates a new row given another row.
       * Creates a new row given another row.
       * @param [in] o - the other row.
       */
      ordered_array (const ordered_array &o);

      /** Destroys a row.
       * Destroys a row.
       */
      virtual ~ordered_array ();

      /** Assigns the row new values.
       * Assigns the row new values.
       * @param [in] o - the new values.
       * @return the row with the new values.
       */
      ordered_array &
      operator= (const ordered_array &o);

      /** Checks if two rows are equal.
       * Checks if two rows are equal.
       * @param [in] o - the second row.
       * @return if the two rows are equal.
       */
      bool
      operator== (const ordered_array &o) const;

      /** Checks if two rows are different.
       * Checks if two rows are different.
       * @param [in] o - the second row.
       * @return if the two rows are different.
       */
      bool
      operator!= (const ordered_array &o) const;

      /** Gets the size of the row.
       * Gets the size of the row.
       * @return the size of the row.
       */
      size_t
      get_size () const;

      /** Adds cells to the row, or replaces them if that is not possible.
       * Adds cells to the row, or replaces them if that is not possible.
       * @param [in] to_place - the vector of cells to be added.
       * @param [in] real_nr_to_place - the total number of cells that will be placed.
       * @param [out] replaced - the cells that were replaced.
       * @param [out] real_nr_replaced - the number of cells that were replaced.
       */
      void
      add (entry * to_place,
           size_t  real_nr_to_place,
           entry * replaced,
           size_t *real_nr_replaced);

        private:
      /** Copies another row into this one.
       * Copies another row into this one.
       * @param [in] o - the other row.
       */
      void
      copy (const ordered_array &o);

      /** Resizes the row.
       * Resizes the row.
       */
      void
      resize ();

      /** Compresses the row.
       * Compresses the row.
       */
      void
      compress ();

      /** Gets the index of the row where an entry with the given value could be placed.
       * Gets the index of the row where an entry with the given value could be placed.
       * @param [in] val - the value.
       * @return the index where the entry with the given value could be placed.
       */
      size_t
      get_mid (const entry_val val) const;

      /** Places an entry in a row.
       * Places an entry in a row.
       * @param [in,out] idx - the index where the cell should be placed.
       * @param [in] to_place - the entry to be placed.
       */
      void
      place_cell_mid (size_t *idx, const entry to_place);

      /** Shifts all cells to the right.
       * Shifts all cells to the right.
       * @param [in,out] idx - the index from where to shift.
       * @param [in] extra - the number of positions to shift.
       * @param [in] replaced - the replaced entries.
       * @param [in] pos - the position where the replaced cells should be written.
       */
      void
      shift_cells_after_mid (size_t *  idx,
                             entry_len extra,
                             entry *   replaced,
                             size_t *  pos);

      /** Places an entry in a row, doing all the necessary shifts and so on.
       * Places an entry in a row, doing all the necessary shifts and so on.
       * @param [in] to_place - the entry to be placed.
       * @param [out] replaced - a vector of cells that were replaced.
       * @param [in] pos - the real number of cells replaced.
       */
      void
      place_cell (entry to_place, entry *replaced, size_t *pos);
    };

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX_ORDERED_ARRAY__

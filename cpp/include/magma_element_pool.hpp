#ifndef __PLACID_MAGMA_ELEMENT_POOL__
#define __PLACID_MAGMA_ELEMENT_POOL__

#include <string>
#include <cstring>

#include <map>
#include <unordered_map>

#include "magma_element.hpp"
#include "free_monoid/free_monoid_element.hpp"
#include "free_monoid/free_monoid_homomorphism.hpp"

namespace __placid
{
  /**
   * This class defines a pool of magma elements.
   * This class defines a pool of magma elements.
   */
  template <typename T>
  struct pool
  {
    static const size_t default_size =
      (1 << 5);    // !< the default size of the pool.

    size_t size;        // !< the number of cells allocated to the pool.
    size_t counter;     // !< the current size of the pool.
    T *    elements;    // !< the elements of the pool.

    /** Creates a new pool with the given size, or with the default size, in
     * case no size is specified. Creates a new pool with the given size, or
     * with the default size, in case no size is specified.
     * @param [in] size - the size of the pool.
     */
    pool (size_t size = default_size)
    {
      this->counter  = 0;
      this->size     = size;
      this->elements = new T[this->size];
    }

    /** Creates a new pool by cloning the given pool.
     * Creates a new pool by cloning the given pool.
     * @param [in] o - the pool to be cloned.
     */
    pool (pool &o) : pool (o.size)
    {
      while (this->counter < o.counter)
      {
        this->add (o.elements[this->counter]);
      }
    }

    /** Destroys the pool.
     * Destroys the pool.
     */
    ~pool ()
    {
      delete[] this->elements;
    }

    /** Returns the size of the pool.
     * Returns the size of the pool.
     */
    size_t
    get_size () const
    {
      return this->counter;
    }

    /** Adds an element to the pool.
     * Adds an element to the pool.
     * @param [in] t - the element to be added to the pool.
     */
    void
    add (const T t)
    {
      if (this->counter == this->size)
      {
        this->resize ();
      }

      this->elements[this->counter++] = t;
    }

    /** Checks if the pool contains the given element.
     * Checks if the pool contains the given element.
     * @param [in] t - the element to search for in the pool.
     */
    bool
    contains (const T t) const
    {
      for (size_t i = 0; i < this->counter; i++)
      {
        if (this->elements[i] == t)
        {
          return true;
        }
      }

      return false;
    }

    /** Removes all duplicate elements from the pool.
     * Removes all duplicate elements from the pool.
     */
    void
    remove_duplicates ()
    {
      for (size_t i = 0; i < this->counter; i++)
      {
        T curr = this->elements[i];
        for (size_t j = i + 1; j < this->counter; j++)
        {
          T curr_comp = this->elements[j];
          if (curr == curr_comp)
          {
            this->elements[j] = this->elements[--this->counter];
          }
        }
      }
    }

    /** Checks if the elements of the pool satisfy a given identity.
     * Checks if the elements of the pool satisfy a given identity.
     * @param [in] identity_ - the identity to be checked.
     */
    void
    test_identity (std::string identity_)
    {
      char *identity =
        (char *) malloc ((identity_.size () + 1) * sizeof (char));
      identity = strcpy (identity, identity_.c_str ());

      trim (identity);

      char *split_1;
      char *split_2;

      split_identity (identity, &split_1, &split_2);

      size_t split_1_sz = strlen (split_1);
      size_t split_2_sz = strlen (split_2);

      char *splits_1[split_1_sz];
      char *splits_2[split_2_sz];

      size_t nr_splits_1 = 0;
      size_t nr_splits_2 = 0;

      split_identity_variables (split_1, splits_1, &nr_splits_1);
      split_identity_variables (split_2, splits_2, &nr_splits_2);

      size_t mapped_splits_1[nr_splits_1];
      size_t mapped_splits_2[nr_splits_2];

      char *vars[nr_splits_1 + nr_splits_2];

      size_t nr_vars = get_mapped_splits (splits_1,
                                          nr_splits_1,
                                          splits_2,
                                          nr_splits_2,
                                          mapped_splits_1,
                                          mapped_splits_2,
                                          vars);

      free (identity);

      test_identity (0,
                     mapped_splits_1,
                     nr_splits_1,
                     mapped_splits_2,
                     nr_splits_2,
                     NULL,
                     vars,
                     nr_vars);
    }

      private:
    /** Resizes the pool.
     * Resizes the pool.
     */
    void
    resize ()
    {
      T *elems       = this->elements;
      this->size     = this->size * 2;
      this->elements = new T[this->size];
      for (size_t i = 0; i < this->counter; i++)
      {
        this->elements[i] = elems[i];
      }

      delete[] elems;
    }

    /** Trims the given stream, removing all spaces (from regular spaces to TABs
     * and new lines. Trims the given stream, removing all spaces (from regular
     * spaces to TABs and new lines.
     * @param [in,out] str - the string to be trimmed.
     */
    void
    trim (char *str)
    {
      size_t b = 0;
      size_t c = 0;
      while (str[c] != '\0')
      {
        if (!isspace (str[c]))
        {
          str[b++] = str[c];
        }
        c++;
      }
      str[b] = '\0';
    }

    /** Splits an identity.
     * Splits an identity.
     * @param [in] identity - the identity to be split.
     * @param [out] split1 - the left side of the identity.
     * @param [out] split2 - the right side of the identity.
     */
    void
    split_identity (char *identity, char **split1, char **split2)
    {
      char *save_ptr;
      *split1 = strtok_r (identity, "=", &save_ptr);
      *split2 = strtok_r (NULL, "=", &save_ptr);
    }

    /** Splits a side of an identity into variables.
     * Splits a side of an identity into variables.
     * @param [in] side - the string of variables.
     * @param [out] splits - the variables split.
     * @param [out] nr_splits - the number of splits.
     */
    void
    split_identity_variables (char *side, char **splits, size_t *nr_splits)
    {
      char *save_ptr;
      *nr_splits = 0;
      while ((splits[*nr_splits] = strtok_r (side, ".", &save_ptr)) != NULL)
      {
        *nr_splits = *nr_splits + 1;
        side       = NULL;
      }
    }

    // TODO optimize for different sizes (specially smaller sizes)
    /** Gets the splits mapped into variable ids.
     * Gets the splits mapped into variable ids.
     * @param [in] splits_1 - the left side of the identity.
     * @param [in] nr_splits_1 - the number of variables in the left side of the
     * identity.
     * @param [in] splits_2 - the right side of the identity.
     * @param [in] nr_splits_2 - the number of variables in the right side of
     * the identity.
     * @param [out] mapped_splits_1 - the mapped splits for the left side of the
     * identity.
     * @param [out] mapped_splits_2 - the mapped splits for the right side of
     * the identity.
     * @param [out] vars - the variables.
     * @return the number of distinct variables occurring in the identity.
     */
    size_t
    get_mapped_splits (char ** splits_1,
                       size_t  nr_splits_1,
                       char ** splits_2,
                       size_t  nr_splits_2,
                       size_t *mapped_splits_1,
                       size_t *mapped_splits_2,
                       char ** vars)
    {
      // create the mappings
      std::map<std::string, size_t> mappings;
      size_t                        id = 0;

      for (size_t i = 0; i < nr_splits_1; i++)
      {
        if (mappings.find (splits_1[i]) == mappings.end ())
        {
          mappings[splits_1[i]] = id;
          id++;
        }
      }

      for (size_t i = 0; i < nr_splits_2; i++)
      {
        if (mappings.find (splits_2[i]) == mappings.end ())
        {
          mappings[splits_2[i]] = id;
          id++;
        }
      }

      // substitute the mappings
      for (size_t i = 0; i < nr_splits_1; i++)
      {
        assert (mappings.find (splits_1[i]) != mappings.end ());
        size_t tmp         = mappings[splits_1[i]];
        mapped_splits_1[i] = tmp;
        if (vars != NULL)
        {
          vars[tmp] = splits_1[i];
        }
      }

      for (size_t i = 0; i < nr_splits_2; i++)
      {
        assert (mappings.find (splits_2[i]) != mappings.end ());
        size_t tmp         = mappings[splits_2[i]];
        mapped_splits_2[i] = tmp;
        if (vars != NULL)
        {
          vars[tmp] = splits_2[i];
        }
      }
      return id;
    }

    /** Tests an identity.
     * Tests an identity.
     * @param [in] beg - the next variable to be assigned.
     * @param [in] mapped_splits_1 - the left side of the identity, where the
     * variables are identified by indices.
     * @param [in] nr_splits_1 - the number of variables occurring in the left
     * side of the identity.
     * @param [in] mapped_splits_2 - the right side of the identity, where the
     * variables are identified by indices.
     * @param [in] nr_splits_1 - the number of variables occurring in the right
     * side of the identity.
     * @param [in] id - the current (possibly partial) variable assignment.
     * @param [in] vars - the variable names.
     * @param [in] nr_vars - the number of variables.
     */
    void
    test_identity (size_t  beg,
                   size_t *mapped_splits_1,
                   size_t  nr_splits_1,
                   size_t *mapped_splits_2,
                   size_t  nr_splits_2,
                   size_t *id,
                   char ** vars,
                   size_t  nr_vars)
    {
      if (beg == nr_vars)
      {
        bool res = check_identity_assignment (mapped_splits_1,
                                              nr_splits_1,
                                              mapped_splits_2,
                                              nr_splits_2,
                                              id,
                                              nr_vars);


        if (!res)
        {
          std::unordered_map<std::string, T> counter_example;
          for (size_t j = 0; j < nr_vars; j++)
          {
            counter_example[std::string (vars[j])] = this->elements[id[j]];
          }
          throw counter_example;
        }
      } else
      {
        size_t tests[this->counter][beg + 1];

        for (size_t i = 0; i < this->counter; i++)
        {
          for (size_t j = 0; j < beg; j++)
          {
            tests[i][j] = id[j];
          }
        }

        for (size_t i = 0; i < this->counter; i++)
        {
          tests[i][beg] = i;
          test_identity (beg + 1,
                         mapped_splits_1,
                         nr_splits_1,
                         mapped_splits_2,
                         nr_splits_2,
                         tests[i],
                         vars,
                         nr_vars);
        }
      }
    }

    /** Checks if the given identity is satisfied for the given variable
     * assignment. Checks if the given identity is satisfied for the given
     * variable assignment.
     * @param [in] x - the left side of the identity, where each entry of the
     * vector corresponds to a variable id.
     * @param [in] len_x - the number of variables appearing on the left side of
     * the identity.
     * @param [in] y - the right side of the identity, where each entry of the
     * vector corresponds to a variable id.
     * @param [in] len_y - the number of variables appearing on the right side
     * of the identity.
     * @param [in] assigns - the assignments, where each entry of the vector
     * corresponds to the index (in the pool) of the element that should be used
     * in the identity testing.
     * @param [in] nr_vars - the number of different variables occurring in the
     * identity.
     */
    bool
    check_identity_assignment (size_t *x,
                               size_t  len_x,
                               size_t *y,
                               size_t  len_y,
                               size_t *assigns,
                               size_t  nr_vars)
    {
      if (this->counter == 0)
      {
        return true;    // if there are no vars, it is not an identity.
      }

      T left_res  = this->elements[assigns[x[0]]];
      T right_res = this->elements[assigns[y[0]]];

      for (size_t i = 1; i < len_x; i++)
      {
        left_res = left_res * this->elements[assigns[x[i]]];
      }

      for (size_t i = 1; i < len_y; i++)
      {
        right_res = right_res * this->elements[assigns[y[i]]];
      }

      return left_res == right_res;
    }
  };    // namespace __placid

}    // namespace __placid

#endif    // __PLACID_MAGMA_ELEMENT_POOL__

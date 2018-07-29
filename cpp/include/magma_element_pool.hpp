#ifndef __PLACID_MAGMA_ELEMENT_POOL__
#define __PLACID_MAGMA_ELEMENT_POOL__

#include <string>
#include <cstring>

#include <map>
#include <unordered_map>

#include "magma_element.hpp"

namespace __placid
{
  template <typename T>
  struct pool
  {
    static const size_t default_size = (1 << 5);

    size_t size;
    size_t counter;
    T *    elements;

    // add pool creation with rank, given another pool?

    pool (size_t size = default_size)
    {
      this->counter  = 0;
      this->size     = size;
      this->elements = new T[this->size];
    }

    /*pool (const pool &o)
    {
      while (this->counter < o.counter)
      {
        this->elements[this->counter] = o.elements[this->counter];
        this->counter++;
      }
      }*/

    ~pool ()
    {
      delete[] this->elements;
    }

    size_t
    get_size () const
    {
      return this->counter;
    }

    void
    add (const T t)
    {
      if (this->contains (t))
      {
        return;
      }

      if (this->counter == this->size)
      {
        this->resize ();
      }

      this->elements[this->counter++] = t;
    }

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

    bool
    test_identity (std::string identity)
    {
      return true;
    }

    void
    read (std::string fn)
    {
    }

    void
    write (std::string fn, file_format format) const
    {
    }

      private:
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

    void
    split_identity (char *identity, char **split1, char **split2)
    {
      char *save_ptr;
      *split1 = strtok_r (identity, "=", &save_ptr);
      *split2 = strtok_r (NULL, "=", &save_ptr);
    }

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
      std::map<char *, size_t> mappings;
      size_t                   id = 0;

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
        size_t tmp = mappings[splits_2[i]];
        if (vars != NULL)
        {
          vars[tmp] = splits_2[i];
        }
      }
      return id;
    }

    bool
    test_identity (char *               identity,
                   void *               elems,
                   size_t               nr_elems,
                   __ap_identity_tester fn,
                   __va_assignment_t ** counter_example)
    {
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


      bool test_identity (size_t beg, size_t * id)
      {
        if (beg == nr_vars)
        {
          return fn (mapped_splits_1,
                     nr_splits_1,
                     mapped_splits_2,
                     nr_splits_2,
                     id,
                     nr_vars,
                     elems);
        } else
        {
          size_t tests[nr_elems][beg + 1];
          bool   oks[nr_elems];
          for (size_t i = 0; i < nr_elems; i++)
          {
            oks[i] = true;
            for (size_t j = 0; j < beg; j++)
            {
              tests[i][j] = id[j];
            }
          }
          for (size_t i = 0; i < nr_elems; i++)
          {
            tests[i][beg] = i;
            oks[i]        = /*spawn*/ (test_identity (beg + 1, tests[i]));
          }
          //sync;
          bool ok = true;
          for (size_t i = 0; i < nr_elems; i++)
          {
            ok &= oks[i];
            if (counter_example != NULL && !oks[i] && beg + 1 == nr_vars)
            {
              *counter_example = __va_create_variable_assignment ();
              for (size_t j = 0; j < nr_vars; j++)
              {
                __va_add_variable_assignment (
                  *counter_example, vars[j], tests[i][j]);
              }
              return ok;
            }
          }
          return ok;
        }
      }

      return nr_vars == 0 || test_identity (0, NULL);
    }
  };

}    // namespace __placid

#endif    // __PLACID_MAGMA_ELEMENT_POOL__

#include "semistandard_tableaux.hpp"
#ifdef __PLACID_SEMISTANDARD_TABLEAUX__

namespace __placid
{
  namespace semistandard_tableaux
  {
    const std::string semistandard_tableaux_format_id =
      std::string ("semistandard_tableaux");

    tableaux::tableaux (size_t size)
    {
      this->size    = size;
      this->counter = 0;
      this->rows    = new ordered_array[this->size];
    }

    tableaux::tableaux (const tableaux &o) : tableaux (o.size)
    {
      this->counter = o.counter;

      for (size_t i = 0; i < this->counter; i++)
      {
        this->rows[i] = o.rows[i];
      }
    }

    tableaux::tableaux (const free_monoid::element &o) : tableaux ()
    {
      this->add_cells (o);
    }

    tableaux::~tableaux ()
    {
      delete[] this->rows;
    }

    tableaux &
    tableaux::operator= (const tableaux &o)
    {
      if (this->size != o.size)
      {
        delete[] this->rows;
        this->size    = o.size;
        this->counter = o.counter;
      }

      for (size_t i = 0; i < this->counter; i++)
      {
        this->rows[i] = o.rows[i];
      }

      return *this;
    }

    tableaux &
    tableaux::operator= (const free_monoid::element &o)
    {
      delete[] this->rows;
      this->counter = 0;
      this->size    = default_size;
      this->rows    = new ordered_array[this->size];

      this->add_cells (o);
      return *this;
    }

    bool
    tableaux::operator== (const tableaux &o) const
    {
      if (this->counter != o.counter)
      {
        return false;
      }

      for (size_t i = 0; i < this->counter; i++)
      {
        if (this->rows[i] != o.rows[i])
        {
          return false;
        }
      }

      return true;
    }

    size_t
    tableaux::get_size () const
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->counter; i++)
      {
        sz += this->rows[i].get_size ();
      }
      return sz;
    }

    size_t
    tableaux::get_storage_size () const
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->counter; i++)
      {
        sz += this->rows[i].counter;
      }
      return sz;
    }

    static void
    get_reading_iteration_function (entry  e,
                                    size_t index,
                                    size_t real_index,
                                    void * data)
    {
      free_monoid::element *w = (free_monoid::element *) data;
      w->word[index].count    = e.count;
      w->word[index].sym      = e.val;
    }

    free_monoid::element
    tableaux::get_reading () const
    {
      size_t               storage_size = this->get_storage_size ();
      free_monoid::element reading (storage_size);

      this->iterate (get_reading_iteration_function, (void *) &reading);

      return reading;
    }

    tableaux tableaux::operator* (const tableaux &o) const
    {
      const free_monoid::element e1 = this->get_reading ();
      const free_monoid::element e2 = o.get_reading ();

      const free_monoid::element res_word = e1 * e2;

      tableaux res (res_word);
      return res;
    }

    void
    tableaux::read (FILE *f)
    {
      char format_id[256];
      if (fscanf (f, "%s", format_id) != 1)
      {
        throw invalid_file_format_exception;
      }

      if (strcmp (format_id, semistandard_tableaux_format_id.c_str ()) != 0)
      {
        throw invalid_file_format_exception;
      }

      int format;
      if (fscanf (f, "%d", &format) != 1)
      {
        throw invalid_file_format_exception;
      }

      if (format != plain_format && format != table_format
          && format != table_format)
      {
        throw invalid_file_format_exception;
      }

      this->counter = 0;
      this->size    = default_size;
      delete[] this->rows;
      this->rows = new ordered_array[this->size];

      if (format == table_format)
      {
        size_t rows;

        if (fscanf (f, "%lu", &rows) != 1)
        {
          throw invalid_file_format_exception;
        }

        char * l   = NULL;
        size_t len = 0;
        getline (&l, &len, f);
        free (l);

        this->read_table (f, rows);

      } else
      {
        size_t lines = format == plain_format ? this->get_size () :
                                                this->get_storage_size ();

        free_monoid::element e;
        if (format == plain_format)
        {
          e.read_plain (f, lines);
        } else
        {
          e.read_compressed (f, lines);
        }

        this->add_cells (e);
      }
    }

    void
    tableaux::write (FILE *f, file_format format) const
    {
      if (f == NULL)
      {
        return;
      }

      if (format != plain_format && format != compressed_format
          && format != table_format)
      {
        throw invalid_file_format_exception;
      }

      fprintf (f, "%s\n%u\n", semistandard_tableaux_format_id.c_str (), format);

      fprintf (f, "%lu\n", this->counter);

      free_monoid::element e = this->get_reading ();

      switch (format)
      {
        case plain_format:
          e.write_plain (f);
          break;
        case compressed_format:
          e.write_compressed (f);
          break;
        case table_format:
          this->write_table (f);
          break;
      }
    }

    void
    tableaux::read_table (FILE *f, size_t lines)
    {
      ssize_t read;
      char *  line     = NULL;
      size_t  len      = 0;
      char *  save_ptr = NULL;

      for (size_t i = 0; i < lines; i++)
      {
        if (getline (&line, &len, f) == -1)
        {
          throw invalid_file_format_exception;
        }

        entry_val v;
        char *    tmp = line;
        char *    res;
        while ((res = strtok_r (tmp, " ", &save_ptr)) != NULL)
        {
          tmp = NULL;

          if (this->counter == this->size)
          {
            this->resize ();
          }

          entry  e (atoll (res));
          entry *tmp      = NULL;
          size_t replaced = 0;
          this->rows[this->counter].add (&e, 1, tmp, &replaced);
        }

        free (line);
        line = NULL;
        this->counter++;
      }
    }

    void
    tableaux::write_table (FILE *f) const
    {
      for (size_t i = 0; i < this->counter; i++)
      {
        for (size_t j = 0; j < this->rows[i].counter; j++)
        {
          for (size_t k = 0; k < this->rows[i].cells[j].count; k++)
          {
            fprintf (f, "%lu ", this->rows[i].cells[j].val);
          }
        }
        fprintf (f, "\n");
      }
    }

    void
    tableaux::add_cells (const free_monoid::element &word)
    {
      size_t word_len = word.get_size ();

      entry arr1[word_len];
      entry arr2[word_len];

      entry *to_place = arr1;
      entry *replaced = arr2;

      size_t result_sz = 0;

      for (size_t i = 0, j = 0; j < word_len; j += word.word[i++].count)
      {
        entry e (word.word[i].sym, word.word[i].count);
        to_place[j] = e;
      }

      size_t j = 0;

      while (word_len != 0)
      {
        if (j == this->counter)
        {
          if (this->counter == this->size)
          {
            this->resize ();
          }
          this->counter++;
        }

        this->rows[j].add (to_place, word_len, replaced, &word_len);

        result_sz += this->rows[j++].counter;

        entry *tmp = to_place;
        to_place   = replaced;
        replaced   = tmp;
      }
    }

    void
    tableaux::resize ()
    {
      ordered_array *old = this->rows;
      this->size         = this->size * 2;
      this->rows         = new ordered_array[this->size];

      for (size_t i = 0; i < this->counter; i++)
      {
        this->rows[i] = old[i];
      }

      delete[] old;
    }

    void
    tableaux::iterate (
      const std::function<void(entry, size_t, size_t, void *)> &fn,
      void *                                                    data) const
    {
      size_t index      = 0;
      size_t real_index = 0;
      size_t i          = 0;
      size_t j          = this->counter;
      while (j != 0)
      {
        while (i < this->rows[j - 1].counter)
        {
          fn (this->rows[j - 1].cells[i], index++, real_index, data);
          real_index += this->rows[j - 1].cells[i++].count;
        }
        i = 0;
        j--;
      }
    }

  }    // namespace semistandard_tableaux

}    // namespace __placid

#endif    // __PLACID_SEMISTANDARD_TABLEAUX__

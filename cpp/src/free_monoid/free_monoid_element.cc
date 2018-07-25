#include "free_monoid_element.hpp"

#ifdef __PLACID_FREE_MONOID_ELEMENT__

#include <string>

namespace __placid
{
  namespace free_monoid
  {
    const std::string free_monoid_format_id = std::string ("free_monoid");

    free_monoid_element::free_monoid_element (size_t size)
    {
      this->length = size;
      this->word   = new entry[this->length];
    }

    free_monoid_element::free_monoid_element (symbol *w, size_t len)
    {
      this->length = len;
      this->word   = new entry[this->length];

      for (size_t i = 0; i < len; i++)
      {
        entry e (w[i]);
        this->word[i] = e;
      }

      this->compress ();
    }

    free_monoid_element::free_monoid_element (const free_monoid_element &o)
    {
      this->length = o.length;
      this->word   = new entry[this->length];

      for (size_t i = 0; i < this->length; i++)
      {
        this->word[i] = o.word[i];
      }
    }

    free_monoid_element::~free_monoid_element ()
    {
      delete[] this->word;
    }

    free_monoid_element &
    free_monoid_element::operator= (const free_monoid_element &o)
    {
      delete[] this->word;

      this->length = o.length;
      this->word   = new entry[this->length];
      for (size_t i = 0; i < this->length; i++)
      {
        this->word[i] = o.word[i];
      }
      return *this;
    }

    void
    free_monoid_element::compress ()
    {
      symbol curr_sym =
        this->length > 0 ? this->word[0].sym : 0;    // current value read
      occurrences count   = 0;    // number of repetitions of current value
      size_t      counter = 0;    // current compressed counter
      for (size_t i = 0; i < this->length; i++)
      {
        if (this->word[i].sym == curr_sym)
        {
          count += this->word[i].count;
        } else
        {
          entry e (curr_sym, count);
          this->word[counter++] = e;
          curr_sym              = this->word[i].sym;
          count                 = this->word[i].count;
        }
      }

      if (this->length > 0)
      {
        entry e (curr_sym, count);
        this->word[counter++] = e;
      }

      if (this->length != counter)
      {
        entry *w   = this->word;
        this->word = new entry[counter];

        for (size_t i = 0; i < counter; i++)
        {
          this->word[i] = w[i];
        }

        delete[] w;
        this->length = counter;
      }
    }

    bool
    free_monoid_element::operator== (const free_monoid_element &o) const
    {
      free_monoid_element e1 (*this);
      free_monoid_element e2 (o);

      e1.compress ();
      e2.compress ();

      if (e1.length != e2.length)
      {
        return false;
      }

      bool equals = true;
      for (size_t i = 0; i < e1.length; i++)
      {
        if (e1.word[i] != e2.word[i])
        {
          equals = false;
          break;
        }
      }

      return equals;
    }

    free_monoid_element free_monoid_element::
                        operator* (const free_monoid_element &o) const
    {
      free_monoid_element e (this->length + o.length);
      for (size_t i = 0; i < this->length; i++)
      {
        e.word[i] = o.word[i];
      }

      for (size_t i = 0; i < o.length; i++)
      {
        e.word[i + this->length] = o.word[i];
      }

      return e;
    }

    void
    free_monoid_element::add (symbol *s, size_t count)
    {
      entry *w   = this->word;
      this->word = new entry[this->length + count];

      for (size_t i = 0; i < this->length; i++)
      {
        this->word[i] = w[i];
      }

      for (size_t i = 0; i < count; i++)
      {
        entry e (s[i]);
        this->word[i + this->length] = e;
      }

      this->length = this->length + count;
      delete[] w;

      this->compress ();
    }

    size_t
    free_monoid_element::get_size () const
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->length; i++)
      {
        sz += this->word[i].count;
      }

      return sz;
    }

    void
    free_monoid_element::read (FILE *f)
    {
      char format_id[256];
      if (fscanf (f, "%s", format_id) != 1)
      {
        throw invalid_file_format_exception;
      }

      if (strcmp (format_id, free_monoid_format_id.c_str ()) != 0)
      {
        throw invalid_file_format_exception;
      }

      int format;
      if (fscanf (f, "%d", &format) != 1)
      {
        throw invalid_file_format_exception;
      }

      if (format != plain_format && format != compressed_format)
      {
        throw invalid_file_format_exception;
      }

      size_t lines;

      if (fscanf (f, "%lu", &lines) != 1)
      {
        throw invalid_file_format_exception;
      }

      char * l   = NULL;
      size_t len = 0;
      getline (&l, &len, f);
      free (l);

      switch (format)
      {
        case free_monoid_element::plain_format:
          this->read_plain (f, lines);
          break;
        case free_monoid_element::compressed_format:
          this->read_compressed (f, lines);
          break;
        default:
          throw invalid_file_format_exception;
          break;
      }
    }

    void
    free_monoid_element::write (FILE *f, file_format format) const
    {
      if (f == NULL)
      {
        return;
      }

      if (format != plain_format && format != compressed_format)
      {
        throw invalid_file_format_exception;
      }

      fprintf (f, "%s\n%u\n", free_monoid_format_id.c_str (), format);

      free_monoid_element e (*this);
      e.compress ();

      fprintf (f, "%lu\n", e.length);

      switch (format)
      {
        case plain_format:
          e.write_plain (f);
          break;
        case compressed_format:
          e.write_compressed (f);
          break;
      }
    }

    void
    free_monoid_element::read_plain (FILE *f, size_t lines)
    {
      delete[] this->word;
      this->length = lines;
      this->word   = new entry[this->length];

      symbol s;

      for (size_t i = 0; i < lines; i++)
      {
        if (fscanf (f, "%lu", &s) != 1)
        {
          throw invalid_file_format_exception;
        }
        entry e (s);
        this->word[i] = e;
      }

      this->compress ();
    }

    void
    free_monoid_element::read_compressed (FILE *f, size_t lines)
    {
      delete[] this->word;
      this->length = lines;
      this->word   = new entry[this->length];

      symbol      s;
      occurrences o;

      for (size_t i = 0; i < lines; i++)
      {
        if (fscanf (f, "%lu %lu", &s, &o) != 2)
        {
          throw invalid_file_format_exception;
        }

        entry e (s, o);

        this->word[i] = e;
      }

      this->compress ();
    }

    void
    free_monoid_element::write_plain (FILE *f) const
    {
      for (size_t i = 0; i < this->length; i++)
      {
        for (occurrences i = 0; i < this->word[i].count; i++)
        {
          fprintf (f, "%lu\n", this->word[i].sym);
        }
      }
    }

    void
    free_monoid_element::write_compressed (FILE *f) const
    {
      for (size_t i = 0; i < this->length; i++)
      {
        fprintf (f, "%lu %lu\n", this->word[i].sym, this->word[i].count);
      }
    }

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_ELEMENT__

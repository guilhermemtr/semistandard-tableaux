#include "free_monoid_element.hpp"

#ifdef __PLACID_FREE_MONOID_ELEMENT__

#include <string>

namespace __placid
{
  namespace free_monoid
  {
    const std::string free_monoid_format_id =
      std::string ("free_monoid_element");

    element::element (size_t size)
    {
      this->length = size;
      this->word   = new entry[this->length];
    }

    element::element (symbol *w, size_t len)
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

    element::element (const element &o)
    {
      this->length = o.length;
      this->word   = new entry[this->length];

      for (size_t i = 0; i < this->length; i++)
      {
        this->word[i] = o.word[i];
      }
    }

    element::~element ()
    {
      delete[] this->word;
    }

    element &
    element::operator= (const element &o)
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
    element::compress ()
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
    element::operator== (const element &o) const
    {
      element e1 (*this);
      element e2 (o);

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

    element element::operator* (const element &o) const
    {
      element e (*this);

      size_t len = o.get_size ();

      symbol *w2 = new symbol[len];

      size_t counter = 0;
      for (size_t i = 0; i < o.length; i++)
      {
        for (size_t j = 0; j < o.word[i].count; j++)
        {
          w2[counter++] = o.word[i].sym;
        }
      }

      e.add (w2, len);

      delete[] w2;

      return e;
    }

    void
    element::add (entry *entries, size_t count)
    {
      entry *w   = this->word;
      size_t len = this->length;
      this->word = new entry[len + count];

      for (size_t i = 0; i < len; i++)
      {
        this->word[i] = w[i];
      }

      for (size_t i = 0; i < count; i++)
      {
        entry e (entries[i]);
        this->word[i + len] = e;
      }

      this->length = len + count;
      delete[] w;

      this->compress ();
    }

    void
    element::add (symbol *s, size_t count)
    {
      entry *entries = new entry[count];

      for (size_t i = 0; i < count; i++)
      {
        entry e (s[i]);
        entries[i] = e;
      }
      this->add (entries, count);
      delete[] entries;
    }

    size_t
    element::get_size () const
    {
      size_t sz = 0;
      for (size_t i = 0; i < this->length; i++)
      {
        sz += this->word[i].count;
      }

      return sz;
    }

    void
    element::read (FILE *f)
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
        case element::plain_format:
          this->read_plain (f, lines);
          break;
        case element::compressed_format:
          this->read_compressed (f, lines);
          break;
        default:
          throw invalid_file_format_exception;
          break;
      }

      this->compress ();
    }

    void
    element::write (FILE *f, file_format format) const
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

      element e (*this);
      e.compress ();

      if (format == compressed_format)
      {
        fprintf (f, "%lu\n", e.length);
      }
      if (format == plain_format)
      {
        fprintf (f, "%lu\n", e.get_size ());
      }

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
    element::read_plain (FILE *f, size_t lines)
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
    }

    void
    element::read_compressed (FILE *f, size_t lines)
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
    }

    void
    element::write_plain (FILE *f) const
    {
      for (size_t i = 0; i < this->length; i++)
      {
        for (occurrences j = 0; j < this->word[i].count; j++)
        {
          fprintf (f, "%lu\n", this->word[i].sym);
        }
      }
    }

    void
    element::write_compressed (FILE *f) const
    {
      for (size_t i = 0; i < this->length; i++)
      {
        fprintf (f, "%lu %lu\n", this->word[i].sym, this->word[i].count);
      }
    }

  }    // namespace free_monoid

}    // namespace __placid

#endif    // __PLACID_FREE_MONOID_ELEMENT__

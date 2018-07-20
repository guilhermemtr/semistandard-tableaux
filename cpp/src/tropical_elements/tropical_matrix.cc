#include "tropical_matrix.hpp"

#ifdef __PLACID_TROPICAL_MATRIX__

namespace __placid
{
  tropical_matrix::tropical_matrix (size_t columns, size_t rows)
  {
    this->rows    = rows;
    this->columns = columns;
    this->matrix  = (tropical_number *) malloc (sizeof (tropical_number)
                                               * this->rows * this->columns);
    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      this->matrix[i] = tropical_number::get_infinite ();
    }
  }

  tropical_matrix::~tropical_matrix ()
  {
    free (this->matrix);
  }

  tropical_matrix
  tropical_matrix::operator= (tropical_matrix o)
  {
    if (this->columns * this->rows != o.columns * o.rows)
    {
      free (this->matrix);
      this->matrix = (tropical_number *) malloc (sizeof (tropical_number)
                                                 * o.rows * o.columns);
    }

    this->rows    = o.rows;
    this->columns = o.columns;

    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      this->matrix[i] = o.matrix[i];
    }

    return *this;
  }

  bool
  tropical_matrix::operator== (tropical_matrix o)
  {
    if (this->columns != o.columns || this->rows != o.rows)
    {
      return false;
    }

    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      if (this->matrix[i] != o.matrix[i])
      {
        return false;
      }
    }
    return true;
  }

  tropical_matrix tropical_matrix::operator* (tropical_matrix o)
  {
    if (this->columns != o.columns || this->rows != o.rows)
    {
      throw std::string ("Different matrix sizes");
    }

    tropical_matrix res (o.rows, o.columns);

    for (size_t i = 0; i < res.columns; i++)
    {
      for (size_t j = 0; j < res.rows; j++)
      {
        res.matrix[i + j * res.columns] = tropical_number::get_infinite ();

        for (size_t k = 0; k < this->columns; k++)
        {
          res.matrix[i + j * res.columns] =
            res.matrix[i + j * res.columns]
            + this->matrix[k + j * this->rows] * o.matrix[i + k * o.rows];
        }
      }
    }

    return res;
  }

  tropical_matrix
  tropical_matrix::operator+ (tropical_matrix o)
  {
    if (this->columns != o.columns || this->rows != o.rows)
    {
      throw std::string ("Different matrix sizes");
    }

    tropical_matrix res (o.rows, o.columns);

    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      res.matrix[i] = this->matrix[i] + o.matrix[i];
    }

    return res;
  }

  void
  tropical_matrix::read (FILE *f)
  {
    ssize_t read;
    char *  line     = NULL;
    size_t  len      = 0;
    char *  save_ptr = NULL;

    size_t sz      = 32L;
    tn_t * tns     = (tn_t *) malloc (sz * sizeof (tn_t));
    size_t entries = 0;
    size_t rows    = 0;


    while ((read = getline (&line, &len, f)) != -1)
    {
      char *tmp = line;
      char *res;
      while ((res = strtok_r (tmp, " ", &save_ptr)) != NULL)
      {
        tmp = NULL;

        if (entries == sz)
        {
          sz  = sz * 2;
          tns = (tn_t *) realloc (tns, sz * sizeof (tn_t));
        }

        tn_t tn;
        if (strcmp ("-inf", res) == 0)
        {
          tn = tropical_number::get_infinite ().get ();
        } else
        {
          if (sscanf (res, "%lu", &tn) < 0)
          {
            // failed reading an entry.
            free (tns);
            return;
          }
        }
        tns[entries++] = tn;
      }

      free (line);
      line = NULL;
      rows++;
    }

    this->rows    = rows;
    this->columns = entries / rows;

    this->matrix = (tropical_number *) malloc (sizeof (tropical_number)
                                               * this->rows * this->columns);

    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      this->matrix[i].n = tns[i];
    }

    free (tns);
  }

  void
  tropical_matrix::write (FILE *f)
  {
    if (f == NULL)
    {
      return;
    }

    for (size_t i = 0; i < this->rows; i++)
    {
      for (size_t j = 0; j < this->columns; j++)
      {
        this->matrix[i * this->columns + j].write (f);
      }
      fprintf (f, "\n");
    }
  }

}    // namespace __placid

#endif    // __PLACID_TROPICAL_MATRIX__

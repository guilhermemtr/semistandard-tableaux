#include "tropical_matrix.hpp"

#ifdef __PLACID_TROPICAL_MATRIX__

namespace __placid
{
  const std::string invalid_matrix_sizes_exception =
    std::string ("Different matrix sizes");

  const std::string tropical_matrix_format_id = std::string ("tropical_matrix");

  tropical_matrix::tropical_matrix (size_t rows, size_t columns)
  {
    this->rows    = rows;
    this->columns = columns;
    this->matrix  = new tropical_number[this->rows * this->columns];
  }

  tropical_matrix::tropical_matrix (size_t           rows,
                                    size_t           columns,
                                    tropical_number *matrix)
    : tropical_matrix (rows, columns)
  {
    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      this->matrix[i] = matrix[i];
    }
  }

  tropical_matrix::tropical_matrix (tropical_matrix &o)
    : tropical_matrix (o.rows, o.columns)
  {
    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      this->matrix[i] = o.matrix[i];
    }
  }

  tropical_matrix::~tropical_matrix ()
  {
    delete[] this->matrix;
  }

  tropical_matrix
  tropical_matrix::operator= (tropical_matrix o)
  {
    if (this->columns * this->rows != o.columns * o.rows)
    {
      delete[] this->matrix;
      this->matrix = new tropical_number[this->rows * this->columns];
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
    if (this->columns != o.rows)
    {
      throw invalid_matrix_sizes_exception;
    }

    tropical_matrix res (this->rows, o.columns);

    for (size_t i = 0; i < res.columns; i++)
    {
      for (size_t j = 0; j < res.rows; j++)
      {
        for (size_t k = 0; k < this->columns; k++)
        {
          res.matrix[i + j * res.columns] =
            res.matrix[i + j * res.columns]
            + this->matrix[k + j * this->columns] * o.matrix[i + k * o.columns];
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
      throw invalid_matrix_sizes_exception;
    }

    tropical_matrix res (o.columns, o.rows);

    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      res.matrix[i] = this->matrix[i] + o.matrix[i];
    }

    return res;
  }

  void
  tropical_matrix::read (FILE *f)
  {
    char format_id[256];
    if (fscanf (f, "%s", format_id) != 1)
    {
      throw invalid_file_format_exception;
    }

    if (strcmp (format_id, tropical_matrix_format_id.c_str ()) != 0)
    {
      throw invalid_file_format_exception;
    }

    int format;
    if (fscanf (f, "%d", &format) != 1)
    {
      throw invalid_file_format_exception;
    }

    if (format != plain_format && format != table_format)
    {
      throw invalid_file_format_exception;
    }

    size_t n_rows;
    size_t n_columns;

    if (fscanf (f, "%lu %lu", &n_rows, &n_columns) != 2)
    {
      throw invalid_file_format_exception;
    }

    delete[] this->matrix;
    this->rows    = n_rows;
    this->columns = n_columns;

    this->matrix = new tropical_number[this->rows * this->columns];

    switch (format)
    {
      case tropical_matrix::plain_format:
        this->read_plain (f);
        break;
      case tropical_matrix::table_format:
        this->read_table (f);
        break;
      default:
        throw invalid_file_format_exception;
        break;
    }
  }

  void
  tropical_matrix::write (FILE *f, file_format format)
  {
    if (f == NULL)
    {
      return;
    }

    if (format != plain_format && format != table_format)
    {
      throw invalid_file_format_exception;
    }

    fprintf (f, "%s\n%u\n", tropical_matrix_format_id.c_str (), format);

    fprintf (f, "%lu %lu\n", this->rows, this->columns);

    switch (format)
    {
      case plain_format:
        this->write_plain (f);
        break;
      case table_format:
        this->write_table (f);
        break;
    }
  }

  void
  tropical_matrix::read_plain (FILE *f)
  {
    char   input[256];
    char   nl;
    size_t entries = 0;

    for (size_t i = 0; i < this->rows * this->columns; i++)
    {
      this->matrix[entries++].read (f);
    }
  }

  void
  tropical_matrix::read_table (FILE *f)
  {
    char input[256];

    for (size_t i = 0; i < this->rows; i++)
    {
      /*char *  line = NULL;
      size_t  len  = 0;
      ssize_t read = getline (&line, &len, f);

      if (read == -1)
      {
        throw invalid_file_format_exception;
      }

      FILE *f_line = fmemopen (line, (1 + strlen (line)) * sizeof (char), "r");
      */
      for (size_t j = 0; j < this->columns; j++)
      {
	this->matrix[j + i * this->columns].read (f);
	/*        try
        {
          this->matrix[j + i * this->columns].read (f_line);
          this->matrix[j + i * this->columns].write (stdout);
        } catch (std::string e)
        {
          printf ("%s\n", e.c_str ());
	  }*/
      }

      /*      fclose (f_line);
      free(line);
      line = NULL;
      len = 0;*/
    }
  }

  void
  tropical_matrix::write_plain (FILE *f)
  {
    for (size_t i = 0; i < this->rows; i++)
    {
      for (size_t j = 0; j < this->columns; j++)
      {
        this->matrix[i * this->columns + j].write (f);
        fprintf (f, "\n");
      }
    }
  }

  void
  tropical_matrix::write_table (FILE *f)
  {
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

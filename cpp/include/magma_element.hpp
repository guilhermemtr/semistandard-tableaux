#ifndef __PLACID_MAGMA_ELEMENT__
#define __PLACID_MAGMA_ELEMENT__

#include <string>

#include <cstdio>
#include <cerrno>
#include <cstdint>

#include "config.hpp"

/**
 * The namespace __placid is the default namespace for the placid project.
 * All classes and utilities are defined within this namespace to avoid any
 * possible clashes with other code that may be used. The name of the namespace
 * itself was also chosen to avoid possible clashes with other namespaces (even
 * though these were already unlikely to occur).
 */
namespace __placid
{
  /**
   * Defines the type of file format identifiers.
   * Defines the type of file format identifiers.
   */
  typedef uint8_t file_format;

  /**
   * Defines the string corresponding to the exception to be thrown when the
   * file format is invalid. Defines the string corresponding to the exception
   * to be thrown when the file format is invalid.
   */
  const std::string invalid_file_format_exception =
    std::string ("Invalid file format");

  /**
   * This class defines an abstract magma element.
   * This class defines an abstract magma element.
   * A magma element is an element from a mathematical structure called magma.
   */
  template <typename T>
  class magma_element
  {
      public:
    /** Assigns to the magma element a value of another magma element.
     * Assigns to the magma element a value of another magma element.
     * @param [in] &o the magma element to assign.
     * @return the magma element value assigned.
     */
    virtual T &
    operator= (const T &o) = 0;

    /** Checks if magma elements are equal.
     * Checks if magma elements are equal.
     * @param [in] &o the second argument of the equality.
     * @return whether the magma elements are equal or not.
     */
    virtual bool
    operator== (const T &o) const = 0;

    /** Checks if magma elements are different.
     * Checks if magma elements are different.
     * @param [in] &o the second argument of the inequality.
     * @return whether the magma elements are different or not.
     */
    bool
    operator!= (const T &o) const
    {
      return !(*this == o);
    }

    /** Returns the multiplication of two magma elements.
     * Returns the multiplication of two magma elements.
     * @param [in] &o the second argument of the multiplication.
     * @return the multiplication of the two given magma elements.
     */
    virtual T operator* (const T &o) const = 0;

    /** Reads a magma element from a file, given the file stream.
     * Reads a magma element from a file, given the file stream.
     * @param [in] f the file stream.
     */
    virtual void
    read (FILE *f) = 0;

    /** Reads a magma element from a file, given the filename.
     * Reads a magma element from a file, given the filename.
     * @param [in] fn the filename.
     */
    void
    read (std::string fn)
    {
      FILE *f = fopen (fn.c_str (), "r");

      if (f == NULL)
      {
        throw errno;
      }

      this->read (f);

      fclose (f);
    }

    /** Writes a magma element into a file, given the file stream.
     * Writes a magma element into a file, given the file stream.
     * @param [in] f the file stream.
     * @param [in] format the file format to be used.
     */
    virtual void
    write (FILE *f, file_format format) const = 0;

    /** Writes a magma element into a file, given the filename.
     * Writes a magma element into a file, given the filename.
     * @param [in] fn the filename.
     * @param [in] format the file format to be used.
     */
    void
    write (std::string fn, file_format format) const
    {
      FILE *f = fopen (fn.c_str (), "w");

      if (f == NULL)
      {
        throw errno;
      }

      this->write (f, format);

      fclose (f);
    }
  };

}    // namespace __placid

#endif    // __PLACID_MAGMA_ELEMENT__

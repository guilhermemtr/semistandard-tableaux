#ifndef __PLACID_MAGMA_ELEMENT__
#define __PLACID_MAGMA_ELEMENT__

#include <string>

#include <cstdio>
#include <cerrno>

namespace __placid
{
  template <typename T>
  class magma_element
  {
      public:
    /** Assigns to the magma element a value of another magma element.
     * Assigns to the magma element a value of another magma element.
     * @param &o the magma element to assign.
     * @return the magma element value assigned.
     */
    virtual T
    operator= (T &o) = 0;

    /** Checks if magma elements are equal.
     * Checks if magma elements are equal.
     * @param &o the second argument of the equality.
     * @return whether the magma elements are equal or not.
     */
    virtual bool
    operator== (T &o) = 0;

    /** Checks if magma elements are different.
     * Checks if magma elements are different.
     * @param &o the second argument of the inequality.
     * @return whether the magma elements are different or not.
     */
    virtual bool
    operator!= (T &o) = 0;

    /** Returns the multiplication of two magma elements.
     * Returns the multiplication of two magma elements.
     * @param &o the second argument of the multiplication.
     * @return the multiplication of the two given magma elements.
     */
    virtual T operator* (T &o) = 0;

    /** Reads a magma element from a file, given the file stream, returning it.
     * Reads a magma element from a file, given the file stream, returning it.
     * @param f the file stream.
     * @return the magma element read.
     */
    virtual T
    read (FILE *f) = 0;

    /** Reads a magma element from a file, given the filename, returning it.
     * Reads a magma element from a file, given the filename, returning it.
     * @param fn the filename.
     * @return the magma element read.
     */
    virtual T
    read (std::string fn) = 0;

    /** Writes a magma element into a file, given the file stream.
     * Writes a magma element into a file, given the file stream.
     * @param f the file stream.
     */
    virtual void
    write (FILE *f) = 0;

    /** Writes a magma element into a file, given the filename.
     * Writes a magma element into a file, given the filename.
     * @param fn the filename.
     */
    virtual void
    write (std::string fn) = 0;
  };

}    // namespace __placid

#endif    // __PLACID_MAGMA_ELEMENT__

#ifndef __PLACID_MAGMA_ELEMENT__
#define __PLACID_MAGMA_ELEMENT__

#include <string>

#include <cstdio>

namespace __placid
{
  class magma_element
  {
      public:
    /** Assigns to the magma element a value of another magma element.
     * Assigns to the magma element a value of another magma element.
     * @param &o the magma element to assign.
     * @return the magma element value assigned.
     */
    magma_element
    operator= (magma_element &o);

    /** Checks if magma elements are equal.
     * Checks if magma elements are equal.
     * @param &o the second argument of the equality.
     * @return whether the magma elements are equal or not.
     */
    bool
    operator== (magma_element &o);

    /** Checks if magma elements are different.
     * Checks if magma elements are different.
     * @param &o the second argument of the inequality.
     * @return whether the magma elements are different or not.
     */
    bool
    operator!= (magma_element &o);

    /** Returns the multiplication of two magma elements.
     * Returns the multiplication of two magma elements.
     * @param &o the second argument of the multiplication.
     * @return the multiplication of the two given magma elements.
     */
    magma_element operator* (magma_element &o);

    /** Returns the sum of two ring elements.
     * Returns the sum of two ring elements.
     * @param &o the second argument of the sum.
     * @return the sum of the two given ring elements.
     */
    magma_element
    operator+ (magma_element &o);

    /** Reads a magma element from a file, given the file stream, returning it.
     * Reads a magma element from a file, given the file stream, returning it.
     * @param f the file stream.
     * @return the magma element read.
     */
    magma_element
    read (FILE *f);

    /** Reads a magma element from a file, given the filename, returning it.
     * Reads a magma element from a file, given the filename, returning it.
     * @param fn the filename.
     * @return the magma element read.
     */
    magma_element
    read (std::string fn);

    /** Writes a magma element into a file, given the file stream.
     * Writes a magma element into a file, given the file stream.
     * @param f the file stream.
     */
    void
    write (FILE *f);

    /** Writes a magma element into a file, given the filename.
     * Writes a magma element into a file, given the filename.
     * @param fn the filename.
     */
    void
    write (std::string fn);
  };

}    // namespace __placid

#endif    // __PLACID_MAGMA_ELEMENT__

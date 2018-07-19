#ifndef __PLACID_ABSTRACT_ELEMENT__
#define __PLACID_ABSTRACT_ELEMENT__

#include <string>

#include <cstdio>

namespace __placid
{
  class abstract_element
  {
      public:
    /** Assigns to the abstract element a value of another abstract element.
     * Assigns to the abstract element a value of another abstract element.
     * @param &o the abstract element to assign.
     * @return the abstract element value assigned.
     */
    virtual abstract_element
    operator= (abstract_element &o) = 0;

    /** Checks if abstract elements are equal.
     * Checks if abstract elements are equal.
     * @param &o the second argument of the equality.
     * @return whether the abstract elements are equal or not.
     */
    virtual bool
    operator== (abstract_element &o) = 0;

    /** Checks if abstract elements are different.
     * Checks if abstract elements are different.
     * @param &o the second argument of the inequality.
     * @return whether the abstract elements are different or not.
     */
    virtual bool
    operator!= (abstract_element &o) = 0;

    /** Reads a abstract element from a file, given the file stream, returning
     * it. Reads a abstract element from a file, given the file stream,
     * returning it.
     * @param f the file stream.
     * @return the abstract element read.
     */
    virtual abstract_element
    read (FILE *f) = 0;

    /** Reads a abstract element from a file, given the filename, returning it.
     * Reads a abstract element from a file, given the filename, returning it.
     * @param fn the filename.
     * @return the abstract element read.
     */
    virtual abstract_element
    read (std::string fn) = 0;

    /** Writes a abstract element into a file, given the file stream.
     * Writes a abstract element into a file, given the file stream.
     * @param f the file stream.
     */
    virtual void
    write (FILE *f) = 0;

    /** Writes a abstract element into a file, given the filename.
     * Writes a abstract element into a file, given the filename.
     * @param fn the filename.
     */
    virtual void
    write (std::string fn) = 0;
  };

}    // namespace __placid

#endif    // __PLACID_ABSTRACT_ELEMENT__

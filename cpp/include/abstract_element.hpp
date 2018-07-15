#include <string>

#ifndef __PLACID_ABSTRACT_ELEMENT__
#define __PLACID_ABSTRACT_ELEMENT__

class __placid_abstract_element
{
    public:
  __placid_abstract_element ();
  __placid_abstract_element (std::string fn);

  virtual ~__placid_abstract_element ();

  __placid_abstract_element
  operator* (__placid_abstract_element
               &o);    // This wouldn't allow to have a multiplication that does
                       // not require a new element to be allocated.

  __placid_abstract_element
  operator= (__placid_abstract_element &o);

  bool
  operator== (__placid_abstract_element &o);

  bool
  operator!= (__placid_abstract_element &o);

  void
  print ();

  void
  write (std::string fn);
};

#endif    // __PLACID_ABSTRACT_ELEMENT__

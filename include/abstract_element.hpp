#ifndef __ABSTRACT_ELEMENT__
#define __ABSTRACT_ELEMENT__

template <class T>
class abstract_element
{
 private:
  T val;
 public:
  abstract_element(T v);
    virtual ~abstract_element();

    abstract_element operator*(abstract_element& o); //This wouldn't allow to have a multiplication that does not require a new element to be allocated.
    bool operator ==(abstract_element& o);
    bool operator !=(abstract_element& o);
    void print();
    abstract_element clone();
    
}

#endif    // __ABSTRACT_ELEMENT__

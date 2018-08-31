#include "placid.hpp"

//#include "free_monoid/free_monoid_element.hpp"
//#include "tropical_elements/tropical_matrix.hpp"
//#include "semistandard_tableaux/semistandard_tableaux.hpp"


int
main (int argc, char **argv)
{
  __placid::free_monoid::element         res;
  // __placid::tropical_elements::number    t1;
  //__placid::tropical_elements::matrix    t2;
  //__placid::semistandard_tableaux::entry t3;
   __placid::semistandard_tableaux::tableaux t4;

  std::string out ("out.txt");

  res.write (stdout, 0);
  return 0;
}

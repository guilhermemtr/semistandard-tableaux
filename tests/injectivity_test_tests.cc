#include <gtest/gtest.h>

#include "magma_element_test_utils.hpp"

#include "free_monoid/free_monoid_homomorphism.hpp"

#include "magma_element_pool.hpp"
#include "free_monoid/factor_monoid_element_pool.hpp"

#include "tropical_elements/tropical_number.hpp"


using namespace __placid::free_monoid;


homomorphism<element>
identity ()
{
  char file_buffer[1 << 10];

  strcpy (file_buffer,
          "tuple\n4\nfree_monoid_element\n0\n1\n1\n,\nfree_monoid_"
          "element\n0\n1\n1\n,\nfree_monoid_element\n0\n1\n2\n,\nfree_"
          "monoid_element\n0\n1\n3\n");

  __placid::tuple<element> t;

  test_magma_element_file_read (t, file_buffer);

  homomorphism<element> h (t);

  return h;
}

homomorphism<element>
non_injective ()
{
  char file_buffer[1 << 10];

  strcpy (file_buffer,
          "tuple\n4\nfree_monoid_element\n0\n1\n0\n,\nfree_monoid_"
          "element\n0\n1\n1\n,\nfree_monoid_element\n0\n1\n1\n,\nfree_monoid_"
          "element\n0\n1\n1\n");

  __placid::tuple<element> t;

  test_magma_element_file_read (t, file_buffer);

  homomorphism<element> h (t);

  return h;
}

factor_element_pool<element> &
get_pool ()
{
  factor_element_pool<element> *p = new factor_element_pool<element> ();

  entry e0 (0);
  entry e1 (1);
  entry e2 (2);
  entry e3 (3);

  element w1;
  w1.add (&e1, 1);
  p->add (w1);


  element w2;
  w2.add (&e2, 1);
  p->add (w2);


  element w3;
  w3.add (&e3, 1);
  p->add (w3);


  element w11 = w1;
  w11.add (&e1, 1);
  p->add (w11);


  element w12 = w1;
  w12.add (&e2, 1);
  p->add (w12);


  element w13 = w1;
  w13.add (&e3, 1);
  p->add (w13);


  element w111 = w11;
  w111.add (&e1, 1);
  p->add (w111);

  element w123 = w12;
  w123.add (&e3, 1);
  p->add (w123);


  element w321 = w3;
  w321.add (&e2, 1);
  w321.add (&e1, 1);
  p->add (w321);


  element w221 = w2;
  w221.add (&e2, 1);
  w221.add (&e1, 1);
  p->add (w221);

  return *p;
}

// identity homomorphism word -> word
// multiplication homomorphism word -> tropical number

TEST (injectivity_test, test_get_homomorphic_image)
{
  homomorphism<element> id = identity ();
  homomorphism<element> ni = non_injective ();

  factor_element_pool<element> p = get_pool ();

  pool<element> p_id;
  p_id = p (id);

  for (size_t i = 0; i < p.counter; i++)
  {
    ASSERT_TRUE (p_id.contains (p.elements[i]));
  }

  for (size_t i = 0; i < p_id.counter; i++)
  {
    ASSERT_TRUE (p.contains (p_id.elements[i]));
  }

  pool<element> p_ni;
  p_ni = p (ni);

  for (size_t i = 0; i < p_id.counter; i++)
  {
    ASSERT_TRUE (p.contains (p_ni.elements[i]));
  }

  entry e1 (1);

  element w1;
  w1.add (&e1, 1);

  element w11 = w1;
  w11.add (&e1, 1);

  element w111 = w11;
  w111.add (&e1, 1);

  p_ni.remove_duplicates ();

  ASSERT_TRUE (p_ni.contains (w1));
  ASSERT_TRUE (p_ni.contains (w11));
  ASSERT_TRUE (p_ni.contains (w111));

  ASSERT_TRUE (p_ni.counter == 3);
}

TEST (injectivity_test, test_injectivity_test)
{
  homomorphism<element> id = identity ();
  homomorphism<element> ni = non_injective ();

  factor_element_pool<element> p = get_pool ();

  ASSERT_TRUE (p.injective (id));
  ASSERT_FALSE (p.injective (ni));
}

#include "tropical_numbers.h"

#ifdef __TROPICAL_NUMBERS__

static __tn_t
get_infinity_part (__tn_t n)
{
  return n >> (sizeof (__tn_t) * 8 / 2);
}

static __tn_t
get_value_part (__tn_t n)
{
  return (n << (sizeof (__tn_t) * 8 / 2)) >> (sizeof (__tn_t) * 8 / 2);
}

bool
__tn_is_infinite (__tn_t n)
{
  return !(!(get_infinity_part (n)));
}

__tn_t
__tn_get_value (__tn_t n)
{
  return get_value_part (n);
}

__tn_t
__tn_sum (__tn_t n1, __tn_t n2)
{
  if (__tn_is_infinite (n1) || __tn_is_infinite (n2))
  {
    return n1 > n2 ? n2 : n1;
  } else
  {
    return n1 > n2 ? n1 : n2;
  }
}

__tn_t
__tn_mult (__tn_t n1, __tn_t n2)
{
  return n1 + n2;
}

bool
__tn_equals (__tn_t n1, __tn_t n2)
{
  return (__tn_is_infinite (n1) && __tn_is_infinite (n2)) || (n1 == n2);
}


#endif    // __TROPICAL_NUMBERS__

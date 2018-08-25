#ifndef __PLACID_CONFIG__
#define __PLACID_CONFIG__

// If the NDEBUG flag is not defined, then we can make all methods public to allow for unit testing

#ifndef NDEBUG
#define private public
//#include <gtest/gtest_prod.h>
#endif    // NDEBUG

#endif    // __PLACID_CONFIG__

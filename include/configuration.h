

// the macro __cilk is automatically defined if the source code is compiled as
// cilk code.

#ifndef __cilk
#define spawn(X) X
#define sync
#else
#include <cilk/cilk.h>
#define spawn(X) cilk_spawn X
#define sync cilk_sync
#endif


#define MAIL_ADDRESS "guilhermemtr@gmail.com"
#define VERSION "version 0.1"

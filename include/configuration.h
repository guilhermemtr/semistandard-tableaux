//#define __USE_CILK__

#ifndef __USE_CILK__
#define spawn(X) X
#define sync 
#else
#define spawn(X) cilk_spawn X
#define sync __cilk_sync
#endif

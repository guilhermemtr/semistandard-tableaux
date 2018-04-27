// In order to use the the logger, you have to define __YAL_ON__ flag.
// If the flag is not defined, there will be no logs.

#ifndef __YAL_LOG__
#define __YAL_LOG__

#include <stdio.h>

extern int   dbg_lvl;
extern FILE *output;

#define init_logger()                                                          \
  do                                                                           \
  {                                                                            \
    set_output (stdout);                                                       \
  } while (0)

#define set_output(out) (output = out)

#define set_log_file(file) (output = fopen (file, "a"))
#define close_log_file() (fclose (output))

#define set_lvl_err() (dbg_lvl = YAL_ERROR)
#define set_lvl_warn() (dbg_lvl = YAL_WARN)
#define set_lvl_dbg() (dbg_lvl = YAL_DBG)
#define set_lvl_info() (dbg_lvl = YAL_INFO)

#define YAL_ERROR 1
#define YAL_WARN 2
#define YAL_DBG 3
#define YAL_INFO 4


#ifdef __YAL_ON__
#define log(lvl, ...)                                                          \
  do                                                                           \
  {                                                                            \
    if (dbg_lvl >= lvl)                                                        \
      fprintf (output, __VA_ARGS__);                                           \
  } while (0)
#else
#define log(...)                                                               \
  {                                                                            \
  }
#endif

#endif    // __YAL_LOG__

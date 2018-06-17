#include "unit_tests.h"
// #include "arg_parsing.h"
#include "yal_log.h"

// extern struct argp_option options[];
// extern struct argp argp;


int
main (int argc, char **argv)
{
  init_logger ();
  set_log_file ("log");
  set_lvl_info ();
  close_log_file ();
  run_tests();
  //  void *d = NULL;

  // int ret = argp_parse(&argp, argc, argv, 0, 0, d);
  return 0;
}

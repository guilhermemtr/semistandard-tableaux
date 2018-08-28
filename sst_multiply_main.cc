#include <iostream>

#include <boost/program_options.hpp>

#include <cstdio>

//#include "free_monoid/free_monoid_element.hpp"
//#include "free_monoid/factor_monoid_element.hpp"

#include "semistandard_tableaux/semistandard_tableaux.hpp"
#include "free_monoid/free_monoid_element.hpp"

namespace po = boost::program_options;
namespace pt = __placid::semistandard_tableaux;

int
main (int argc, char **argv)
{
  po::options_description desc ("Options");
  desc.add_options () ("help,h", "Produces this help message.")    //
    ("input,i",
     po::value<std::vector<std::string>> (),
     "Adds semistandard tableaux to the multiplication.")    //
    ("output,o",
     po::value<std::string> (),
     "Sets the output file. By default the result is written into stdout.")    //
    ("format,f",
     po::value<std::string> (),
     "Sets the output format (plain, compressed, or table).");

  po::positional_options_description p;
  p.add ("input", -1);

  po::variables_map vm;
  po::store (
    po::command_line_parser (argc, argv).options (desc).positional (p).run (),
    vm);
  po::notify (vm);


  if (vm.count ("help"))
  {
    std::cout << desc << std::endl;
    return 1;
  }

  FILE *f = stdout;

  if (vm.count ("output"))
  {
    std::string fn = vm["format"].as<std::string> ();
    f              = fopen (fn.c_str (), "w");

    if (f == NULL)
    {
      std::cout << "Error opening output file." << std::endl;
      return -1;
    }
  }

  __placid::semistandard_tableaux::entry res;

  /*if (!vm.count ("input"))
  {
    std::cout << "No input files." << std::endl;
  }

  std::vector<std::string> opts = vm["input"].as<std::vector<std::string>> ();

  for (size_t i = 0; i < opts.size (); i++)
  {
    std::string  in_fn = opts[i];
    pt::tableaux input;
    input.read_file (in_fn);
    res = res * input;
  }

  __placid::file_format fm = 0;
  if (vm.count ("format"))
  {
    std::string format = vm["format"].as<std::string> ();
    if (format == "plain")
    {
      fm = pt::tableaux::plain_format;
    } else if (format == "compressed")
    {
      fm = pt::tableaux::compressed_format;
    } else if (format == "table")
    {
      fm = pt::tableaux::table_format;
    } else
    {
      std::cout << "Invalid output format specified." << std::endl;
    }
  } else
  {
    std::cout << "No output format specified." << std::endl;
  }

  res.write (f, fm);

  fclose (f);*/

  return 0;
}

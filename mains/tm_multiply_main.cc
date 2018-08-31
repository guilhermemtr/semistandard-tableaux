#include <iostream>

#include <boost/program_options.hpp>

#include <cstdio>

#include "placid.hpp"

namespace po = boost::program_options;
namespace pt = __placid::tropical_elements;

int
main (int argc, char **argv)
{
  __placid::free_monoid::element      aaa;
  __placid::tropical_elements::number bbb;


  po::options_description desc ("Options");
  desc.add_options () ("help,h", "Produces this help message.")    //
    ("input,i",
     po::value<std::vector<std::string>> (),
     "Adds tropical matrices to the multiplication.")    //
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
    std::string fn = vm["output"].as<std::string> ();
    f              = fopen (fn.c_str (), "w");

    if (f == NULL)
    {
      std::cout << "Error opening output file." << std::endl;
      return -1;
    }
  }

  pt::matrix res;

  if (!vm.count ("input"))
  {
    std::cout << "No input files." << std::endl;
  }

  std::vector<std::string> opts = vm["input"].as<std::vector<std::string>> ();

  if (opts.size () > 0)
  {
    std::string in_fn = opts[0];

    res.read_file (in_fn);
  }

  for (size_t i = 1; i < opts.size (); i++)
  {
    std::string in_fn = opts[i];
    pt::matrix  input;

    input.read_file (in_fn);
    try
    {
      res = res * input;
    } catch (std::string exception)
    {
      printf ("%s\n", exception.c_str ());
    }
  }




  __placid::file_format fm = 0;
  if (vm.count ("format"))
  {
    std::string format = vm["format"].as<std::string> ();
    if (format == "plain")
    {
      fm = pt::matrix::plain_format;
    } else if (format == "matrix")
    {
      fm = pt::matrix::table_format;
    } else
    {
      std::cout << "Invalid output format specified." << std::endl;
    }
  } else
  {
    std::cout << "No output format specified." << std::endl;
  }

  res.write (f, fm);

  fclose (f);

  return 0;
}

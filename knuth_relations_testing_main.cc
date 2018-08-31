#include <iostream>

#include <boost/program_options.hpp>

#include <cstdio>

#include "placid.hpp"

namespace po = boost::program_options;

namespace p = __placid;

int
main (int argc, char **argv)
{
  p::free_monoid::element      aaa;
  p::tropical_elements::number bbb;

  po::options_description desc ("Options");
  desc.add_options () ("help,h", "Produces this help message.")    //
    ("input,i",
     po::value<std::string> (),
     "Adds semistandard tableaux to the multiplication.");

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

  p::tuple<p::tropical_elements::matrix> tup;
  if (vm.count ("input"))
  {
    std::string fn = vm["input"].as<std::string> ();
    try
    {
      tup.read_file (fn);
    } catch (std::string e)
    {
      std::cout << e << std::endl;
      return 1;
    }
  } else
  {
    std::cout << "No homomorphism given" << std::endl;
  }

  p::free_monoid::knuth_homomorphism<p::tropical_elements::matrix> h (tup);

  if (h.knuth_relations_satisfied ())
  {
    std::cout << "Knuth relations satisfied! :D" << std::endl;
  } else
  {
    std::cout << "Knuth relations NOT satisfied :(" << std::endl;
  }

  return 0;
}

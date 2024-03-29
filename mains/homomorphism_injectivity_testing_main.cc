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
    ("include,i",
     po::value<std::vector<std::string>> (),
     "Adds semistandard tableaux to the pool.") (
      "test,t",
      po::value<std::string> (),
      "Sets the homomorphism to be tested.");

  po::positional_options_description p;
  p.add ("include", -1);

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

  p::free_monoid::factor_element_pool<p::semistandard_tableaux::tableaux> pool;

  std::vector<std::string> opts = vm["include"].as<std::vector<std::string>> ();

  for (size_t i = 0; i < opts.size (); i++)
  {
    std::string                        in_fn = opts[i];
    p::semistandard_tableaux::tableaux input;
    try
    {
      input.read_file (in_fn);
      pool.add (input);
    } catch (std::string e)
    {
      std::cout << e << std::endl;
      return 1;
    }
  }

  p::tuple<p::tropical_elements::matrix> tup;

  if (vm.count ("test"))
  {
    std::string fn = vm["test"].as<std::string> ();
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
    std::cout << "No filename for an homomorphism given" << std::endl;
    return 1;
  }

  p::free_monoid::knuth_homomorphism<p::tropical_elements::matrix> h (tup);

  try
  {
    if (pool.injective (h))
    {
      std::cout
        << "No injectivity counter-example found for the given inputs :)"
        << std::endl;
    } else
    {
      std::cout << "The homomorphism is not injective :(" << std::endl;
    }
  } catch (std::string e)
  {
    std::cout << e << std::endl;
  }


  return 0;
}

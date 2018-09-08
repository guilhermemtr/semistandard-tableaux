# Semistandard tableaux library

* Requirements
- CMake
- Google Test Suite.
- Boost.
- Sagemath (for generating semistandard tableaux).

* Generating semistandard tableaux:
- Example: sage tableaux-generation.py 4 tmp/ all

* Testing the injectivity of an homomorphism:
- Example: ./homomorphism_injectivity_testing tmp/size_4_0.sst tmp/size_4_1.sst tmp/size_4_2.sst -t inputs/krsh.hm

* Testing if an homomorphism satisfies the Knuth relations:
- Example: ./knuth_relations_testing inputs/krsh.hm

* Testing if an identity is satisfied given a set of semistandard tableaux:
- Example: ./pool_identity_testing tmp/size_3_0.sst tmp/size_3_1.sst tmp/size_3_2.sst -t "p.q=p.p"

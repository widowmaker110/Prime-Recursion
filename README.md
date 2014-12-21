Prime-Recursion
===============

Author: Alexander Miller
Date: 10/13/2014
 
This program uses recursion within multi-threading
to generate the prime factors of any number up to 
the max number allowed by long long. On 10/13/2014 
the max number is 9223372036854775807 in a long long 
variable in the C++ language.

fastest computation with four 18-digit numbers: 0.01

The idea was to create a prime number object which would 
hold both the original number and a vector of all the prime
factors. 

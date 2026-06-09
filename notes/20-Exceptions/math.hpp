#ifndef MATH_EXCEPTIONS_HPP
#define MATH_EXCEPTIONS_HPP

#include <utility>

// The equation will likely have two roots so we need to return std::pair of doubles.
// If we have a pair p, then we can acces the first element via p.first and the second element
// via p.second. 

std::pair<double , double> find_roots(double a , double b , double c);

#endif
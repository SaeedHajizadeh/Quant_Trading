#include "math.hpp"
#include <cmath>
#include <stdexcept>

// Quadratic formula implementation
std::pair<double , double> find_roots(double a , double b , double c) {
    // It makes sense to use constant in function definition if the value does not change
    auto const determinant = b * b - 4 * a * c;
    
    // std::domain_error is a standard C++ exception class defined in the <stdexcept> 
    // header that reports situation where an input value falls outside the mathematical
    // domain of an operation.
    
    if (determinant < 0)
        throw std::domain_error{"No real roots..."};
        
    // std::sqrt returns the square root of its argument
    auto const two_a = 2 * a;
    auto const d_part = std::sqrt(determinant);
    
    // std::make_pair is a standard C++ utility function template that constructs a 
    // std::pair object by automatically deducing the types of its two arguments. It eliminate
    // the need to pass template parameters, making your code significantly cleaner and faster
    // and to write. It is in <utility> header.
    
    return std::make_pair((-b + d_part) / two_a , (-b - d_part) / two_a);
} 
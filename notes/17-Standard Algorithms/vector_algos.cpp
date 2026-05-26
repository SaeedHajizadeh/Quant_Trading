// Following the hpp file, it is good practice to implement the .cpp file after the header,
// as it contains the implementation of the functions declared in the header. This separation
// allows for better organization and modularity in the code.

#include "vector_algos.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>

// Read ints until EOF. On a bad token, clears the error state, discareds the offending line, 
// warns, and resumes. std::istream_iterator<int> walks the stream like a forward-only range;
// std::back_inserter appends to the result
std::vector<int> read_into_vector(std::istream& stream) {
    std::vector<int> result; 

    while (true) {
        // Instead of using a loop here, we can utilize std::copy
    }
    return result;
}
// Building modules usually start with building the hpp header interface
// Reason: he header is the interface. Deciding what a module offers to the rest of the program
// The .cpp is just the implementation of those decisions. If you write the header first,
// you're forced to think about what this module does before getting tangled in how it does it.

// It also tends to produce cleaner APIs, because you're picking names and parameter types
// without the implementation pulling you toward whatever happens to be convenient.

#ifndef VECTOR_ALGOS_HPP
#define VECTOR_ALGOS_HPP

#include <vector>
#include <iostream>

// Read ints from a stream until EOF, skipping non-int tokens with a warning
std::vector<int> read_into_vector(std::istream& stream = std::cin);

int sum(std::vector<int> const& v);
std::vector<int> filter_greater_than(std::vector<int> const& v , int threshold);
bool all_positive(std::vector<int> const& v);
void display_range(std::vector<int>::const_iterator begin ,
                   std::vector<int>::const_iterator end);


// Defined inline because it is short amd we want to avoid the overhead of a function call 
// for such a simple operation. Returns 0 to avoid division by zero if the vector is empty.
inline int average(std::vector<int> const& v) {
    if (v.empty())
        return 0; // Avoid division by zero
    else
        return sum(v) / int(v.size()); 
}


#endif 


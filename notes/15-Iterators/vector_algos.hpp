#ifndef Chapter_15_vector_algos_hpp
#define Chapter_15_vector_algos_hpp

#include <vector>

std::vector<int> read_into_vector();

std::vector<int> sort(std::vector<int> v);

// std::vector<int>::iterator binary_search(std::vector<int> v , int target);

// You can declare a function using the following syntax:
// bool binary_search(std::vector<int> v , int target); but this way a copy of v is passed on
// instead, to avoid unncessary copying, add & afer the type of v to pass it by reference
// also add const to indicate that the function does not modify v
bool binary_search(const std::vector<int>& v , int target);

#endif
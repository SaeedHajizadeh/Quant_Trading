#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// Here we teach the prerequisites of functions in vector_algos.cpp of this chapter


int main() {
    // We start off by std::copy --> std::copy is a C++ Standard Library algorithm in <algorithm>
    // It copies elements from a source range to a destination range 
    // Header: #include <algorithm>
    // Time Complexity: O(N)
    // Syntax: std::copy(first , last , d_last)
    // first, last: Iterators marking the beginning and ending of a source range
    // d_last: Iterator marking the start of the destination

    // Example:
    std::cout << "Building the source as {1 ,2 , 3 , 4 , 5}" << std::endl;
    std::cout << "constructing an empty destination of size() 5" << std::endl;
    std::vector<int> source = {1 , 2 , 3 , 4 , 5};
    std::vector<int> dest(source.size());    // Allocates space for a vector of size source.size()

    std::cout << "std::copy(source.begin() , source.end() , dest.begin());" << std::endl;
    std::copy(source.begin() , source.end() , dest.begin());
    std::cout << "The destination now is :";
    for (auto num : dest)
        std::cout << " " << num;
    std::cout << std::endl;




    // Notice how we needed to allocate memory prior to copying
    // To avoid this, we can utilize std::back_inserter. It calls push_back() on the 
    // destination container, effectively handling dynamic resizing
    // std::back_inserter is from <iterator>
    
    std::cout << "Building the source1 as {1 ,2 , 3 , 4 , 5}" << std::endl;
    std::cout << "constructing an empty destination with no pre-allocated memory" << std::endl;
    std::vector<int> source1 = {1 , 2 , 3 , 4 , 5};
    std::vector<int> dest1;

    std::cout << "std::copy(source1.begin() , source1.end() , std::back_inserter(dest1));" << std::endl;
    std::copy(source1.begin() , source1.end() , std::back_inserter(dest1));
    std::cout << "The destination now is :";
    for (auto num : dest1)
        std::cout << " " << num;
    std::cout << std::endl;


    return 0;
}
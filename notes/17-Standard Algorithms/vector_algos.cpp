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

// Before reading this function, look at miscellania.cpp and make sure you understand it
std::vector<int> read_into_vector(std::istream& stream) {
    std::vector<int> result; 

    while (true) {
        std::copy(std::istream_iterator<int>{stream} ,
        std::istream_iterator<int>{},
        std::back_inserter(result)
        );

        if (stream.eof()) break;
        stream.clear();
        std::string bad_line;
        std::getline(stream , bad_line);
        std::cerr << "Warning, ignoring " << bad_line << std::endl;
    }
    return result;
}

int sum(std::vector<int> const& v) {
    return std::accumulate(v.begin() , v.end() , 0);
}

std::vector<int> filter_greater_than(std::vector<int> const& v , int threshold) {
    std::vector<int> result;
    for (auto num : v){
        if (num > threshold)
            result.push_back(num);
    }
    return result;
}

// is_positive returns "static". In a .cpp file, static at file scope gives the function
// internal linkage — it's visible only inside this translation unit. Since is_positive is
// just a local helper for all_positive and isn't declared in the header, marking it static
// tells the compiler and any future reader: "this is private to this file." It also prevents
// accidental linker collisions if another .cpp defined its own is_positive.

static bool is_positive(int x){
    return (x > 0);
}


    


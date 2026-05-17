// The following two lines are called "include guards". They prevent the contents of this header
// file from being included multiple times in the same translation unit, which can cause
// compilation errors. 
#ifndef CHAPTER_02_VECTOR_ALGOS_HPP     // if not defined, define it; if defined skip the file
#define CHAPTER_02_VECTOR_ALGOS_HPP

# include <vector>
#include <iostream>

// Function declarations (prototypes) for the functions defined in vector_algos.cpp.
// The declaration promises the compiler that the function will be defined somewhere else
std::vector<int> read_into_vector();

int sum(std::vector<int> v);

std::vector<int> greater_than(std::vector<int> v , int x);

// inline functions are defined in the header file and can be used by any transaltion unit
// The inline keyword is a hint to the compiler that the function is allowed to be defined
// in multiple translation units without causing linker errors
// A translation unit is a source file and all the headers it includes. When you compile a C++
// program, each source file is compiled into an object file, like a.out. The linker then combines
// all the object files into a single executable. 

// The inline keyword is often used for small functions that are called frequently
inline double average(std::vector<int> v){
    double total = 0;
    if (v.empty()){
        std::cout << "The vector is empty! Cannot calculate the average." << std::endl;
        return 0; // throw and exception instead of returning 0
    }

    for (int num : v){
        total += num;
    }

    return total / v.size();
}



#endif // CHAPTER_02_VECTOR_ALGOS_HPP
#ifndef CHAPTER_16_VECTOR_ALGOS_HPP
#define CHAPTER_16_VECTOR_ALGOS_HPP

#include <vector>
#include <iostream>

// std::cin is C++ standard input stream object -- std::cin has the type std::istream
// We want a reference to the stream object intsead of copying it --> std::istream&
// The reason is streams are special and large objects that should generally not be copied

// Instead of always reading from std::cin, let's make std::cin
// the default and allow the caller to pass an alternative if they want.

// The following function works like: it receives a reference called stream to a stream object
// in C++. The default value of stream is the standard input stream object std::cin
// The output is a vector of integers.
std::vector<int> read_into_vector(std::istream& stream = std::cin);
int sum(std::vector<int> const& v);

// Note that the return type of the function is not a reference but the actual variable
// The reason is the reference is to a local variable and the local variable dies with the
// completion of function execution which then results in the reference referring to nothing

std::vector<int> filter_greater_than(std::vector<int> const& v , int target);

inline int average(std::vector<int> const& v) {
    if (v.empty())
        return 0;

    // std::vector<int> v; v.size(), the length (size) of a vector, is NOT an integer
    // v.size() is an object of type std::size_t (unsigned integer type --> 64bit in modern systems)
    // Converging may lose information since int is a signed 32bit integer
    // If v.size() == 5000000000 then int(v.size()) may lose information --> "narrowing conversion"
    // Modern solution:  int x{v.size()} --> initializes an integer with initial value v.size()
    //  named x. This is (mostly) equivalent to int x = v.size() except it is safer since it gives
    // error/warning if unfit/info loss : e.g. double d = 3.55; int x = d; goes fine but
    // int x{d}; is an error/warning 

    
    return sum(v) / int(v.size());
}


// We're not going to change the type of sort.  We need to perform a copy of the
// vector anyway; we may as well do that when the vector is passed in -- there
// are cases where this is faster than doing it later.
std::vector<int> sort(std::vector<int> v);


// Instead of returning an std::vector<int>::iterator, we return an
// std::vector<int>::const_iterator.  This is also an iterator, but it doesn't
// allow us to modify the values it refers to.
std::vector<int>::const_iterator binary_search(std::vector<int> const& v, int val);

#endif // CHAPTER_16_VECTOR_ALGOS_HPP


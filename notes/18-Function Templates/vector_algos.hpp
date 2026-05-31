






#ifndef CHAPTER_18_VECTOR_ALGOS_HPP
#define CHAPTER_18_VECTOR_ALGOS_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

// Function templates MUST be defined in the header
// The compiler needs the full definition to 
// instantiate a version for each T at the call site;
// a forward declaration in a header with the body in
// a .cpp won't work the way it does for ordinary
// functions


template <typename T>
std::vector<T> read_vector(std::istream& stream = std::cin) {
    std::vector<T> = result;

    while (true) {
        std::copy(std::stream_iterator<T>{stream} ,
        std::istream_iterator<T>{},
        std::back_insertor(result));

        if (stream.eof()) break;

        stream.clear()
        std::string bad_line;
        std::getline(stream , bad_line);
        std::cerr << "Warning, ignoring" << bad_line << "\n";

    }
    return result;
}

// T{} value initializes: 0 for int types, "" for
// string, 0.0 for double, false for bool. So sum works on strings
// (concatenation) without any special case

template <typename T>
T sum(std::vector<T> const& v){
    return std::accumulate(v.begin() , v.end() , T{})
}

/* By the way, what if we pass the template a type that doesn't make any sense?
 * For example, what if we try to call sum<void>?  Seeing as templates are done
 * compile-time, the compiler can detect errors like this and give you an error.
 * In this case, it may complain that we're passing void{} to a function, or
 * that std::vector<void> isn't allowed.  These errors are sometimes long and
 * unclear; learning to read them is part of learning C++.
 */


 // In the original function, we took int x by value.  However, now that we may
// be dealing with arbitrary T, the copy may be expensive, so we take it by
// const reference.

template <typename T>
std::vector<T> filter_greater_than(std::vector<T> const& v , T const& threshold) {
    std::vector<T> result;
    // Notice how auto here means we have one less thing to change.
    for (auto const& num : v)
        if (num > threshold)
            result.push_back(num);

    return result;
}



template <typename T>
T average(std::vector<T> const& v) {
    if (v.empty())
        return T{};
    
    T result{};
    for (auto const& num : v) {
        result += num;
    }
    result = result / T(std::distance(v.begin() , v.end()));
    return result;
}


// // You can equivalently write
// template <typename T>
// T average(std::vector<T> const& v) {
//     if (v.empty())
//         return T{};
    
//     return sum(v) / T(v.size());
// }


template <typename T>
bool is_positive(T const& x) {
    return x > T{};
}


template <typename T>
bool all_positive(std::vector<T> const& v) {
    // is_positive itself is a template -- we write is_positive<T> to tell the
    // compiler which instantiation to pass as the predicate
    return std::all_of(v.begin() , v.end() , is_positive<T>)
}


// Instead of generalizing int and taking std::vector<T>::const_iterator, let's
// allow any kind of iterator. std::copy requires an input iterator to read from
// so we'll call the type parameter InputIt; this is fairly common. This is purely
// for people reading our code and the compiler does not care what we call it. 
template <typename InputIt>
void display_range(InputIt begin , InputIt end) {

}

#endif
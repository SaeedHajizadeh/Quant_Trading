






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
    std::vector<T> result;

    while (true) {
        std::copy(std::istream_iterator<T>{stream} ,
        std::istream_iterator<T>{},
        std::back_inserter(result));

        if (stream.eof()) break;

        stream.clear();
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
    return std::accumulate(v.begin() , v.end() , T{});
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
    return std::all_of(v.begin() , v.end() , is_positive<T>);
}


// // Reminder on std::ostream_iterator: it is a Standard Library iterator adapter that 
// // converts output stream (such as std::cout) into functional output. This allows 
// // standard algorithms--such as std::copy--to stream data directly to a console or file
// // or a string buffer rather than copying it to a container. It is contained in <iterator>
// // and the syntax is: std::ostream_iterator<Type> iterator_name(output_stream , delimiter_string);
// // Type: The data type of the elements you want to print (e.g., int, std::string). The type must support the << operator. 
// // output_stream: The stream destination, such as std::cout
// // delimiter (Optional): A null-terminated character string (like " " or ", ") printed automatically after every element.
// // Example
// #include <iostream>
// #include <iterator>
// #include <vector>
// #include <algorithm>

// int main() {
//     std::vector<int> numbers{10, 20, 30, 40, 50};
    
//     // Create an iterator targetting std::cout with a space as a delimiter
//     std::ostream_iterator<int> out_it(std::cout, " ");

//     // Copy the contents of the vector directly to the console
//     std::copy(numbers.begin() , numbers.end() , out_it);
//     return 0;
// }




// In order to generalize display_range, we need to generalize the type of the iterators
// as well as the type of the elements (int -> T). If the vector is of type std::vector<int>
// then the iterators will be of type std::vector<int>::const_iterator and 
// std::vector<int>::const_iterator::value_type will be int. If the vector is of type std::vector<std::string>
// then the iterators will be of type std::vector<std::string>::const_iterator and
// std::vector<std::string>::const_iterator::value_type will be std::string. More generally, 
// if the vector is of type std::vector<T> then the iterators will be of type std::vector<T>::const_iterator and
// std::vector<T>::const_iterator::value_type will be T. So we can use the value_type typedef in the iterator 
// to extract the element type from the container automatically. Therefore, we can use the input iterators of
// the container as the template parameter and extract the element type from the iterator. For example, if 
// we have a vector of type std::vector<int> v then the input iterators v.begin() and v.end() will be of type
// std::vector<int>::const_iterator and the element type will be int and so for instance v.begin()::value_type 
// will be int. Let's say the iterator input, named InputIt, is of type std::vector<T>::const_iterator. 
// Then InputIt::value_type will be T. 

// We are almost there. The only problem is that the compiler can't tell at parse time whether InputIt::value_type names a type or a value.

// Suppose InputIt is actually std::vector<int>::const_iterator. Then InputIt::value_type is int (or more precisely std::vector<int>::const_iterator::value_type is int)) 
// so we can simply write std::ostream_iterator<InputIt::value_type> to create an ostream_iterator of the correct type. 
// However, the compiler can't tell at parse time whether InputIt::value_type names a type or a value.
// This is a common issue in C++ templates, and the solution is to use the typename keyword to tell the compiler that it is a type. 
// So we write typename InputIt::value_type to tell the compiler that it is a type. Then we can use this type to create an ostream_iterator of the correct type.


template <typename InputIt>
void display_range(InputIt begin , InputIt end) {
    // Extract the element type from the container automatically using the value_type typedef in the iterator
    using T = typename InputIt::value_type;  
    std::cout << "{ ";
    std::copy(begin , end , std::ostream_iterator<T>{std::cout , " "});
    std::cout << "}\n";
}


// We can generalize all the sort-related functions now. They all use random access iterators, so let's call them RandomIt
template <typename RandomIt>
RandomIt partition(RandomIt begin , RandomIt end);

template <typename RandomIt>
void quicksort_impl(RandomIt begin , RandomIt end);

// Why not make sort work on any container, not just vectors?  Any container that has a begin() and end() and supports
// random access iterators can be sorted with std::sort, so we can write a template that takes any container and sorts it.
template <typename Container>
Container sort(Container c) {
    quicksort_impl(c.begin() , c.end());
    return c;
}

template <typename RandomIt>
void quicksort_impl(RandomIt begin , RandomIt end) {
    if (end - begin <= 1) return; // Base case: 0 or 1 element is already sorted

    // Use of auto means we can leave more code unchanged.
    auto pivot = partition(begin , end);
    quicksort_impl(begin , pivot);
    quicksort_impl(pivot + 1 , end);
}


template <typename RandomIt>
RandomIt partition(RandomIt begin , RandomIt end) {
    // we use begin++: since we put the ++ after begin, the value of begin is the original first element,
    // which is assigned to the pivot, and then the compiler increments begin to point to the second element. 
    // If we had written ++begin, then begin would have been incremented before being assigned to pivot, 
    //and pivot would have been the second element instead of the first.
    auto pivot = begin++; // Choose the first element as the pivot and move begin to the next element
    for (; begin != end; ++begin) {
        if (*begin < *pivot) {
            std::swap(*begin , *pivot); // Swap the current element with the pivot
            ++pivot; // Move the pivot to the next position
        }
    }
    return pivot;
}

template <typename T>
// Up to this point, T is unknown, so we can't write std::vector<T>::const_iterator as the return type. 
// We can only write it after we know what T is. SO
typename std::vector<T>::const_iterator              // This line says to the compiler: "Trust me, I know that T is a type so std::vector<T>::const_iterator is a valid type, and that's the return type of this function."
binary_search(std::vector<T> const& v , T const& val){
    auto bottom = v.begin() , top = v.end();

    while (top != bottom) {
        auto mid = bottom + (top - bottom)/2;
        if (*mid < val)
            bottom = mid + 1;
        else if (*mid > val)
            top = mid;
        else
            return mid;
    }
}







#endif
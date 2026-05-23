#include "vector_algos.hpp"
#include <iostream>
#include <string>

#include <iterator>  // this header allows us to use std::begin and std::end

// We will use std::vector<int>::iterator a lot so we create a type alias for it
// The below makes iterator a synonym for std::vector<int>::iterator
using iterator = std::vector<int>::iterator;
using cnst_iterator = std::vector<int>::const_iterator; // for const iterators


std::vector<int> read_into_vector() {
    std::vector<int> result;
    int x;

    std::cout << "Enter integers (Ctrl + D to end input): ";

    while (result.empty()) {
        while (std::cin >> x){
            result.push_back(x);
        }
        if (std::cin.eof())
            break;
        
        std::string s;
        std::getline(std::cin , s); // read the rest of the line (the non-integer input) and write in s
        
        std::cout << " Warning: Non-integer input: " << s << " ignoring... " << std::endl;

        std::cin.clear(); // clear the fail state caused by non-integer input
        std::cin.ignore(1000 , '\n'); // ignore the rest of the line

    }
    std::cout << "End of file encountered. Stopping input." << std::endl;   
    return result;
}


// Let's implement quicksort. Quicksort is a divide and conquer algorithm that needs recursion
// To impement quicksort, we pick a pivot element, and partition the array into two subarrays: 
// one with elements less than the pivot and one with elements greater than the pivot.
// We then recursively sort the subarrays and concatenate the results.
// The recursive nature of quicksort makes it a good candidate for using iterators
// We use std::vetor<int>::iterator to represent the range of elements we want to sort
// This is a random access iterator, which means we can use it to access any element in the range in
// constant time, which is important for the efficiency of quicksort

// To get an iterator like this, we need v.begin() and v.end() which return iterators to the
// beginning and the end of the vector respectively. 
// v.begin() is the corresponding iterator to the first element of the vector
// v.end() is the corresponding iterator to one past the last element of the vector
// That means, v.end() does not point to a valid element, so is used to represent the end of the
// range of elements we want to iterate over.
// Moreover, if v is empty, v.begin() also represents an imaginary element 
// and thus v.begin() == v.end()

// Let's initiate an operator: 
// auto it = v.begin(); // it is a std::vector<int>::iterator; points to the 1st element of the vector
// We can compare iterators using == and !=
// We can also use <, >, <=, >= to compare iterators, but only if they are from the same container
// We can also use ++ and -- to move the iterator forward and backward respectively
// for example ++it moves the iterator to the next element (in this case it points to v[1])
// We can also use * to dereference the iterator and get the value it points to
// For example, *it gives us the value of the element that it points to (in this case v[1])
// We can also use it + n and it - n to move the iterator forward and backward by n positions
// We can also use

// Recall iterator is a synonym for std::vector<int>::iterator
std::vector<int> sort(std::vector<int> v) {
    iterator partition(iterator begin , iterator end);
    void quicksort_impl(iterator begin , iterator end);  // function declaration for recursive quicksort implementation
    quicksort_impl(v.begin() , v.end());    
    return v;
}


void quicksort_impl(iterator begin , iterator end) {
    iterator partition(iterator begin , iterator end); // Redeclaring partition function

    // We can subtract two iterators to get the number of elements in the range they create
    if (end - begin <= 1) // base case: if the range is empty or has one element, it's already sorted
        return;
    
    // Now let's determine the subranges for the recursive calls. We need to partition
    iterator pivot = partition(begin , end);

    // We know that pivot is already in the correct position (how?).  We also
    // know that pivot != end, so we can increment pivot.  We thus use pivot+1
    // as the beginning of our second range, and this will be correct.
    quicksort_impl(begin , pivot); // sort the left subarray
    quicksort_impl(pivot + 1 , end); // sort the right subarray
}

iterator partition(iterator begin , iterator end) {
    auto pivot = begin++;   // we choose the first element as the pivot and move the begin 
                            // iterator to the next element
    for (; begin != end ; ++begin) {
        if (*pivot > *begin) {\
            // We need to swap the pivot element with the current element 
            // and move the pivot iterator forward
            std::swap(*pivot , *begin);
            ++pivot;
            std::swap(*pivot , *begin);
        }
    // After the loop, pivot points to the location where the pivot element should be, so we
    // return it
    
    }
    return pivot;
}   



bool binary_search(const std::vector<int>& v , int target) {
    cnst_iterator begin = v.begin();
    cnst_iterator end = v.end();

    while (begin != end) {
        cnst_iterator mid = begin + (end - begin) / 2; // find the middle element (is / 2 integer division? yes it is)

        if (*mid == target)
            return true;
        else if (*mid < target)
            begin = mid + 1;
        else
            end = mid;
    }
    return false;
}



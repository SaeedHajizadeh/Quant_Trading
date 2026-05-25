#include "vector_algos.hpp"
#include <iostream>
#include <string>

std::vector<int> read_into_vector(std::istream& stream) {
    std::vector<int> result;

    int num;
    while (true) {
        while (stream >> num)
            result.push_back(num);
        if (stream.eof())
            break; // End of file reached, we're done
        stream.clear(); // Clear the error state caused by non-integer input
        std::string junk;
        std::getline(stream, junk); // Discard the rest of the line

        // normal output → std::cout
        // errors/warnings/debugging → std::cerr
        std::cerr << "Warning.. ignoring " << junk << std::endl;

    }
    return result;
}


int sum(std::vector<int> const& v) {
    int total = 0;
    for (auto num : v)
        total += num;
    return total;
}


std::vector<int> filter_greater_than(std::vector<int> const& v , int threshold) {
    std::vector<int> result;
    for (auto num : v)
        if (num > threshold)
            result.push_back(num);
    return result;
}

using iterator = std::vector<int>::iterator;
using const_iterator = std::vector<int>::const_iterator;
iterator partition(iterator begin , iterator end);
void quicksort_impl(iterator begin , iterator end);

std::vector<int> sort(std::vector<int> v) {
    quicksort_impl(v.begin() , v.end());
    return v;
}

void quicksort_impl(iterator begin , iterator end) {
    if (end - begin <= 1)
        return;
    
    auto pivot = partition(begin , end);
    quicksort_impl(begin , pivot);
    quicksort_impl(pivot + 1 , end);
}

iterator partition(iterator begin , iterator end) {
    auto pivot = begin++;

    for (; begin != end ; ++begin) {
        if (*begin > *pivot){
            std::swap(*pivot , *begin);
            ++pivot;
            std::swap(*pivot, *begin);  
        }
    }
    return pivot;
}

const_iterator binary_search(std::vector<int> const& v , int target) {
    auto begin = v.begin(), end = v.end();

    while (begin < end) {
        const_iterator mid = begin + (end - begin) / 2;
        if (*mid == target)
            return mid;
        else if (*mid > target)
            end = mid;
        else
            begin = mid + 1;
    }
    return end;
}


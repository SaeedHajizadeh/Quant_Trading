// Demonstrates standard algorithms (max_element, min_element, sort) alongside
// our own vector helpers. Both std algorithms and ours work through iterators,
// which is what lets them compose cleanly.

#include "vector_algos.hpp"

#include <iostream>
#include <algorithm>

// Custom ordering: compare by squared value rather than raw value.
// Returns true when x sorts before y under this rule.

bool compare_by_square(int x , int y) {
    return x * x < y * y;
}

int main() {
    std::cout << "Enter at least one number: \n";
    auto v = read_into_vector();

    if (v.empty()) {
        std::cout << "I said, at least one number.\n";
        return -1;
    }


    std::cout << "The vector you entered is : " << "\n";
    display_range(v.begin() , v.end());
    std::cout << std::endl;
    
    // Since we only get here if v is non-empty, it is safe to dereference (i.e. *iterator when
    // iterator is between v.begin() and v.end()) 

    std::cout << "Maximum element: "
    << *std::max_element(v.begin() , v.end()) << std::endl;

    // Min and max_element default to the operator <. We can use, instead, a custom comparison
    // UnaryPredicate e.g. compare_by_square as an optional third argument
    std::cout << "Min element (default): ";
    std::cout << *std::min_element(v.begin() , v.end()) << std::endl;
    std::cout << "Min element (by square): "
              << *std::min_element(v.begin() , v.end() , compare_by_square) << "\n";
    
    std::cout << "Sum : " << sum(v) << std::endl;
    std::cout << "Average : " << average(v) << std::endl;

    std::cout << (all_positive(v)
                  ? "All numbers you entered were positive.\n"
                  : "You entered at least one non-positive number.\n");

    // std::sort is in-place, so the original input order is lost after this.

    std::sort(v.begin() , v.end());
    std::cout << "Sorted (default): ";
    display_range(v.begin() , v.end());
    std::cout << std::endl;

    return 0;
}
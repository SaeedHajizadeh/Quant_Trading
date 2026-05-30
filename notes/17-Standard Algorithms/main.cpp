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
    std::cout << "Enter at least one number: "
    return 0;
}
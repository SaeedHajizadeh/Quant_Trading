#include "vector_algos.hpp"
#include <iostream>


int main() {
    std::vector<int> v = read_into_vector();
    std::vector<int> sorted_v = sort(v);
    std::cout << "Sorted vector: ";
    for (int x : sorted_v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cin.clear(); // clear the input buffer before reading the target integer
    std::cin.ignore(1000 , '\n'); // ignore the rest of the line

    std::cout << "Enter an integer to search for: ";
    int target;
    std::cin >> target;
    if (binary_search(sorted_v , target))
        std::cout << target << " found in the vector." << std::endl;
    else
        std::cout << target << " not found in the vector." << std::endl;

    return 0;
}
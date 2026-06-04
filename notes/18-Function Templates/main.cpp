#include "vector_algos.hpp"
#include <iostream>

int main() {
    std::cout << "Enter at least one numbber:\n";

    // read_vector<int> must be specified explicitly: the function takes no
    // argument involving T (just a stream), so there's nothing to deduce from.
    // Try changing <int> to <double> or <std::string> — the program still works.
    auto input_vector = read_vector<int>();

    if (input_vector.empty()) {
        std::cout << "No numbers entered.\n";
        return -1;
    }

    std::cout << "Sum: " << sum(input_vector) << "\n";
    std::cout << "Average: " << average(input_vector) << "\n";

    auto sorted_vector = sort(input_vector);
    std::cout << "Sorted: ";
    display_range(sorted_vector.begin() , sorted_vector.end());
    std::cout << "\n";

    return 0;
}
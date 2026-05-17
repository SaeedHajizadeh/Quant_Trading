#include "vector_algos.hpp"
#include <iostream>

int main(){
    auto v = read_into_vector();

    std::cout << "Average of the vector: " << average(v) << std::endl;
    std::cout << "Sum of the vector: " << sum(v) << std::endl;

    std::cout << "Elements greater than 5: ";
    for (auto num : greater_than(v , 5)){
        if (num > 5){
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
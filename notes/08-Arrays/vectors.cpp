#include <iostream>
#include <vector>

int main(){
    // Vectors are dynamic arrays that can grow and shrink in size. They are part of the C++ Standard Library 
    // and are defined in the <vector> header. To use vectors, you need to includethe <vector> 
    // header and specify the type of elements the vector will hold. 
    // For example, to create a vector of integers, you can use
    std::vector<int> v;
    
    int n;
    std::cout << "Enter as many integers as you want (enter a non-integer to stop): " << std::endl;
    while (std::cin >> n){
        v.push_back(n); // Add n to the end of the vector -- like appending to a list in Python
    }
    
    std::cout << "Size of vector v: " << v.size() << std::endl; // Size of the vector
    std::cout << "Capacity of vector v: " << v.capacity() << std::endl; // Capacity of the vector
    std::cout << "Is the vector empty? " << v.empty() << std::endl; // true if empty, false otherwise
    std::cout << "The first element of the vector v: " << v[0] << std::endl; // Undefined behavior if v is empty
    std::cout << "Max of the vector v: " << v.max_size() << std::endl;
    std::cout << "The vector v: ";
    for (int i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    // Standard way of playing with indices and looping through a vector uses std::size_t
    // std::size_t is an unsigned integer type used to represent the size of objects in bytes. 
    std::cout << "The vector v: ";
    for (std::size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    // Let's find the max and min using size_t objects as indices
    std::size_t i = 0;
    std::size_t max_index = 0;
    std::size_t min_index = 0;

    while (i < v.size()){
        if (v[i] > v[max_index]){
            max_index = i;
        }
        if (v[i] < v[min_index]){
            min_index = i;
        }
        i++;
    }
    if (v.empty()){
        std::cout << "The vector is empty! No max or min element." << std::endl;
    }
    else {
        std::cout << "Max element is " << v[max_index] << " at index " << max_index << std::endl;
        std::cout << "Min element is " << v[min_index] << " at index " << min_index << std::endl;
    }

    return 0;
}
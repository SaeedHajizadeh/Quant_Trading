#include "vector_algos.hpp"
#include <iostream>
#include <vector>
#include <string>

// Define a function that reads as many integers as the user wants and stores them in a vector
std::vector<int> read_into_vector(){
    std::vector<int> result;
    int x;

    while (true){
        std::cout << "Enter an integer (enter a non-integer to stop): " << std::endl;
        while (std::cin >> x)
            result.push_back(x); 
        // We get here when the user enters a non-integer so we need to clear the fail state
        if (std::cin.eof()){
            std::cout << "End of file reached! No more input to read." << std::endl;
            break;
        }
        std::cin.clear();

        // We now would like to tell the user what caused the input to fail
        std::string s;
        std::getline(std::cin , s);  // read a line from std::cin into s

        std::cout << "Warning, ignoring " << s << std::endl;
    }
    
    return result;
}

int sum(std::vector<int> v){
    int total = 0;
    for (int num : v){
        total += num;
    }
    return total;
}




// Function that given a vector and an integer, returns all elements greater than the given integer
std::vector<int> greater_than(std::vector<int> v , int x){
    std::vector<int> result;

    for (int num : v){
        if (num > x){
            result.push_back(num);
        }
    }

    return result;
}
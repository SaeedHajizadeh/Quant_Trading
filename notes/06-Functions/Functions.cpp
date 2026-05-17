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



// Define a function that given a vector, returns the average of its elements
double average(std::vector<int> v){
    double total = 0;
    if (v.empty()){
        std::cout << "The vector is empty! Cannot calculate the average." << std::endl;
        return 0; // throw and exception instead of returning 0
    }

    for (int num : v){
        total += num;
    }

    return total / v.size();
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


int main(){
    std::vector<int> v = read_into_vector();
    std::cout << "You entered the following integers: ";
    for (int num : v){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "The average is " << average(v) << std::endl;
    std::cout << "The following integers are greater than 5: ";
    std::vector<int> greater_than_5 = greater_than(v , 5);
    for (std::size_t i = 0 ; i < greater_than_5.size(); ++i){
        std::cout << greater_than_5[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
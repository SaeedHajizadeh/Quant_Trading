#include <iostream>
#include <vector>

int main(){
    // For loop has the structure for (initialization; condition; update) { body }
    // The initialization is executed once at the beginning of the loop, and is typically
    // used to declare and initialize a loop variable.
    // You can define multiple variables of the same type, but you cannot define multiple variables 
    // of different types

    // The loop continues as long as the condition is true.
    // Any of the three parts may be omitted, but the semicolons are required. 
    // for (;;) is an infinite loop like while (true)

    // Let's create a vector of integers and calculate its minimum and maximum elements

    int x;
    std::vector<int> v;
    
    while (v.empty()){
        std::cout << "Enter as many integers as you want (enter a non-integer to stop): " << std::endl;
        while (std::cin >> x){
            v.push_back(x);
        }
        if (v.empty()){
            std::cin.clear();
            std::cin.ignore(1000 , '\n');
            std::cout << "You haven't entered any integers! Please try again." << std::endl;
        }
    }
    
 
    std::size_t max_index = 0;
    std::size_t min_index = 0;

    for (std::size_t i = 0; i < v.size(); ++i){
        if (v[i] > v[max_index]){
            max_index = i;
        }
        if (v[i] < v[min_index]){
            min_index = i;
        }
    }
    std::cout << "Max element is " << v[max_index] << " at index " << max_index << std::endl;
    std::cout << "Min element is " << v[min_index] << " at index " << min_index << std::endl;

    // You can also use a range-based for loop to iterate through the elements of the vector
    // You do not have access to the indices of the elements in a range-based for loop
    int total = 0;
    for (int num : v){
        total += num;
    }
    std::cout << "The total of the elements in the vector v is: " << total << std::endl;


    // If v was defined to be a vector of doubles then num and total above need to be doubles too
    std::vector<double> w;
    double y;
    while (w.empty()){
        // emptying the fail state and the input buffer in case the user entered a non-integer
        // in prior attempt to fill in another vector using std::cin type
        std::cin.clear();
        std::cin.ignore(1000 , '\n');
        std::cout << "Enter as many integers as you want (enter a non-integer to stop): " << std::endl;
        while (std::cin >> y){
            w.push_back(y);
        }
        if (w.empty()){
            std::cin.clear();
            std::cin.ignore(1000 , '\n');
            std::cout << "You haven't entered any integers! Please try again." << std::endl;
        }
    }
    double total_double = 0.0;
    for (double num : w){
        total_double += num;
    }
    std::cout << "The total of the elements in the vector w is: " << total_double << std::endl;

    // we can simplify the for loop using auto type deduction; let compiler choose the type
    total_double = 0.0;
    for (auto num : w){
        total_double += num;
    }
    std::cout << "The total of the elements in the vector w is: " << total_double << std::endl;


    // Let's change to an incorrect int--what changes?
    total_double = 0.0;
    for (int num : w){
        total_double += num;
    }
    std::cout << "The total of the elements in the vector w is: " << total_double << std::endl;

    return 0;
}
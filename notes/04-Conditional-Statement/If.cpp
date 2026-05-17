#include <iostream>
#include <string>

int main(){
    std::string name;
    std::cout << "Enter your best friend's name: " << std::endl;
    std::cin >> name;

    if (name == "Amir"){
        std::cout << "Congratulations! Amir is your best friend!" << std::endl;
    }
    else if (name == "Amir Masoud"){
        std::cout << "Congratulations! Amir Masoud is your best friend!" << std::endl;
    }
    else {
        std::cout << "Shame one you! How can you forget your best friend's name?!" << std::endl;
    }


    // Put a check whether an input is valid
    int x;
    std::cout << "Enter a number for x: " << std::endl;
    std::cin >> x;

    if (!std::cin){
        std::cout << "Invalid input! Please enter an integer number.";
        return 1; // Means the program ended with an error
    }

    // Recall that std::cout << "Hello" evaluates to std::cout, which is a stream object
    // Similarly, std::cin >> x evaluates to std::cin which is also a stream object
    // So, we can chain multiple input operations together
    std::cout << "Enter another number for x: " << std::endl;
    if (!(std::cin >> x)){
        std::cout << "Invalid input! Please enter an integer number.";
        return 1; // Means the program ended with an error
    }

    // Instead of returning 1; you can clear the fail state, clear the cache and ask the user 
    // to enter a valid input again

    std::cout << "Enter another number for x: " << std::endl;
    while (!(std::cin >> x)){
        std::cin.clear(); // Clear the fail state
        std::cin.ignore(1000 , '\n'); // Clear the input buffer
        std::cout << "Invalid input! Please enter an integer number. Please try again: \n";
    }
    std::cout << "You successfully entered: " << x << std::endl;



    // Finally since std::cin is a stream object and evaluates to std::cin, you can input
    // multiple integers
    int y;
    std::cout << "Enter two numbers for x and y: " << std::endl;
    while (!(std::cin >> x >> y)){
        std::cin.clear();
        std::cin.ignore(1000 , '\n');
        std::cout << "One or both inputs were invalid. Please try again: \n";
    }
    std::cout << "You successfully entered: " << x << " and " << y << std::endl;
    return 0;
}
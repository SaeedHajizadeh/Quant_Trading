// We are introducing types here
#include <iostream>
#include <string>
#include <limits>

int main(){
    int counter = 0; // integer type
    double price = 100.2; //double type
    char act = 'B'; //character type
    bool is_volatile = true; //boolean type

    std::cout << "Counter is equal to: " << counter << std::endl;
    std::cout << "Price is equal to: " << price << std::endl;
    std::cout << "Action is : " << act << std::endl;
    std::cout << "Is the market volatile? " << std::boolalpha << is_volatile << std::endl;

    // We can now set new values to these variables
    std::cout << "Let's change the values of these variables!" << std::endl;
    std::cout << "Enter a value/integer for the counter: " << std::endl;
    std::cin >> counter;
    std::cout << "Counter is now equal to: " << counter << std::endl;
    std::cout << "Enter a value/double for the price: " << std::endl;
    std::cin >> price;
    std::cout << "Price is now equal to: " << price << std::endl;   
    std::cout << "Enter a value/character for the action: " << std::endl;
    std::cin >> act;
    std::cout << "Action is now : " << act << std::endl;
    std::cout << "Is the market volatile? (true/false) " << std::endl;
    std::cin >> std::boolalpha >> is_volatile;
    std::cout << "Is the market volatile? " << std::boolalpha << is_volatile << std::endl;

    // Now define an integer value'
    int x;
    std::cout << "Enter a number for x: " << std::endl;
    std::cin >> x;
    std::cout << "You entered: " << x << std::endl;
    
    int y = 2 * x + 11;
    std::cout << "The value of y is: " << y << std::endl;

    
    std::string s;

    // std::cin >> s; reads only until the first whitespace (space, tab, newline).
    std::cout << "Enter a sentence and see what happens: " << std::endl;
    std::cin >> s;
    std::cout << "You entered: " << s << std::endl;

    // To read a full line of input, including spaces, we can use std::getline

    // First discard everything left in the buffer up to and including the newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   // Need #include <limits>
    std::cout << "Enter an new sentence and see what happens: " << std::endl; 
    std::getline(std::cin , s); // This will read the remaining newline character from the previous input
    std::cout << "You entered: \n" << s << std::endl;

    return 0;
}



#include <iostream>
#include <string>

void reference_practice() {
    int x = 5;
    int& ref_x = x; // ref_x is a reference to x
    std::cout << "Value of x: " << x << " and ref_x: " << ref_x << std::endl;

    // Let's try assigning a new value to ref_x
    ref_x = 10;
    std::cout << "After changing ref_x, value of x: " << x << " and ref_x: " << ref_x << std::endl;

    // Let's try assigning a new value to x
    x = 20;
    std::cout << "After changing x, value of x: " << x << " and ref_x: " << ref_x << std::endl;

    // No matter what we do, x and ref_x will always have the same value

    // auto can be used to deduce the type of a reference
    auto z1 = ref_x; // z1 is an int, not a reference
    auto& z2 = ref_x; // z2 is a reference to ref_x (and thus to x)
    std::cout << "z1: " << z1 << " and z2: " << z2 << std::endl;

    x = 15;
    std::cout << "After changing x again, z1: " << z1 << " and z2: " << z2 << std::endl;

    // Let's see what happends inside a function
    // We can only declare a function but not define it here since we are in another function
    void takes_a_reference(int& i);
    std::cout << std::endl;

    std::cout << "> x == " << x << std::endl;
    std::cout << "> takes_a_reference(x);" << std::endl;
    takes_a_reference(x);
    std::cout << "> x == " << x << std::endl;

    // C++ allows us to guarantee the value of a reference won't change by using const
    // int const y = 5; // y is a constant integer, its value cannot be changed
    // int const& ref_y = y; // ref_y is a constant reference to y
    // ref_y = 10; // This will cause a compile-time error because ref_y is a constant reference

    // Rules regarding reading types: Read from right to left (best way)
    // e.g. int const& ref_y; // ref_y is a reference to a constant integer
    // int const& is equivalent to const int&; both mean a reference to a constant integer

    
    int& a = x;         // mutable reference
    const int& b = x;   // read-only reference

    a = 7;              // OK
    // b = 8;              // ERROR - cannot assign to a read-only reference
    // b = 8 is only possible if we change the value of x, which b is referencing to
    // x = 8;              // OK - changes the value of x, which b is

    // Let's see what happens when we are dealing with functions
    void takes_a_reference_to_const(int const& i);

    std::cout << std::endl;
    std::cout << "> x == " << x << std::endl;
    std::cout << "> takes_a_reference_to_const(x);" << std::endl;
    takes_a_reference_to_const(x);
    std::cout << "> x == " << x << std::endl;   // x does not change

    // Question: What can we make a reference to? One clear answer is another variable
    // The other answer is a function return value, but only if the function returns a reference

    std::cout << std::endl;
    std::cout << "double const& d = x;" << std::endl;
    double const& d = x; // d is a reference to a constant double, initialized with the value of x (which is an int)
    std::cout << "> x == " << x << std::endl; 
    std::cout << "> d == " << d << std::endl; 

    x = 22;
    std::cout << "> After changing x to 22, x == " << x << std::endl; 
    std::cout << "> d == " << d << std::endl; // d doesn't change bc it is a reference to a constant double
    // when making the constant double, a temporary double is created with the value of x,
    // and d is a reference to that temporary double.


    // temporary object is one that dies at the end of the full expression in which it is created.
    // for example, std::string("hello") is a temporary object that dies at the end of the line
    // Lifetime extension: If a temporary object is bound to a reference to const, its lifetime
    // is extended to match the lifetime of the reference. For example:
    // const std::string& s = std::string("hello"); 
    // The temporary string "hello" lives as long as s does    

    // The lifetime extension only applies to references to const, not to non-const references. e.g.
    // std::string& s2 = std::string("world"); // ERROR - cannot bind a temporary to a non-const reference

    // Also, lifetime extension does not work to return a reference from a function if the reference
    // is to a temporary object created inside the function. For example:
    // const std::string& get_temporary() {
    //     return std::string("temporary"); // ERROR - returning a reference to a temporary
    // }

    std::cout << "\n";
    void print(std::string const& str);
    // What's the \"?  We can't have a " in the string, as that would end the
    // string.  The \" is turned into a ".
    std::cout << "print(\"I'm a string literal, not a string, but I can be converted!\");\n";
    print("I'm a string literal, not a string, but I can be converted!");

}



void takes_a_reference(int& i) {
    std::cout << ">  i == " << i << "\n";
    i = 7;
    std::cout << "i = 7;\n";
}

void takes_a_reference_to_const(int const& i) {
    std::cout << ">  i == " << i << "\n";
}

void print(std::string const& str) {
    std::cout << ">  str == \"" << str << "\"\n";
    std::cout << str << "\n";
}




#include "vector_algos.hpp"


int main() {
    reference_practice();

    std::cout << std::endl;
    std::cout << "Enter as many numbers as you want:\n";
    auto v = sort(read_into_vector());    

    std::cout << "You entered:\n";
    for (auto num : v)
        std::cout << " " << num;
    
    std::cout << std::endl;

    // Search for a few numbers in that sorted vector v
    for (int i = 0; i < 50; i += 5) {
        auto it = binary_search(v, i);
        if (it == v.end())
            std::cout << i << " was not amongst the numbers you entered.\n";
        else
            std::cout << "You entered " << (it - v.begin()) << " numbers less than " << i << ".\n";
    }

    std::cout << "Average: " << average(v) << "\n";
    std::cout << "Sum: " << sum(v) << "\n";


    std::cout << "Elements greater than 5:";
    for (auto e : filter_greater_than(v, 5))
        std::cout << " " << e;
    std::cout << std::endl;

    return 0;
}
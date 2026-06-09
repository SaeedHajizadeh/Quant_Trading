// Recommended order to read: main.cpp -> io.hpp -> math.hpp -> math.cpp -> main.cpp

// This file is meant to be a sandbox for testing out exceptions. 
// Exceptions are a powerful tool for handling errors in C++.
// They allow you to write code that can gracefully handle unexpected situations without crashing the program.
// Exceptions split our code into two parts: the throwing code, which detects an error and throws an exception,
// and the catching code, which handles the exception when it is thrown.

// When an exception is thrown, its type is remembered.  A catcher is found, and
// then its catch clauses are inspected from top to bottom.  If any of them have
// a suitable type, that catch clause is run and the statements in there should
// handle the error.  If we've checked all catchers up to main and nobody is
// willing to handle this type of exception, the program terminates.


// We can see this system as one of passing around responsibility.  When you
// call a function, you make it responsible for computing a certain value.  If a
// function cannot do that, it can throw an exception.  It loses its
// responsibility (and thus also its right to keep executing), and we look at
// each caller in turn to see who is willing to accept this responsibility.
// Whoever does has his handler code run.  If nobody does, no code is run, and
// your program grinds to a halt.

#include "io.hpp"
#include "math.hpp"
#include <iostream>

int main() try {
    std::cout << "Enter a: ";
    auto a = read<double>();
    std::cout << "Enter b: ";
    auto b = read<double>();
    std::cout << "Enter c: ";
    auto c = read<double>();

    auto result = find_roots(a, b, c);
    std::cout << "First root: " << result.first << std::endl;
    std::cout << "Second root: " << result.second << std::endl;
    // Notice how we do not need to check for errors in here. It is all done by read and find_roots
    // if anything goes wrong, am exception will be thrown and we will jump to catch it below. We
    // have separated the code that does the work from the code that handles errors.
}


// Now it is time to do error catch. What do we catch though? The two types of erros 
// that we threw were std::runtime_error and std::domain_error. One solution to catch
// those is to write individual catch blocks for each of them, but there is a better
// solution.

// Before going into details, let us look at supertype and subtype entities in C++
/* In C++, subtype and supertype entities are implemented using object-oriented inheritance. The supertype is the base class (or parent), which holds shared characteristics, while the subtype is the derived class (or child) that inherits from the base class and adds specialized attributes or behaviors.

Implementation Details

* Supertype:    The general class with common properties (e.g., Vehicle).
* Subtype:      The specialized class (e.g., Car, Truck) that uses public inheritance public to establish an "is-a" relationship (e.g., a Car is a Vehicle).
* Polymorphism: This allows you to treat subtypes as their supertype, dynamically executing specific code at runtime using virtual functions and pointers or references.
*/

// C++ types do not have to be distinct. We have type hierarchy: i.e. supertypes and
// subtypes. If a type A is a subtype of type B, that means every value that has type
// A also has type B. Alterantively, we say that B is a supertype of A. In this 
// example, std::runtime_error and std::domain_error both has a supertype of 
// std::exception, so catching std::exception will catch both of them. 

// However, a subtype may say more about the value than a supertype does. If
// we catch std::exception by value, we will be copying the std::runtime_error
// and std::domain_error, which may lose us data.  Instead, we'll catch it by
// reference: seeing as our value has type std::exception that is allowed, and
// seeing as our reference refers to the original object, no data loss can
// occur.

catch (std::exception& e) {
    // e.what() returns the message that we attached to the object e which is either
    // of type std::runtime_error or std::domain_error
    std::cerr << "Error: " << e.what() << std::endl;
    return -1;
}

// Since we really do NOT want any catch to escape the main() function, we can use
// catch(...) clause to catch errors of any type. However, as the value of the error
// can be of any type, it woould not make sense for us to be able to inspect it; we
// would not know this error.

catch (...) {
    std::cerr << "Unknown error..." << std::endl;
    return -1;
}



// There are a group of developers who are not so fond of exceptions as a method of
// handling the errors.
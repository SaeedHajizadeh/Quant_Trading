#ifndef IO_Exceptions_HPP
#define IO_Exceptions_HPP

#include <iostream>
#include <stdexcept>

/*

We are going to define a function template that reads a value of the type we specify (e.g. T).
If it can't read the value, it will throw an instance of std::runtime_error with a message that describes the error.

C++ allows us to throw any type as an exception, but it is generally recommended to throw only those types that are
designed to be used as exceptions, such as those derived from std::exception. We should limit ourselves to those types
since they have a standard interface that can be used to retrieve information about the error (e.g. the what() method).
We will learn later how to define our own exception types, but for now we will stick to the standard ones.

*/

// We note the difference between std::istream and std::ostream. The former is used for input (e.g. reading from the console or a file),
// while the latter is used for output (e.g. writing to the console or a file).

/*

Key Differences at a Glance
Feature                    std::istream                                std::ostream
Direction                  Input (Read)                                Output (Write)
Common Use Case            Getting input from a keyboard or file       Printing to the console or writing to a file
Operator                   Extraction operator: >>                     Insertion operator: <<
Examples                   std::cin, std::ifstream                     std::cout, std::ofstream

*/

template <typename T>
T read(std::istream& stream = std::cin) {
    T result;

    // If everything went well, we return
    if (stream >> result) {
        return result;
    }

    // If we hit the end of file (eof), we report that by throwing an exception with a message 
    if (stream.eof()) 
        throw std::runtime_error{"Read failed: End of file reached."};

    // If we reach here, it means the input was in some other format
    throw std::runtime_error{"Read failed: Invalid input format."};
}


#endif
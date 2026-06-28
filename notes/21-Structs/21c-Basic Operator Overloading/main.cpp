/*
    Up to this point we have learned how to create Token types (that we use here to 
    represent tokens), know how to pass them to functions, and how to read their 
    values and types. However, we cannot 'compare' them in the sense that if x and y
    are two tokens, we cannot evaluate the predicates x == y or x != y, and we also
    cannot pass x to a standard output stream, i.e. std::cout << x is undefined. 

    We fix these issues here using "operator overloading". We teach C++ what ==, !=
    >>, and << mean for Tokens. 

    Operator overloading in C++ allows you to redefine how standard operators
    (like +, ==, or <<) behave when used with custom classes or structures. It is
    a form of compile-time polymorphism that provides "syntactic sugar," making
    user-defined objects look and act like built-in types.

    This chapter fixes that by *overloading* those operators -- teaching C++ what
    they mean for Tokens. An overloaded operator is just a function with a special
    name (operator==, operator<<, ...), so this is nothing we couldn't already do
    with ordinary functions; the operator syntax is simply nicer to read.
*/

// Next go to token.hpp

#include "lex.hpp"
#include <iostream>
#include <exception>

int main() try{
    Token tok;

    while (std::cin >> tok)
        std::cout << tok << std::endl;

    
    // std:: string lexar;
    // Token tokb;
    // while (std::cin >> tokb)
    //     lexar += tokb.value;
    //     lexar += " ";

    // std::cout << lexar << '\n';
}

catch(std::exception const& e) {
    std::cerr << "Error " << e.what() << std::endl;
    return -1;
}

catch(...) {
    std::cerr << "Unknown error.\n";
    return -1;
}
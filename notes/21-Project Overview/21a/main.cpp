// In these projects, we will be building a simple lexer, parser, and interpreter for a LISP-like
// programming language. 



/*
    The LISP language is a family of programming languages that have a long history in 
    computer science. It was one of the earliest programming languages, and it has
    influenced many other languages that came after it. LISP is known for its simple syntax,
    which is based on the idea of lists. In LISP, code and data are represented as lists, 
    which makes it easy to manipulate code as data. 

    LISP looks something like this: (+ 1 2) which means "add 1 and 2". The first element of the
    list is the operator, and the rest of the elements are the operands.

    A more sophisticated expression might look like this: (* (+ 1 2) (- 4 3))
    In C++ this can be written as: (1 + 2) * (4 - 3)

    We can also define variables and functions in LISP. For example, we can define a variable x
    as follows: (define x 10). A lambda function that raises its argument to the power of 2 can
    be defined as: (define square (lambda (x) (* x x))).

    We'll also support the -, /, ==, !=, <, <=, >, >= operators and an if
    function. This means the factorial function can be written as:
   
     (define factorial
             (lambda (x)
                     (if (<= x 1)
                        0
                         (* x (factorial (- x 1))))))
   
    Translated to C++, the above is almost exactly the same as
   
     int factorial(int x) {
         if (x <= 1)
             return 0;
         else
             return x * factorial(x-1);
     }



    All in all, we want a program that can take
 
    (+ foo 24)
  
    And print
 
    { open_paren: "(" }
    { name: "+" }
    { name: "foo" }
    { number: "24" }
    { close_paren: ")" }
    { end_of_file: "" }
}
*/


#include <string>
#include <iostream>
#include <cctype>
#include <stdexcept>

// Split the program into a few functions

void print_next_token(std::istream& stream);

// Let's get the implementation of main out of the way first before we go into mode details
int main() try {
    while (std::cin) {
        print_next_token(std::cin);
        std::cout << std::endl;
    }
}

catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return -1;
}

catch (...) {
    std::cerr << "Unknown error" << std::endl;
    return -1;
}

// We are done with the main function and now let's implement the more interesting part of the code

// We will use helper functions for lexing and non-trivial symbols. The simpler ones will be
// handled in the print_next_token function itself.

void lex_name(std::istream& stream);
void lex_number(std::istream& stream);
void lex_operator(std::istream& stream);

// Let's write a function to check for the tokens that are allowed as operators
bool is_operator(char c) {
    // std::string represents the standard string class in C++. It is a part of the C++ Standard 
    // Library and provides a convenient way to work with strings. std::string::find is a member
    // function of the std::string class that searches for the first occurrence of a specified
    // character or substring within the string. It returns the index of the first occurence of
    // the character or substring, or std::string::npos if it is not found.
    // In this case, we are checking if the character c is one of the allowed operators.
    // The following checks if character c is found in valid_operators string
    std::string const valid_operators = "+-*-/!=<>";
    return valid_operators.find(c) != std::string::npos;    
}


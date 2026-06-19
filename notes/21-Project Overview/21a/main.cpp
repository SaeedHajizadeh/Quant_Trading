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




/*

    This very program is a lexar (also called a tokenizer). You feed it text; it reads one
    character at a time and groups characters into meaningful chunks called tokens., labeling
    each one. It throws whitespaces away because nothing later cares about it. 

    If input is "(+ foo 24)" the code produces the following tokens:
    { open_paren: "(" }
    { name: "+" }
    { name: "foo" }
    { number: "24" }
    { close_paren: ")" }
    { end_of_file: "" }

    One line per token. Each line says what kind of token it found and the exact text it was:
    ( is an open_paren token, + and foo are name tokens, and 24 is a number token and ) is a
    closed_paren token. This output is a description of the tokens found in the input.

    The next program, a parser, will reason about "the name foo" and "the number 24"
*/




#include <string>
#include <iostream>
#include <cctype>
#include <stdexcept>

// ----------------- Character Classification ------------------
//
// The <cctype> functions take an int whoser value must be represetable as an unsigned char or EOF.
// 'char' is often signed, so a byte >= 128 becomes negative, and passing it directly becomes 
// undefined behavior. We do the cast once here to avoid the issue. and we cname these so they 
// cannot be confused with the standard library functions (std:: functions).



// std::isspace(c) is a standard library function from <cctype> header that answers "is c a 
// whitespace character?"--space, tab, newline, etc. It returns a non-zero value if affirmative.
// It is used instead of c == ' ' || c == '\t' || c == '\n'

// static_cast<unsigned char>(c) is just a type conversion to avoid undefined behavior
// when passing a signed char to the <cctype> functions.
// This is necessary because the <cctype> functions expect an unsigned char or EOF,
// not a signed char. 

// static_cast<T>(x) means "convert x to type T"--for example, static_cast<int>(3.9) gives 3.
// Here it converts c (a char) into an unsigned char before passing it to std::isspace which is
// a <cctype> function.

bool is_space(char c) { return std::isspace(static_cast<unsigned char>(c)); }

// std::isalpha(c) is a standard library function from <cctype> header that answers "is c a
// alphabetic character?"--a-z, A-Z. It returns a non-zero value if affirmative.
// It is used instead of c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'
bool is_alpha(char c) { return std::isalpha(static_cast<unsigned char>(c)); }

// std::isdigit(c) is a standard library function from <cctype> header that answers "is c a
// digit character?"--0-9. It returns a non-zero value if affirmative.
// It is used instead of c >= '0' && c <= '9'
bool is_digit(char c) { return std::isdigit(static_cast<unsigned char>(c)); }









// Let's now write a function to check if a character is a valid operator
bool is_operator(char c) {
    std::string const valid_operators = "+*-/!=<>";
    return valid_operators.find(c) != std::string::npos;
}


// ------------------------- Driver ------------------------------
// Reads one token from the stream and prints it. Everything else is called from here

void print_next_token(std::istream& stream);

// Let's get the implementation of main out of the way first before we go into mode details
// int main() try { ... } catch(...) { ... } is a function-try-block: the try wraps the entire 
// body, so any exception thrown while lexing is caught here instead of crashing the program.
int main() try {
    while (std::cin) {
        print_next_token(std::cin);
        std::cout << std::endl;
    }
}

catch (std::exception const& e) {          // catch by const reference
    std::cerr << "Error: " << e.what() << std::endl;
    return -1;
}

catch (...) {
    std::cerr << "Unknown error" << std::endl;
    return -1;
}

// -------------------------------- Lexing Functions --------------------------------


// We will use helper functions for lexing and non-trivial symbols. The simpler ones will be
// handled in the print_next_token function itself.

void lex_name(std::istream& stream);
void lex_number(std::istream& stream);
void lex_operator(std::istream& stream);

// std::stream::get: stream.get(c) is a member function of std::istream objects (like std::cin). Its
// primary job is to read the next character from the input stream and store it in the variable c.
/*  
    char c;
    std::istream& stream = std::cin;
    stream.get(c);
*/


void print_next_token(std::istream& stream) {
    char c;

    // Skip whitespace. Write a loop where the body does not do anything (includes only a ;)
    // all the work is done in the condition. 'stream.get(c)' reads the next input character
    // into the variable c. and produces true only if the read was successful. '&&' short-circuits
    // the condition, so we stop as soon as we encounter a non-whitespace character or the
    // end of the stream/input is reached. When the loop ends, c holds the first non-whitespace
    // character from the input stream (if there is one).

    while (stream.get(c) && is_space(c))
        ;


    // The above loop ends either with a non-whitespace character or the end of the stream.
    // if end of stream is reached, we are done.
    if (!stream) {
        std::cout << " { end of file: \"\" }" << std::endl;
        return;
    }

    // single-character tokens are easy so handle them first here
    if (c == '(') { std::cout << "{ open_paren: \"(\" }" << std::endl; return; }
    if (c == ')') { std::cout << "{ close_paren: \")\" }" << std::endl; return; }

    // Otherwise, c is either an operator, or the start of a name or number. The lex_* functions
    // below re-read from the stream, but we have already read the first character into c.
    // 'unget()' is used to push the character back into the stream so that the lex_* functions
    // can read it again. (c is unchanged so we can test it below)


    // Note the stream.get(c) copies thr first character of the input stream into c AND moves 
    // stream's internal pointer forward by one character. That character is technically not
    // available for reading until we call unget() and move the pointer back. You want to 
    // remember that C++ streams are only guaranteed to remember the last character read.
    // So one cannot rely on the stream to remember more than the last character read.
    /*
        SO if you want to, say, print the first character of the input stream twice, you go:
        char c;
        std::istream& stream = std::cin;
        stream.get(c);
        std::cout << c;
        stream.unget();
        stream.get(c);
        std::cout << c << std::endl;
    */

    stream.unget();

    if (is_alpha(c))
        lex_name(stream);
    else if (is_digit(c))
        lex_number(stream);
    else if (is_operator(c))
        lex_operator(stream);
    else
        throw std::runtime_error("Unrecognized character");
}



// The three lexers below share one shape: keep reading chars while they belong
// to the token, then unget the one char that didn't fit. Only the predicate and
// the printed label differ. (We'll factor out the duplication later.)
 

void lex_name(std::istream& stream) {
    char c;
    std::string name;
    while(stream.get(c) && (is_alpha(c))){
        name.push_back(c);
    }
    if (stream)               // skip unget at end of file (nothing to put back)
        stream.unget();
    std::cout << "{ name: \"" << name << "\" }" << std::endl;
}

void lex_number(std::istream& stream) {
    char c;
    std::string number;
    while (stream.get(c) && is_digit(c)){
        number.push_back(c);
    }
    if (stream)               // skip unget at end of file (nothing to put back)
        stream.unget();
    std::cout << "{ number: \"" << number << "\" }" << std::endl;
}

void lex_operator(std::istream& stream) {
    char c;
    std::string op;
    while (stream.get(c) && is_operator(c))
        op.push_back(c);
    if (stream)
        stream.unget();
    // Operators are emitted as name tokens — the parser treats them the same.
    std::cout << "{ name: \"" << op << "\" }" << std::endl;
}




/* Next chapter: instead of printing tokens on sight, we give them a proper
 * in-program representation so we can store them in a vector and pass them
 * around. std::pair<std::string, std::string> would work, but C++ has a tidier
 * option. */


// We have seen how to fetch the tokens from the input stream and print them, but we have not seen how to store
// or return them.

// First of all, we would like to have a name for each token: open_paren_token, close_paren_token, number_token
// end_of_file_token. 

// Second, we want the tokens to have type. For an instance tok of a token, we want to be able to write tok.type
// to get the type of the token, and tok.value to get the value of the token (i.e. the string associated with it)

// --------------------------- NOW Continue to token.hpp --------------------------------

#include "lex.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

// Prints one token in a readable form, e.g.   { name_token, "foo" }
//
// 'Token const& tok': the & means we take a reference to the caller's Token rather than copying
// it (cheaper, and we don't need our own copy), and const means this function promises not to
// modify it.
void print_token(Token const& tok) {
    std::cout << "{ ";

    // tok.type is just a number (remember we defined them in token.hpp as 0,1,2,3,4), so we can
    // check which label it matches and prints a readable name for it. (This if/else chain is)
    // clunky; a later chapter replaces it with something nicer.)
    if (tok.type == open_paren_token)
        std::cout << "open_paren_token";
    else if (tok.type == close_paren_token)
        std::cout << "close_paren_token";
    else if (tok.type == name_token)
        std::cout << "name_token";
    else if (tok.type == number_token)
        std::cout << "number_token";
    else if (tok.type == end_of_file_token)
        std::cout << "end_of_file_token";

    std::cout << ", \"" << tok.value << "\" }\n";
}


int main() try{
    // A vector is a resizable list. std::vector<Token> means "a list of Tokens".
    std::vector<Token> tokens;

    // Keep pulling tokens from input and appending each one to the list.
    // push_back adds a single item to the end of the vector.

    while (std::cin)
        tokens.push_back(extract_next_token(std::cin));
    
    // std::for_each runs a function on every element in a range. The range is
    // given as a start and an end: tokens.begin() refers to the first element,
    // tokens.end() to just past the last. So this calls print_token on each
    // token in the vector, in order.
    std::for_each(tokens.begin() , tokens.end() , print_token);  
}

// This is a function-try-block: the try covers main's entire body, so if
// anything throws while lexing (such as an unrecognised character), we land
// here instead of crashing. Catching by `const&` is the standard form: we
// don't copy the exception, and we don't intend to modify it.
catch (std::exception const& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return -1;
}
catch (...) {
    std::cerr << "Unknown error.\n";
    return -1;
}



/* We can now work with tokens inside the program. Before rushing on to parsing,
 * the next chapters polish what we have: comparing tokens with == and !=,
 * reading/writing them with >> and <<, tidying up print_token, and finally a
 * proper explanation of the name::other_name syntax we keep using. */
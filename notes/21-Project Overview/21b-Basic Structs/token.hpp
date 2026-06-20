#ifndef TOKEN_HPP_CH21B
#define TOKEN_HPP_CH21B

#include <string>

// Let's start by defining the token types. We will make them int constants for now, but we will 
// eventually see a better solution. In regards to them being consts, there are two reasons for
// that: First, and most important, it does not make sense for these types to be modified?
// Second, making them constant allows us to define them in the header. If they were not consts
// but normal ints, this'd lead to double definition errors, but becasue the types are defined
// as constant, they are excluded from this rule and may be defined multiple times in different
// translation units. 

/*
    I want to reiterate that defining arbitray variables outside functions in your code is a sure
    way to make your whole project a tangled mess. Chances are that if you wanted to do this,
    the features of structs we'll be looking at shortly will provide a better solution.
*/

int const open_paren_token = 0;
int const close_paren_token = 1;
int const name_token = 2;
int const number_token = 3;
int const end_of_file_token = 4;


// ---------------------------------- The Token Types ------------------------------------
/*

    A `struct` lets us bundle several related variables together under one name.
    Here we bundle the two things that describe a token:
        - type:  which kind it is (one of the labels above)
        - value: the exact text it came from, e.g. "foo" or "24"

    
    Once we have this, if 'tok' is a Token, then 'tok.type' gives its kind and 'tok.value' gives
    its text. The '.' reaches into the struct to read one of its members. 

    Why is 'type' a plain 'int' and not 'int const', when the labels above are all const? The
    reason is we want to be able to copy one token into another (tok_a = toke_b), which overwrites
    tok_a members (here members being type and values). A const member can never be overwritten,
    so that assigment would be illegal. 

    The semicolon after the closing braces is necessary for a struct definition.
*/

struct Token {
    int type;
    std::string value;
};

/*
    Side note: a struct can be *declared* without being *defined*, like 'struct Token;'.
    That would only promise "a type called Token exists" without saying what's inside, so you
    couldn't create one or use its members yet. We want the full definition here because every
    .cpp file that works with Tokens need to know what members it has.

    Now continue to lex.hpp
*/




#endif
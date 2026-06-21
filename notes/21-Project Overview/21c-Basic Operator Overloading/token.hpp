#ifndef TOKEN_HPP_CH21C
#define TOKEN_HPP_CH21C

#include <string>
#include <istream>
#include <ostream>

/*
    This file defines the Token types (same as before) and now also *declares* four
    operators that work on Tokens. 

    What's new in this chapter: We teach C++ what ==, !=, >>, and << should mean for
    Tokens, so we can write things like tok_a == tok_b and std::cout << tok

    (Include-guard reminder: the #ifndef/#define/#endif stops this file's
    contents from being pasted in twice. We pull in <istream>/<ostream> because
    the operator declarations at the bottom mention std::istream/std::ostream.)
*/


// The five Token types as distinct integer tags (unchanges from last chapter).
int const open_paren_token = 0;
int const close_paren_token = 1;
int const name_token = 2;
int const number_token = 3;
int const end_of_file_token = 4;

// We define the Token using a struct which budles two of its attributes we care
// about: its value and its type 

struct Token {
    int type;
    std::string value;
};

 
/* --- Operator overloading ---
 *
 * In C++ an operator like == is really just a function with a special name:
 * `operator==`. "Overloading" it means writing our own version that says what
 * == should do when its operands are Tokens. The compiler then rewrites
 * `a == b` into a call to `operator==(a, b)`.
 *
 * You get less freedom than with a normal function -- you can't, for instance,
 * change how many operands == takes -- but the body can do anything a normal
 * function can.
 *
 * Because this is a header, we only *declare* the operators here (announce that
 * they exist); the actual code lives in token.cpp. These declarations let any
 * file that includes this header use ==, !=, >>, << on Tokens.
 *
 *   ==  : are two tokens equal?
 *   !=  : are two tokens different?
 *   >>  : read a token from an input stream   (e.g. std::cin >> tok)
 *   <<  : write a token to an output stream   (e.g. std::cout << tok)
 */


bool operator==(Token const& lhs , Token const& rhs);
bool operator!=(Token const& lhs , Token const& rhs);
std::istream& operator>>(std::istream& is , Token& tok);
std::ostream& operator<<(std::ostream& os , Token const& tok);

// Continue to token.cpp to see how each function is implemented. 
#endif
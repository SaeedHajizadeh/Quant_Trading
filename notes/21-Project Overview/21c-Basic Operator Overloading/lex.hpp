#ifndef LEX_HPP_CH21B
#define LEX_HPP_CH21B

#include "token.hpp"
#include<istream>

/*
    This is the lexer's "interface"--the list of what other files are allowed to use from it.
    It says: there is a function called extract_next_token that takes an input stream and gives
    back one Token.

    Note the two #include styles:
        #include "token.hpp"  -- quotes: one of our own files, looked for nearby
        #include <istream>    -- angle brackets: a standard library header

    We need token.hpp because this file mentions Token, and <istream> because it mentions
    std::istream.

*/

// extract_next_token reads one token from the stream and returns it. The previous chapter
// printed the read tokens directly; now it hands it back to the caller so the caller can store
// it instead.
//
// 'std::istream& stream': As stated before, the & means "reference". The function works on the 
// caller's actual stream, not a copy, so reading inside it advances the real input (and streams
// cannot be copied anyway).
// The other lexer helpers (lex_name, lex_number, lex_operator) are internal details, so we
// deliberately leave them out of this header. Only the things other files should be able to call 
// belong in the interface.

Token extract_next_token(std::istream& stream);

// NOW move to lex.cpp

#endif
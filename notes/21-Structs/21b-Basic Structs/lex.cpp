#include "lex.hpp"
#include <cctype>
#include <stdexcept>

/*

    This file is the lexer's "implementation" -- the actual code behind the function promised in
    lex.hpp. It reads characters from a stream and builds Tokens out of them.

    It is almost identical to previous chapter's code, with one change: instead of printing each
    token, we now build Token and 'return' it. 

*/

// We are making, as before, three helper functions, one per multi-character token kind. They are
// declared here (not in the lex.hpp) because nothing outside this file needs to call them. 

Token lex_name(std::istream& stream);
Token lex_number(std::istream& stream);
Token lex_operator(std::istream& stream);

// True if c is one of the characters an operator can be built from. 
bool isoperator(char c) {
    // 'static' here means the string is built "once" on the first call and then reused on later
    // calls , instead of being recalled every single time
    static std::string const valid_operators = "+*-/!=<>";

    // As stated before, std::string.find(c) returns the first position of c within the string,
    // or the special value std::string::npos if c is not in it. So "result is no npos" means
    // "found".
    return valid_operators.find(c) != std::string::npos;
}

Token extract_next_token(std::istream& stream) {
    char c;

    // Skip past any whitespace. std::isspace(c) (from <cctype>) answers "is c a space, tab
    // , newline, etc.?". The loop body is empty (just the ';'): all the work is in the condition.
    // stream.get(c) reads one character into c and is true only if it succeeded; && stops as soon
    // as either part is false. So we keep reading while we get whitespace, and the loop ends with
    // c holding the first non-space character (if there was one).
    while (stream.get(c) && std::isspace(static_cast<unsigned char>(c)));
    
    // No more input: hand back an end-of-file token.
    //
    // {end_of_file_token, ""} builds a Token right here. The compiler already
    // knows this function returns a Token, so we don't have to write the type
    // name. The values fill the members in declaration order: type gets
    // end_of_file_token, value gets the empty string "".
    if (!stream)
        return {end_of_file_token , ""};

    // The two single-character tokens are easy.
    if (c == '(')
        return {open_paren_token , "("};
    if (c == ')')
        return {close_paren_token , ")"};
    
    // Otherwise c starts a name, number, or operator. The helpers below re-read
    // from the stream, but we have already pulled c out of it. unget() puts that
    // one character back so the helper sees the whole token.
    stream.unget();

    // std::isalpha(c) -> "is c a letter?"; std::isdigit(c) -> "is c a digit?".
    // (Same unsigned char cast as above, for the same reason.)
    if (std::isalpha(static_cast<unsigned char>(c)))
        return lex_name(stream);
    if (std::isdigit(static_cast<unsigned char>(c)))
        return lex_number(stream);
    if (isoperator(c))
        return lex_operator(stream);

    // None of the above: the input contains a character we don't understand.
    throw std::runtime_error{"unrecognized character"};
}

// The three helpers share the same shape: keep collecting characters while they
// still belong to the token, put back the one character that doesn't, then
// return the finished Token. push_back adds one character to the end of a string.

Token lex_name(std::istream& stream){
    char c;
    std::string name;

    while (stream.get(c) && std::isalpha(static_cast<unsigned char>(c)))
        name.push_back(c);
    
    if (stream)               // at end of file there is nothing to put back
        stream.unget();
    
    return {name_token , name};
}


Token lex_number(std::istream& stream) {
    char c;
    std::string number;
    while (stream.get(c) && std::isdigit(static_cast<unsigned char>(c)))
        number.push_back(c);
 
    if (stream)
        stream.unget();
 
    return {number_token, number};
}
 
Token lex_operator(std::istream& stream) {
    char c;
    std::string op;
    while (stream.get(c) && isoperator(c))
        op.push_back(c);
 
    if (stream)
        stream.unget();
 
    // An operator is returned as a name_token -- the rest of the program treats
    // names and operators the same.
    return {name_token, op};
}


 
/* Now that the lexer hands back Tokens, head back to main.cpp to see them
 * collected into a vector. */
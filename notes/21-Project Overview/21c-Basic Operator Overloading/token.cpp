
/* This file *implements* the four operators declared in token.hpp.
 *
 * Why include BOTH headers here? Because token and lex are each split into a
 * header (declarations) and a source file (definitions), any .cpp can include
 * both headers in either order and it just works. If we hadn't split them this
 * way, we'd have to fuss over include order so that everything was declared
 * before it was used. (Try merging them into one file and you'll hit exactly
 * that problem.)
 */


#include "token.hpp"
#include "lex.hpp"

 
/* Each definition below is just a function with a funny name: `operator==` is
 * the function the compiler calls when it sees `a == b`. `lhs` and `rhs` are the
 * conventional names for the left-hand-side and right-hand-side operands.
 *
 * We take the operands as `Token const&`: by reference so they aren't copied,
 * and const because comparing or printing a token shouldn't change it.
 */


// Two tokens are equal when BOTH their kind and their text match.
// && means "and"; its right side is only checked if the left side is true.

bool operator==(Token const& lhs , Token const& rhs) {
    return lhs.type == rhs.type && lhs.value == rhs.value;
}

bool operator!=(Token const& lhs , Token const& rhs) {
    return !(lhs == rhs);
}


/*
    operator>> reads a Token from an input stream, so we can write 'std::cin >> tok'.

    It returns the stream by reference, and that return is what lets reads be chained:
    in 'std::cin >> a >> b', the first >> returns the stream so the second >> has
    something to read from. 
    
    'tok' is taken by plain reference (not const): we are filling it in so we must be
    able to change it. Rather than re-implement the lexing, we reuse 
    extract_next_token. The `if (is)` guard skips the read when the stream has
    already failed, leaving tok untouched.
*/

std::istream& operator>>(std::istream& is , Token& tok) {
    if (is)
        tok = extract_next_token(is);
    return is;
}


/* 
 * operator<< writes a Token to an output stream, so we can write
 * `std::cout << tok`. It also returns the stream by reference, which is what
 * lets us chain output like `std::cout << tok << "\n"`.
 *
 * For now it just prints the token's text (value). We could reuse the richer
 * print_token format instead, but >> and << are usually expected to be
 * symmetric -- what you write with << should read back with >>. A later chapter
 * brings a better lexer, and at that point we'll give << a nicer, more
 * debugging-friendly form.
 */
std::ostream& operator<<(std::ostream& os , Token const& tok) {
    os << tok.value;
    return os;
}
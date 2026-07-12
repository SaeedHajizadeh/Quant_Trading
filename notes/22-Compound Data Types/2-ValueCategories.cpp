// -------------------------  lvalue references --------------------------------
// Before talking about lvalue references, let's talk about lvalues
// In C++, an *expression* is defined as “a combination of literals, variables, operators,
// and function calls that can be executed to produce a singular value”.
// e.g. 2 + 3 (which evaluates to 5) or ++x (which evaluates to x + 1)

// All expressions in C++ have two properties: (i) the type and (ii) the value category
// Type of an expression is the type of the value the expression is evaluated to

// In order to understabd value category, conside the following program
/*
int main() {
    int x {};

    x = 5;    // legal
    5 = x;    // illegal; we cannot assign the value of x to literal value 5

    return 0;
}
*/

// How does the compiler know which expressions can legally appear on either side of
// an assignment statement? The answer lies in value category
// The value category of an expression (or subexpression) indicates whether an expression
// resolves to a value, a function, or an object of some kind.

// Prior to C++11, there were only two possible value categories: lvalue and rvalue
// In C++11, three additional value categories, i.e. gvalue, xvalue, and pvalue, were added
// to supprt a new feature called "move semantics".

// In this chapter we only look at pre-C++11 view of value categories. We will cover move semantics
// and the additional value categories later.

// ---------------------------------------- Lvalue -------------------------------------------
// An lvalue (pronounced “ell-value”, short for “left value” or “locator value”, and sometimes
// written as “l-value”) is an expression that evaluates to an identifiable object or function
// (or bit-field). The classic definition of an lvalue is: an expression that refers to a
// specific memory location.
/*
x = 5;   // x is an lvalue
*/
// In other words, if you take something's address with an & sign, it is then an lvalue
// If you cannot, it is called an rvalue

// Examples of lvalues
/*
int x;
x          // a named variable
*ptr       // dereferenced pointer
arr[i]     // array subscript
++x        // pre-increment returns an lvalue
*/

// Since the introduction of constants into the language, lvalues come in two subtypes:
// a modifiable lvalue is an lvalue whose value can be modified. A non-modifiable lvalue is an
// lvalue whose value can’t be modified (because the lvalue is const or constexpr).
// Example
/*
int main()
{
    int x{};
    const double d{};

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression

    return 0;
}
*/



// --------------------------------------- rvalue ------------------------------------------
// Rvalue expressions evaluate to a value. Moreover, you cannot take their address because they
// do not have any address on the memeory. More formally stated, Rvalues aren’t identifiable
// (meaning they have to be used immediately), and only exist within the scope of the expression
// in which they are used. 


/*
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
*/

// You may be wondering why return5(), x + 1, and static_cast<int>(d) are rvalues: the answer is
// because these expressions produce temporary values that are not identifiable objects.


// Briefly speaking, an rvalue is a temporary value that does not have a persistent memory address.
// It is typically used in expressions where the value is needed for a short duration and does
// not need to be stored or referenced later. In other words:
// Lvalue expressions evaluate to an identifiable object.
// Rvalue expressions evaluate to a value.

// ----------------------------------- value categories ------------------------------------
// Unless otherwise stated, operators in C++ expect their operands to be rvalues.
// For example, operator+ expects its operands to be rvalues and returns an rvalue. 

// An assignment operator expects its left operand to be an lvalue so 5 = x is illegal. It also
// expects the right operand to be an rvalue, so x = 5 is legal. However, the expression y = x
// is also legal (if x is defined already) because the lvalue on the right side will go under
// an lvalue-to-rvalue conversion, so that the assignment operation is legal. 



// ****** how to differentiate between lvalues and rvalues ********
// A rule of thumb to identify lvalue and rvalue expressions:

// Lvalue expressions are those that evaluate to functions or identifiable objects
// (including variables) that persist beyond the end of the expression.

// Rvalue expressions are those that evaluate to values, including literals and temporary
// objects that do not persist beyond the end of the expression.

// Finally, we can write a prog. and have the compiler tell us what kind of expression something is. 
#include <iostream>
#include <string>

// T& is an lvalue reference, so this overload will be preferred for lvalues
// recall we create a template T as a placeholder for any type (int, double, std::string, etc.)
// What this template does here is it takes a reference to T and returns true if the expression 
// is an lvalue, and false if it is an rvalue.

// another thing to notice: 
// T& is a reference to a type T, that binds to lvalue ONLY
// T&& is a reference to a type T, that binds to rvalue ONLY
/*
int x = 5;

int&  a = x;    // ✅ x is an lvalue
int&  b = 5;    // ❌ 5 is an rvalue — error, as you know

int&& c = 5;    // ✅ 5 is an rvalue — this is what && is for
int&& d = x;    // ❌ x is an lvalue — error! && refuses lvalues
*/


template <typename T>
constexpr bool is_lvalue(T&)
{
    return true;
}

// T&& is an rvalue reference, so this overload will be preferred for rvalues
template <typename T>
constexpr bool is_lvalue(T&&)
{
    return false;
}

// A helper macro (#expr prints whatever is passed in for expr as text)
#define PRINTVCAT(expr) { std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n"); }

int getint() { return 5; }

int main()
{
    PRINTVCAT(5);        // rvalue
    PRINTVCAT(getint()); // rvalue
    int x { 5 };
    PRINTVCAT(x);        // lvalue
    PRINTVCAT(std::string {"Hello"}); // rvalue
    PRINTVCAT("Hello");  // lvalue
    PRINTVCAT(++x);      // lvalue
    PRINTVCAT(x++);      // rvalue
}
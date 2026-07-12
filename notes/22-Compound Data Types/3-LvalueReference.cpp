// In C++, a "reference" is an alias for an existing object.
// Following the definition of an alias, any operation performed on the reference is actually
// applied to the original object being referenced. 

// Modern C++ has two types of references: lvalue references and rvalue references.
// In this code snippet, we focus on the lvalue reference.

// An lvalue reference is a reference that can only bind to an lvalue.
// value reference types can be identified by use of a single ampersand (&) in the type specifier:
// regular types
/*
int        // a normal int type (not an reference)
int&       // an lvalue reference to an int object
double&    // an lvalue reference to a double object
const int& // an lvalue reference to a const int object
*/
// So int& is the type of an lvalue reference to an int object etc
// const int& is the type of an lvalue reference to a const int object etc

// An "lvalue reference variable" is a variable that is declared to be an lvalue reference type.
/*
#include <iostream>

int main() {
    int x { 5 }; // x is an int object
    int& ref { x }; // ref is an lvalue reference variable that can be used as an alias for x

    std::cout << x << std::endl; // prints the value of x, which is 5
    std::cout << ref << std::endl; // prints the value of x via ref which is 5
    return 0;
}
*/



// From the compiler’s perspective, it doesn’t matter whether the ampersand is “attached” to
// the type name (int& ref) or the variable’s name (int &ref), and which you choose is a matter
// of style. Modern C++ programmers tend to prefer attaching the ampersand to the type, as it
// makes clearer that the reference is part of the type information, not the identifier.

// ---------------- Modifying values through nonconstant lvalue reference ----------------
/*
#include <iostream>

int main()
{
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
*/


// -------------------------------- Reference utilization --------------------------------
// Much like constants, all references must be initialized. References are initialized using
// a form of initialization called reference initialization.
/*
int main()
{
    int& invalidRef;   // error: references must be initialized

    int x { 5 };
    int& ref { x }; // okay: reference to int is bound to int variable

    return 0;
}
*/

// When a reference is initialized with an object (or function), we say it is bound to that
// object (or function). The process by which such a reference is bound is called reference
// binding. The object (or function) being referenced is sometimes called the referent.

// **** nonconstant lvalue references can only bind to nonconstant lvalues ****
/*
int main()
{
    int x { 5 };
    int& ref { x };         // okay: non-const lvalue reference bound to a modifiable lvalue

    const int y { 5 };
    int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
    int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue

    return 0;
}
*/


// Once initialized, a reference in C++ cannot be reseated, meaning it cannot be changed to
// reference another object. If you attempt to reseat a reference, the compiler will run but not
// function as you expect. 

/*

The program below runs well and the output is 6
#include <iostream>

int main()
{
    int x { 5 };
    int y { 6 };

    int& ref { x }; // ref is now an alias for x

    ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
    // The above line does NOT change ref into a reference to variable y!

    std::cout << x << '\n'; // user is expecting this to print 5

    return 0;
}
*/

// ----------------------------- Reference Scope -----------------------------
// Reference variables follow the same scoping and duration rules that normal variables do:
/*
#include <iostream>

int main()
{
    int x { 5 }; // normal integer
    int& ref { x }; // reference to variable value

     return 0;
} // x and ref die here
*/



// ----------------------------- Lvalue Reference to Constant -----------------------------
// A reference to a constant is a reference that cannot be used to modify the object being
// referenced. A reference to a constant is declared by placing the const keyword before the
// type name in the reference declaration. 
/*
int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    return 0;
}
*/


/*
#include <iostream>

int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    std::cout << ref << '\n'; // okay: we can access the const object
    ref = 6;                  // error: we can not modify an object through a const reference

    return 0;
}
*/


// Lvalue references to const can also bind to modifiable lvalues. In this situation, the reference
// can be used to access the object, but not to modify it. However, the object itself can still be
// modified through other means, such as through another non-constant reference or through the
// original variable itself.
/*
#include <iostream>

int main()
{
    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

    std::cout << ref << '\n'; // okay: we can access the object through our const reference
    ref = 7;                  // error: we can not modify an object through a const reference

    x = 6;                // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    return 0;
}
*/



// *** initializing a const lvalue reference to an lvalue of a different type ***
/*
#include <iostream>

int main()
{
    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

    std::cout << r1 << '\n'; // prints 5

    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary

    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    return 0;
}
*/ 


// In case 2, a temporary object of type int is created and initialized with char value a.
// Then const int& r2 is bound to that temporary int object.

// Temporary objects die at the end of the expression in which they are created. If we use
// a const lvalue reference to bind to a temporary object, the lifetime of the temporary is
// extended to match the lifetime of the reference. This is a special rule in C++ that
// allows us to avoid having dangling references to destroyed temporary objects. 
/*
#include <iostream>

int main()
{
    const int& ref { 5 }; // The temporary object holding value 5 has its lifetime extended to match ref

    std::cout << ref << '\n'; // Therefore, we can safely use it here

    return 0;
} // Both ref and the temporary object die here
*/




// ---------------------------- What makes a reference useful? ----------------------------
// Why not simply using the lvalue itself? 
// Let's introduce "pass by reference" and "pass by value" to answer this question.
// Pass by value is when a full copy of the argument is made and passed (,say, to the function)
// Pass by reference is when a reference to the memory address of the argument is passed (, say,
// to the function). The latter is more efficient, especially for large objects, as it avoids
// the overhead of copying the entire object. Additionally, pass by reference allows functions
// to modify the original argument, while pass by value does not. This is particularly useful
// when we want to change the state of an object or when we want to return multiple values
// from a function.)

// Most of the types provided by the standard library (such as std::string) are class types.
// Class types are usually expensive to copy. Whenever possible, we want to avoid making
// unnecessary copies of objects that are expensive to copy, especially when we will destroy
// those copies almost immediately.

/*
#include <iostream>
#include <string>

void printValue(std::string y)
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" }; // x is a std::string

    printValue(x); // x is passed by value (copied) into parameter y (expensive)

    return 0;
}
*/


// While this program behaves like we expect, it’s also inefficient. When printValue() is called,
// argument x is copied into printValue() parameter y. However, in this example, the argument is
// a std::string instead of an int, and std::string is a class type that is expensive to copy.
// And this expensive copy is made every time printValue() is called!

// ----------------------------- Pass by reference ----------------------------
// Here is an example of how we can use a reference to avoid the overhead of copying an expensive
// object

/*
#include <iostream>
#include <string>

void printValue(std::string& y) // type changed to std::string&
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" };

    printValue(x); // x is now passed by reference into reference parameter y (inexpensive)

    return 0;
}
*/


// This program is identical to the prior one, except the type of parameter y has been changed
// from std::string to std::string& (an lvalue reference). Now, when printValue(x) is called,
// lvalue reference parameter y is bound to argument x. Binding a reference is always inexpensive,
// and no copy of x needs to be made. 

// The following program demonstrates that a value parameter is a separate object from the
// argument, while a reference parameter is treated as if it were the argument:

/*
#include <iostream>

void printAddresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
}

int main()
{
    int x { 5 };
    std::cout << "The address of x is: " << &x << '\n';
    printAddresses(x, x);

    return 0;
}
*/

// Output:
/*
The address of x is: 0x7ffd16574de0
The address of the value parameter is: 0x7ffd16574de4
The address of the reference parameter is: 0x7ffd16574de0
*/

// Pass by reference allows us to change the value of an argument
// When an object is passed by value, the function parameter receives a copy of the argument.
// This means that any changes to the value of the parameter are made to the copy of the argument,
// not the argument itself:
/*
#include <iostream>

void addOne(int y) // y is a copy of x
{
    ++y; // this modifies the copy of x, not the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has not been modified

    return 0;
}
*/

// However, since a reference acts identically to the object being referenced, when using pass
// by reference, any changes made to the reference parameter will affect the argument:

/*.
#include <iostream>

void addOne(int& y) // y is bound to the actual object x
{
    ++y; // this modifies the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has been modified

    return 0;
}
*/



/* 
                              ********************************* 
Passing values by reference to non-const allows us to write functions that modify the value
of arguments passed in.
                              ********************************* 
*/





/* 
                              ********************************* 
Pass by reference can only accept modifiable lvalue arguments
                              ********************************* 
*/

/*

#include <iostream>

void printValue(int& y) // y only accepts modifiable lvalues
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printValue(x); // ok: x is a modifiable lvalue

    const int z { 5 };
    printValue(z); // error: z is a non-modifiable lvalue

    printValue(5); // error: 5 is an rvalue

    return 0;
}
*/





// -------------------------------- Pass by reference to const --------------------------------
// A reference to a constant can be used to pass an argument

// Unlike a reference to non-const (which can only bind to modifiable lvalues), a reference to
// const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues. Therefore, if we
// make a reference parameter const, then it will be able to bind to any type of argument:

/*
#include <iostream>

void printRef(const int& y) // y is a const referece
{
    std::cout << y << std::endl;
}

int main()
{
    int x { 5 };
    printRef(x); // okay: x is a modifiable lvalue

    const int z { 5 };
    printRef(z); // okay: z is a non-modifiable lvalue

    printRef(5); // okay: 5 is an rvalue
    return 0;
}
*/



// Passing by const reference offers the same primary benefit as pass by non-const reference
// (avoiding making a copy of the argument), while also guaranteeing that the function can not
// change the value being referenced.

/*
void addOne(const int& ref)
{
    ++ref; // not allowed: ref is const
}
*/


/*
                ********************************************************************
    Best practice:
    Favor passing by const reference over passing by non-const reference unless you have a
    specific reason to do otherwise (e.g. the function needs to change the value of an argument).
                ********************************************************************
*/

// Mixing pass by vallue, pass by reference, and pass by const reference in a single function

/*
#include <string>

void foo(int a, int& b, const std::string& c)
{
}

int main()
{
    int x { 5 };
    const std::string s { "Hello, world!" };

    foo(5, x, s);

    return 0;
}
*/



// When to pass by value, pass by reference, or pass by const reference?
//                                  best practice: 
// As a rule of thumb, pass fundamental types by value and class types by const reference. If
// you aren’t sure what to do, pass by const reference, as you’re less likely to encounter
// unexpected behavior.
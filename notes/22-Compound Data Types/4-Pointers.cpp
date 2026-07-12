// Pointers behave a lot like lvalue reference so if you are rusty go look at 
// 3-LvalueReferences.cpp


// the variable char c {}; utilizes 1 byte of memory
// Simplifying a bit, when the code generated for this definition is executed, a piece of memory
// from RAM will be assigned to this object. For the sake of example, let’s say that the variable
// x is assigned memory address 140. Whenever we use variable x in an expression or statement,
// the program will go to memory address 140 to access the value stored there.

// Nice thing is we do not need to know the memory address of x to use it. However, the compiler
// allows us to access the memory address of a variable using the address-of operator (&).

/*
#include <iostream>

int main() {
    char c {};

    std::cout << "Address of c: " << &c << std::endl; // prints the address of c

    int x { 5 };
    std::cout << "Value of x: " << x << std::endl; // prints the value of x
    std::cout << "Address of x: " << &x << std::endl; // prints the address of x
    return 0;
}
*/


// For objects that use more than one byte of memory, address-of will return the memory
// address of the first byte used by the object.

/*
The & symbol tends to cause confusion because it has different meanings depending on context:
1. When following a type name, & denotes an lvalue reference: int& ref.
2. When used in a unary context in an expression, & is the address-of operator: std::cout << &x.
3. When used in a binary context in an expression, & is the Bitwise AND operator: std::cout << x & y.
*/

// --------------------------------- deference operator (*) ---------------------------------
// We have seen how the dereference operator (*) can be used to refer to the value associated
// with an iterator when we use the iterator in accessing elements of a container such as 
// std::vector. 
// We can also use the dereference operator to access the value that is stored at a particular
// memory address. 
// The dereference operator returns the value at a given memory address as an *** lvalue ***.

/*
#include <iostream>

int main() {
    int x { 5 };
    std::cout << "Value of x: " << x << std::endl; // prints the value of x
    std::cout << "Address of x:" << &x << std::endl; // prints the address of x

    std::cout << "Value at the address of x: " << *(&x) << std::endl;

    // address-of operator and dereference operator are inverses of each other
    std::cout << &*&x << std::endl; // prints the address of x
    return 0;
}
*/



// --------------------------------- Pointers ---------------------------------
// **** A pointer is an object that stores a memory address (of another variale) as its value. ****
// **** A type that specifies a pointer (e.g. int*) is called a pointer type. ****
// Reference types are declared using an ampersand (&); 
// Pointer types are declared using an asterisk (*).

/*
int;  // a normal int
int&; // a reference to an int
int*; // a pointer to an int value (holds the address of an integer value)
*/

// define a pointer variable:
/*
#include <iostream>

int main() {
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is an lvalue reference to x

    int* ptr {&x}; // ptr to an integer variable, initialized with the address of x
    return 0;
}

*/


// Best practice: When declaring a pointer type, place the asterisk next to the type name.

// Like normal variables, pointers are not initialized by default.
// A pointer that has not been initialized is sometimes called a wild pointer. Wild pointers
// contain a garbage address, and dereferencing a wild pointer will result in undefined behavior.
// Because of this, you should always initialize your pointers to a known value.

// ***** Best Practice: always initialize your pointers to a known value *******
/*
#include <iostream>

int main() {
    int x { 5 }; // normal integer variable

    int* ptr; // uninitialized pointer to an integer variable (holds a garbage address)
    int* prt {}; // a null pointer to an integer variable (We will talk about this)
    int* ptr {&x}; // a pointer to an integer variable, initialized with the address of x
    return 0;
}
*/


// When we initialize a value to a pointer, the value has to be an address
// As stated before, once we have a pointer that points to the address of another variable, we
// get the value of that variable using a dereference operator (*).

/*
# include <iostream>

int main() {
    int x { 5 }; // normal integer variable
    std::cout << "Value of x: " << x << std::endl; // prints the value of x

    int* ptr {&x}; // a pointer to an integer variable, initialized with the address of x
    std::cout << "Value of ptr: " << ptr << std::endl; // address of x
    std::cout << "Value at the address of ptr: " << *ptr << std::endl; // prints the value of x
    std::cout << "Address of ptr: " << &ptr << std::endl; // prints the address of ptr
    std::cout << "Value of ptr: " << *&ptr << std::endl; 
    return 0;
}
*/


/*
A note on pointer nomenclature: “X pointer” (where X is some type) is a commonly used shorthand
for “pointer to an X”. So when we say, “an integer pointer”, we really mean “a pointer to an
integer”. This understanding will be valuable when we talk about const pointers.
*/


// Much like the type of a reference has to match the type of the object being referenced, the
// type of a pointer has to match the type of the object being pointed to.

/*
int main()
{
    int i{ 5 };
    double d{ 7.0 };

    int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
    int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double object
    double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
    double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int object

    return 0;
}
*/


// With one exception, initialization of a pointer with a literal value is not allowed. 
// The exception is the null pointer literal.

/*
int* ptr{ 5 }; // not okay
int* ptr{ 0x0012FF7C }; // not okay, 0x0012FF7C is treated as an integer literal
*/

// -------------------------------- Pointers and assignments --------------------------------
// We can use assignment with pointers in two different ways
// 1. To change what the pointer is pointing at (by assigning the pointer a new address)
// 2. To change the value being pointed at (by assigning the dereferenced pointer a new value)

// Case 1.
/*
#include <iostream>
int main() {
    int x { 5 };
    int* ptr { &x }; // ptr points to x

    std::cout << *ptr << std::endl; // value at the address being pointed to (x's address)

    int y { 10 };
    ptr = &y;   // change ptr to now point at y

    std::cout << *ptr << std::endl; // value at the address being pointed to (y's address)
    
    return 0;
}
*/



// Case 2.

/*
#include <iostream>

int main() {
    int x { 5 };
    int* ptr { &x }; // ptr points to x

    std::cout << x << std::endl; // prints the value of x
    std::cout << *ptr << std::endl; // value at the address being pointed to (x's address)

    *ptr = 22; // change the value at the address being pointed to (x's address)

    std::cout << x << std::endl; // prints the value of x
    std::cout << *ptr << std::endl; // value at the address being pointed to (x's address)

    return 0;
}

*/


// ******** Pointers behave much like the lvalue reference *********

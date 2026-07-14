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
/*
#include <iostream>

int main()
{
    int x{ 5 };
    int& ref { x };  // get a reference to x
    int* ptr { &x }; // get a pointer to x

    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (5)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

    ref = 6; // use the reference to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (6)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

    *ptr = 7; // use the pointer to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (7)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (7)

    return 0;
}
*/


// Difference between pointers and references:
// 1. References must be initialized, pointers are not required to be initialized (but should be).
// 2. References are not objects, pointers are.
// 3. References can not be reseated (changed to reference something else), pointers can change
//    what they are pointing at.
// 4. References must always be bound to an object, pointers can point to nothing (we’ll see
//    an example of this in the next lesson).
// 5. References are “safe” (outside of dangling references), pointers are inherently dangerous
//    (we’ll also discuss this in the next lesson).




// It is important to note that the address-of operator (&) returns the address of its operand
// as a pointer, and NOT as a literal (C++ does not support address literals). So it returns a 
// pointer whose value is the address of its operand. 

/*
#include <iostream>
#include <typeinfo>

int main() {
    int x { 5 };
    std::cout << typeid(x).name() << std::endl; // prints the type of x
    std::cout << typeid(&x).name() << std::endl; // type of the address of x

    return 0;
}
*/

// Using g++, the result prints as i and Pi


// ****************** Note that the size of a pointer on a 32-bit machine is 4 Bytes and
// ****************** the size of a pointer in a 64-bit machine is 8 Bytes (64 bits)

/*
// The following code assumes a 64-bit machine
#include <iostream>

int main() {
    int x { 5 };
    int* ptr {&x};

    int* ptr_n1 {};
    char* ptr_n2 {};
    long double ptr_n3 {};

    std::cout << sizeof(ptr) << std::endl;      // 8

    std::cout << sizeof(ptr_n1) << std::endl;   // 8
    std::cout << sizeof(ptr_n2) << std::endl;   // 8
    std::cout << sizeof(ptr_n3) << std::endl;   // 16

    return 0;
}
*/




// ------------------------------ Dangling Pointer --------------------------------
// Much like a dangling reference, a dangling pointer is a pointer that is holding the address of
// an object that is no longer valid (e.g. because it has been destroyed). Dereferencing a
// dangling pointer (e.g. in order to print the value being pointed at) will lead to undefined
// behavior, as you are trying to access an object that is no longer valid.



/*
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x };

    std::cout << *ptr << '\n'; // valid

    {
        int y{ 6 };
        ptr = &y;

        std::cout << *ptr << '\n'; // valid
    } // y goes out of scope, and ptr is now dangling

    
    std::cout << *ptr << '\n'; // undefined behavior from dereferencing a dangling pointer

    return 0;
}
*/




// --------------------------------- Null Pointers -----------------------------------------
// When a pointer holds not an address, but a null value, it means it is not pointing to anything
// Such a  pointer is called a null pointer

/*
int main()
{
    int* ptr {}; // ptr is now a null pointer, and is not holding an address

    return 0;
}
*/


// **** Best Practice **** initialize your pointers with a null value if you are not initializing
// then with the address of an object

// A pointer that is set to null, can later be changed to point at a valid object. Such 
// flexibility is not available for references as they can not be reseated to refer to a
// different object.


// ---------------------------------- The nullptr keyword -----------------------------
// Much like the keywords true and false are Bolean literal values, the nullptr keywords
// represents a null pointer literal. We can use nullptr to explicitly initialize or assign
// a pointer to a null value. It can also be used to check if a pointer is a null pointer
/*
int* ptr = nullptr;

if (ptr == nullptr) {
    std::cout << "No object\n";
}
*/


// Best practice: Use nullptr when you need a null pointer literal for initialization,
// assignment, or passing a null pointer to a function.

// Much like dereferencing a dangling (or wild) pointer leads to undefined behavior, 
// dereferencing a null pointer leads to undefined behavior as well.

// #include <iostream>

// int main()
// {
//     int* ptr {}; // Create a null pointer
//     std::cout << *ptr << '\n'; // Dereference the null pointer

//     return 0;
// }



/*
                          ********************************************
    Accidentally dereferencing null and dangling pointers is one of the most common mistakes
    C++ programmers make, and is probably the most common reason that C++ programs crash in
    practice.

                          ********************************************
*/


// As stated before, much like true and false, we cam sey conditionals to assess if something
// is a null pointer

/*
#include <iostream>

int main() {
    int x { 5 };
    int* ptr { &x };

    if (ptr == nullptr)
        std::cout << "ptr is null.\n";
    else
        std::cout << "ptr is non-null.\n";

    int* nullPtr {};
    // explicit test for equivalence
    std::cout << "nullPtr is " << (nullPtr == nullptr ? "null\n" : "non-null\n");

    return 0;
}
*/

// This last line is ternary operator in C++ having the general form of the following:
// condition ? expression_if_true : expression_if_false;


// Similarly, pointers will also implicitly convert to Boolean values: a null pointer
// converts to Boolean value false, and a non-null pointer converts to Boolean value true.
// This allows us to skip explicitly testing for nullptr and just use the implicit conversion
// to Boolean to test whether a pointer is a null pointer. 

/*
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    // pointers convert to Boolean false if they are null, and Boolean true if they are non-null
    if (ptr) // implicit conversion to Boolean
        std::cout << "ptr is non-null\n";
    else
        std::cout << "ptr is null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n"); // implicit conversion to Boolean

    return 0;
}
*/



// Avoid dereferencing a null pointer: check for nullptr before dereferencing
/*
// Assume ptr is some pointer that may or may not be a null pointer
if (ptr) // if ptr is not a null pointer
    std::cout << *ptr << '\n'; // okay to dereference
else
    // do something else that doesn't involve dereferencing ptr (print an error message,
    do nothing at all, etc...)
*/

// Unfortunately, avoiding dangling pointers isn’t always easy: when an object is destroyed,
// any pointers to that object will be left dangling. Such pointers are not nulled automatically!
// It is the programmer’s responsibility to ensure that all pointers to an object that has just
// been destroyed are properly set to nullptr.






// Additionally, there is a preprocessor macro named NULL (defined in the <cstddef> header).
// This macro is inherited from C, where it is commonly used to indicate a null pointer.
/*

#include <cstddef>  // for NULL macro
int main() {
    double* ptr { NULL }; // ptr is a null  pointer
    double* ptr2;         // ptr2 is uninitialized

    ptr2 = NULL;          // ptr2 is a now a null pointer
    return 0;
}
*/



// ************************ AVOID NULL -- USE nullptr instead *****************************





// ***** Favor references over pointers whenever possible *******
// Pointers and references both give us the ability to access some other object indirectly. 
// Pointers have the additional abilities of being able to change what they are pointing at,
// and to be pointed at null. However, these pointer abilities are also inherently dangerous:
// A null pointer runs the risk of being dereferenced, and the ability to change what a pointer
// is pointing at can make creating dangling pointers easier:

/*
int main()
{
    int* ptr { };

    {
        int x{ 5 };
        ptr = &x; // assign the pointer to an object that will be destroyed (not possible with a reference)
    } // ptr is now dangling and pointing to invalid object

    if (ptr) // condition evaluates to true because ptr is not nullptr
        std::cout << *ptr; // undefined behavior

    return 0;
}
*/



// ----------------------------- Pointers and const ------------------------------------
// Consider the following program

/*
int main() {
    const int x { 5 };
    int* ptr { &x };       // raises an error

    return 0;
}
*/


// The reason is that we can change the value at the address a non-const pointer is pointing at
// and if the pointer is pointing at the address in which a const variable is stored, that
// cannot work.

// A pointer to a const value (sometimes called a pointer to const for short) is a
// (non-const) pointer that points to a constant value. To declare a const pointer, use
// the keyword const before the type T* of a pointer

/*
#include <iostream>
int main(){
    const int x { 5 };
    const int* ptr { &x }; // ptr points to const int x

    const int y { 15 };
    ptr = &y;              // okay: ptr now points at const int y

    return 0;
}

*/



// Just like a reference to const, a pointer to const can point to non-const variables too.
// A pointer to const treats the value being pointed to as constant, regardless of whether
// the object at that address was initially defined as const or not:
/*
int main()
{
    int x{ 5 }; // non-const
    const int* ptr { &x }; // ptr points to a "const int"

    *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
    x = 6; // allowed: the value is still non-const when accessed through non-const identifier x

    return 0;
}
*/



// Notice we have two notions of const in pointers:
// 1. Pointer to a const 
// 2. const pointers

// Case 1. We have just defined above. The compiler allows you to point it to a different '
// variable if need be. It will only make sure you cannot change the variable at the address
// the pointer is referring to through the pointer. 

// How to declare Case 1: const int* ptr {};

// Case 2. A const pointer is a pointer whose address can not be changed after initialization.

// How to declare Case 2: int* const ptr {};

/*
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // const after the asterisk means this is a const pointer

    return 0;
}
*/


// In the above, the const pointer ptr is pointing towards a (non-const) variable x
// Just like a normal variable, a const pointer need to be initialized when defined, and its 
// value (i.e. the address it is pointing to) can NOT change after that.

/*
int main()
{
    int x{ 5 };
    int y{ 6 };

    int* const ptr { &x }; // okay: the const pointer is initialized to the address of x
    ptr = &y; // error: once initialized, a const pointer can not be changed.

    return 0;
}
*/


// However, if the value being pointed to by the const pointer is not a const, then you can
// still change the value at the address (just cannot point to a different address)
/*
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // ptr will always point to x

    *ptr = 6; // okay: the value being pointed to is non-const

    return 0;
}
*/





// Finally, it is possible to declare a const pointer to a const value by using the const
// keyword both before the type and after the asteris

/*
int main() {
    int x { 5 };
    const int* const ptr { &x }; // a const pointer to a const value

    return 0;
}
*/


// A const pointer to a const value can not have its address changed, nor can the value
// it is pointing to be changed through the pointer. It can only be dereferenced to get
// the value it is pointing at.

// ----------------------------- pointer and const recap --------------------------------
int main()
{
    int v{ 5 };

    int* ptr0 { &v };             // points to an "int" but is not const itself.  We can modify the value or the address.
    const int* ptr1 { &v };       // points to a "const int" but is not const itself.  We can only modify the address.
    int* const ptr2 { &v };       // points to an "int" and is const itself.   We can only modify the value.
    const int* const ptr3 { &v }; // points to a "const int" and is const itself.  We can't modify the value nor the address.

    // if the const is on the left side of the *, the const belongs to the value
    // if the const is on the right side of the *, the const belongs to the pointer

    return 0;
}






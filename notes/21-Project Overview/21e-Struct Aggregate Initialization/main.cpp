// In the previous chapter, 21d, we talked about how structs are defined, how to 
// instantiate struct objects, and how to access their member variables.

// Here we will discuss how structs are initializec

// ----------------- What is aggregate? ----------------------------
// In general programming, an *aggregate data type* (also called an aggregate) is any
// type that can contain multiple data members. 
// Some types of aggregates allow "data members"/"member variables" to have different
// types (such as structs) and some other aggregates require all members to be of
// the same type (such as std::array )

// Definition of aggregate in C++ is more specific. Look at the link below for details:
// https://en.cppreference.com/cpp/language/aggregate_initialization


// ------------------- Aggregate initialization of a struct ------------------

// Aggregates use a form of initialization called "aggregate initialization", which
// allows us to initialize the members of the aggregate simultaneously
// To do this, we provide an "initializer list" which is just a braced list of
// comma-separated values. 

// We touched on this in the last chapter, but there are two primary forms of 
// aggregate initialization

/*
struct Employee {
    int age {};
    std::string id {};
    double wage {};
};

int main() {
    // copy-list initialization using braced list
    Employee Saeed = {22 , "shajiz2" , 1100.00}; 

    // list initialization using braced list (preferred)
    Employee James {28 , "jh2234" , 12000.00};
    return 0;
}
*/

// These are called "memberwise initialization" -- initialize member variables in the
// order that they are defined. 

// In C++20, we can initialize (some) aggregates using a parenthesized list of vals
// We recommend avoiding this as much as possible since it does not work for arrays
// Employee Robert (31 , "R2235" , 1123.22);



// ----------------------- Missing an initialization in a list ---------------------
// If an aggregate is initialized but the number of initialization values is fewer than
// the number of member variables, then each member WITHOUT an explicit initializer is 
// initialized as follows:
// 1. If the member has a default member initializer, that is used.
// 2. Otherwise, the member is copy-initialized from an empty initializer list. In most
//    cases this will be a value-initialization (e.g. 0.0 for double)

/*
#include <iostream>
struct Employee {
    int id {};
    int age {};
    double wage {75000.0};
    double whatever; 
    std::string whatever2;
};

int main () {
    Employee Saeed {11 , 29}; // Saeed.whatever will be initialized at 0.0
                              // Saeed.whatever2 will be initialized at ""

    std::cout << "Saeed.whatever : " << Saeed.whatever;
    std::cout << " and Saeed.whatever2 is " << (Saeed.whatever2 ==  "") << std::endl;
    return 0;
}
*/



// --------------------- Print struct with overloading operator<< -------------------
// We have seen in previous chapters how to overload operator>> to print an enumeration
// Here we overload operator<< to print a struct 
/*
#include <iostream>

struct Employee {
    int id {};
    int age {};
    double wage {};
};

std::ostream& operator<<(std::ostream& out , const Employee& e) {
    out << e.id << " " << e.age  << " " <<  e.wage;
    return out;
}

int main() {
    Employee Saeed {2 , 28}; // wage will be initialized to 0.0
    operator<<(std::cout ,  Saeed) << std::endl;
}
*/




// ---------------------- Const structs ------------------------------------
// Variables of struct type can be const (or constexpr) just like any other type
// Let's say we want to write a program that receives two rectangles and outputs
// whether there is exactly one ellipse that circumscribes one and is inscribed inside
// the other. In such situations, we need to pass the rectangles as two constant inputs
// Hence, using constant structs to represent these rectangles would be appropriate.


/*
struct Rectangle {
    double length {};
    double width {};
};

int main () {
    const Rectangle unit {1.0 , 1.0};
    const Rectangle zero { };
    return 0;
}
*/


// -------------------------------- Designated initializers ----------------------------------
// When initializing a struct from a list of values, the initializers are applied to the members
// in order of declaration.
/*
struct Foo
{
    int a {};
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // f.a = 1, f.c = 3

    return 0;
}
*/

// Now consider what would happen if you were to update this struct definition to add a new
// member that is not the last member:

/*
struct Foo
{
    int a {};
    int b {}; // just added
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // now, f.a = 1, f.b = 3, f.c = 0

    return 0;
}*/
// Now all your initialization values have shifted, and worse, the compiler may not detect
// this as an error (after all, the syntax is still valid).

// **** Solution ***** : C++20 adds a new way to initialize struct members called
//                       ******* designated initializers *******:
// Designated initializers allow you to explcitly specify which initialization value maps to what
// member. It can be a list ({.a {1} , etc etc}) or a copy ({.a = 1 , etc etc}) initialization

/*
struct Foo{
    int a{};
    int b{};
    int c{};
};

int main() {
    Foo f1{ .a { 1 } , .c { 3 }}; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a = 1 , .c = 3};     // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
    Foo f3{ .b{ 2 }, .a{ 1 } };   // error: initialization order does not match order of 
                                  // declaration in struct
    return 0;
}
*/

// Lastly, while designated initializers are nice, we do not recommend using them since
// they easily clutter up the initializer list
// ***** Best practice ******:
// When adding a new member to an aggregate, it’s safest to add it to the bottom of the
// definition list so the initializers for other members don’t shift. 

// ---------------- Initialize a struct with another struct of the same type -------------------
#include <iostream>

struct Foo {
    int a{};
    int b{};
    int c{};
};

std::ostream& operator<<(std::ostream& out , const Foo& f) {
    out << f.a << " " << f.b << " " << f.c ;
    return out;
}

int main() {
    Foo f {1 , 2 , 3};

    Foo f1 = f;  // copy-initialization
    Foo f2(f);   // direct-initialization
    Foo f3 {f};  // direct-list-initialization

    std::cout << f1 << '\n';
    std::cout << f2 << '\n';
    std::cout << f3 << '\n';
    return 0; 
}
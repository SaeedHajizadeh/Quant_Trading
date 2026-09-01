// ---------------------------------------------------------------------------------------
// ---------------------------- Static Member Variables ----------------------------------
// ---------------------------------------------------------------------------------------

// *Global variables* and *static local variables* are both variables that have static storage
//  duration, meaning they exist for the lifetime of the program. In other words, they have
// started at the start of the program and will continue to exist until the program ends. 
// The difference between the two is that global variables are visible throughout the entire
// program, while static local variables are only visible within the function in which
// they are defined.

// For instance the following program prints 1 2 3
/*
#include <iostream>

int generateID() {
    static int s_id { 0 }; // static local variable
    return ++s_id;
}

int main() {
    std::cout << generateID() << ' ';
    std::cout << generateID() << ' ';
    std::cout << generateID() << '\n';

    return 0;
}
*/
// Note that static local variable s_id has kept its value across multiple function calls.
// For comparison, the following program prints 1 1 1 because the local variable id is
// reinitialized to 0 at the start of each function call.

/*
#include <iostream>

int generateID() {
    int s_id { 0 }; // static local variable
    return ++s_id;
}

int main() {
    std::cout << generateID() << ' ';
    std::cout << generateID() << ' ';
    std::cout << generateID() << '\n';

    return 0;
}
*/


// Class types bring two more uses for the static keyword: static member variables,
// and static member functions.

// ------------------------------ Static Member Variables ------------------------------
// Before starting static member variables, let's first look at a simple class
/*
#include <iostream>

struct Something
{
    int value{ 1 };
};

int main()
{
    Something first{};
    Something second{};

    first.value = 2;

    std::cout << first.value << '\n';
    std::cout << second.value << '\n';

    return 0;
}
*/
// The program above prints 2 and 1. The reason is:
// When we instantiate a class object, each object gets its own copy of all *normal* member
// variables. In this case, because we have declared two Something class objects, we end up
// with two copies of value: first.value, and second.value. first.value is distinct from
// second.value.


// **********************************************************************************************
// Unlike normal member variables, static member variables are shared by all objects of the class 
// **********************************************************************************************
/*
#include <iostream>

struct Something
{
    static int s_value; // declare s_value as static (initializer moved below)
};

int Something::s_value{ 1 }; // define and initialize s_value to 1 (we'll discuss this section below)

int main()
{
    Something first{};
    Something second{};

    first.s_value = 2;

    std::cout << first.s_value << '\n';
    std::cout << second.s_value << '\n';
    return 0;
}
*/
// Program above prints 2 and 2. The reason is because s_value is a static member variable,
// and thus s_value is shared between all objects of the class.

// -------------- Static members are not associated with class objects -----------------
// Although you can access static members through objects of the class (as shown with
// first.s_value and second.s_value in the example above), static members exist even if
// no objects of the class have been instantiated! This makes sense: they are created at the
// start of the program and destroyed at the end of the program, so their lifetime is not
//bound to a class object like a normal member. Moreover, if a static member variable is 
// shared between all objects of the class, it would be strange to have to create an object
// of the class just to access a static member variable. 

// Essentially, static members are global variables that live inside the scope region of the class

// Because static member s_value exists independently of any class objects, it can be accessed
// directly using the class name and the scope resolution operator (in this case,
// Something::s_value)
/*
#include <iostream>
class Something {
    public:
        static int s_value; // declare s_value as static 
        
};

int Something::s_value { 1 }; // define and initialize s_value to 1; we'll discuss this below

int main() {
    // note: we're not instantiating any objects of type Something

    Something::s_value = 2;
    std::cout << Something::s_value << '\n';
    return 0;
}
*/
// ************************************** Best practices **************************************
// Access static members using the class name and the scope resolution operator (::)
// ********************************************************************************************

// ----------------------- Defining and initializing static member variables ------------------
// When we declare a static member variable inside a class type, we’re telling the compiler
// about the existence of a static member variable, but not actually defining it (much like
// a forward declaration). Because static member variables are essentially global variables,
// you *must* explicitly define (and optionally initialize) the static member outside of
// the class, in the global scope.

// The line that does this in the code above is 
/*
int Something::s_value{ 1 }; // define and initialize s_value to 1
*/
// This line serves two purposes: it instantiates the static member variable (just like a global
// variable), and initializes it. In this case, we’re providing the initialization value 1.
// If no initializer is provided, static member variables are zero-initialized by default.

// Note that this static member definition is not subject to access controls: you can define
// and initialize the value even if it’s declared as private (or protected) in the class
// (as definitions are not considered to be a form of access).

// For non-template classes, if the class is defined in a header (.h) file, the static
// member definition is usually placed in the associated code file for the class (e.g.
// Something.cpp). Alternatively, the member can also be defined as inline and placed
// below the class definition in the header (this is useful for header-only libraries).
// If the class is defined in a source (.cpp) file, the static member definition is usually
// placed directly underneath the class. Do not put the static member definition in a header
// file (much like a global variable, if that header file gets included more than once,
// you’ll end up with multiple definitions, which will cause a linker error).

// For template classes, the (templated) static member definition is typically placed
// directly underneath the template class definition in the header file (this doesn’t violate
// the One definition rule (ODR) because such definitions are implicitly inline).


// -------- Initialization of static member variables inside the class definition --------
// when the static member is a constant integral type (which includes char and bool)
// or a const enum, the static member can be initialized inside the class definition:
/*
#include <iostream>

class Configuration {
public:
    // a static const int can be defined and initialized directly -- it is a compilte-time
    // constant so it can be initialized inside the class definition
    static const int maxConnections { 100 };
    // inline variables are the ones allowed to have multiple definitions across
    // C++17 allows static member variables to be defined as inline, which allows them
    // to be initialized inside the class definition.
    static inline int maxtime { 60 }; // inline static member variable (C++17 and later)

    // Because constexpr members are implicitly inline (as of C++17), static constexpr members
    // can also be initialized inside the class definition without explicit use of the
    // inline keyword
    static constexpr int maxUsers { 1000 }; // static constexpr member variable (C++17 and later)

    static int timeout; // Declaration of static member variable (definition below) 
};

// Note that since this is NOT a constant integral type, we cannot initialize it inside
// the class definition. We initialize it here outside the class definition, in the global scope
// Note also that when you define a static class member outside the class, you must omit
// the static keyword and include the class scope (Configuration::).
int Configuration::timeout { 30 }; // Definition of static member variable (outside the class)

int main() {
    // Accessing without creating an object
    std::cout << Configuration::maxConnections << std::endl; 
    std::cout << Configuration::maxtime << std::endl; 
    std::cout << Configuration::maxUsers << std::endl; 
    std::cout << Configuration::timeout << std::endl; 
    return 0;
}
*/

// ************************************** best practices ***************************************
// Make your static members inline or constexpr so they can be initialized inside the
//  class definition.
// *********************************************************************************************

// Why use static variables inside classes? One use is to assign a unique ID to every
// instance of the class. For example:
/*
#include <iostream>

class Something
{
private:
    static inline int s_idGenerator { 1 };
    int m_id {};

public:
    // grab the next value from the id generator
    Something() : m_id { s_idGenerator++ }
    {
    }

    int getID() const { return m_id; }
};

int main()
{
    Something first{};
    Something second{};
    Something third{};

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';
    return 0;
}
*/

// The program above prints 1, 2, and 3. 

// Because s_idGenerator is shared by all Something objects, when a new Something object
// is created, the constructor initializes m_id with the current value of s_idGenerator
// and then increments the value for the next object. This guarantees that each instantiated
// Something object receives a unique id (incremented in the order of creation).

// Giving each object a unique ID can help when debugging, as it can be used to
// differentiate objects that otherwise have identical data. This is particularly
// true when working with arrays of data.

// ----------- Only static members may use type deduction (auto and CTAD) -----------
// A static member may use auto to deduce its type from the initializer, or
// Class Template Argument Deduction (CTAD) to deduce template type arguments from
// the initializer.

// Non-static members may not use auto or CTAD. The reasons for this are quite complicated.

/*
#include <utility> // for std::pair<T, U>

class Foo
{
private:
    auto m_x { 5 };           // auto not allowed for non-static members
    std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members

    static inline auto s_x { 5 };           // auto allowed for static members
    static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members

public:
    Foo() {};
};

int main()
{
    Foo foo{};

    return 0;
}
*/



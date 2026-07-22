// t’s say you wanted to write a function to calculate the maximum of two numbers.

/*
int max(int x, int y)
{
    return (x < y) ? y : x;
    // Note: we use < instead of > because std::max uses <
}
*/


// This function really only works for integers. If the user would like to enter and compare two
// doubles, another function definition needs to be provided. 

/*
double max(double x, double y)
{
    return (x < y) ? y: x;
}
*/


// Note that the code for the implementation of the double version of max is exactly the same as
// for the int version of max!

// Having to overload function definitions for each set of function parameters is a maintenance 
// headache, and error prone. More importantly, if the user would like to apply the max funciton
// to a new argument type the developer did not anticipate, things stop working. 

// We can utilize a feature in C++ that allows us to definie *one* function that captures any
// type for the inputs and outputs ---> C++ templates.

// ---------------------------------- C++ Templates ------------------------------------
// Instead of manually creating a bunch of mostly-identical functions or classes (one for each
// set of different types), we instead create a single template. Just like a normal definition,
// a template definition describes what a function or class looks like. Unlike a normal
// definition (where all types must be specified), in a template we can use one or more
// placeholder types. A placeholder type represents some type that is not known at the time the
// template is defined, but that will be provided later (when the template is used).

// Because the actual types aren’t determined until the template is used in a program
// (not when the template is written), the author of the template doesn’t have to try to
// anticipate all of the actual types that might be used. This means template code can be
// used with types that didn’t even exist when the template was written! We’ll see how this
// comes in handy later, when we start exploring the C++ standard library, which is absolutely
// full of template code!


// -------------------------------------- Function Templates -------------------------------
// A function template is a function-like definition that is used to generate one or more
// overloaded functions, each with a different set of actual types. This is what will allow
// us to create functions that can work with many different types. The initial function template
// that is used to generate other functions is called the primary template, and the functions
// generated from the primary template are called instantiated functions.

// When we create a primary function template, we use placeholder types (technically called
// type template parameters, informally called template types) for any parameter types, return
// types, or types used in the function body that we want to be specified later, by the user of
// the template.

// --------------------------------- Creating max() function -----------------------------------
// The int version of the max() function again
/*
int max(int x, int y)
{
    return (x < y) ? y : x;
}
*/


// To create a function template for max(), we’re going to do two things. First, we’re going to
// replace any actual types that we want to be specified later with type template parameters.
// In this case, because we have only one type that needs replacing (int), we only need one
// type template parameter (which we’ll call T):

/*
T max(T x , T y) {  // // won't compile because we haven't defined T
    return (x < y) ? y : x;
}
*/



// This is a good start. BUT it does not compile since the compiler does not know T! Also, this
// is still a normal function not a template function

// Second, we’re going to tell the compiler that this is a template, and that T is a type
// template parameter that is a placeholder for any type. Both of these are done using a
// ***template parameter declaration***, which defines any template parameters that will
// be subsequently used. The scope of a template parameter declaration is strictly limited
// to the function template (or class template) that follows. Therefore, each function template
// or class template needs its own template parameter declaration.

/*
template <typename T> // this is the template parameter declaration defining T
T max(T x , T y){     // // this is the function template definition for max<T>
    return (x < y) ? y : x;
}
*/

// ******** template parameter declaration **********
// In our template parameter declaration, we start with the keyword template, which tells
// the compiler that we’re creating a template. Next, we specify all of the template parameters
// that our template will use inside angled brackets (<>). For each type template parameter,
// we use the keyword typename (preferred) or class, followed by the name of the type
// template parameter (e.g. T).

// ---------------------------------- Naming template parameters -----------------------------
// Much like we often use a single letter for variable names used in trivial situations
// (e.g. x), it’s conventional to use a single capital letter (starting with T) when the
// template parameter is used in a trivial or obvious way. 




// ---------------------------- Function template instantiation ------------------------------
// How do we use a function template we just defined?
// Function templates are NOT actually functions; but their job is to generate functions that are
// compiled and executed. To use the max<T> functio template we just defined, we make the 
// following function call:

/*
max<actual_type>(arg1 , arg2);   // actual_type is some actual type like int or double
*/
// This looks a lot like a normal function call -- the primary difference is the addition
// of the type in angled brackets (called a template argument), which specifies the actual
// type that will be used in place of template type T.


// A full example:

/*
#include <iostream>

template <typename T>
T max (T x , T y){
    return (x < y) ? y : x;
}

int main(){
    int x { 11 };
    int y { -2 };

    std::cout << max<int>(x , y) << '\n'; // instantiates and calls function max<int>(int, int)
    return 0;
}
*/


// ****************************************************************************************
// When the compiler encounters the function call max<int>(1, 2), it will determine that a *
// function definition for max<int>(int, int) does not already exist. Consequently, the    *
// compiler will implicitly use our max<T> function template to create one.                *
// ****************************************************************************************

// The process of creating functions (with specific types) from function templates (with template
// types) is called ***function template instantiation*** (or ***instantiation*** for short).
// When a function is instantiated due to a function call, it’s called *implicit instantiation*.
// A function that is instantiated from a template is technically called a ***specialization***,
// but in common language is often called a *function instance*. The template from which a
// specialization is produced is called a ***primary template***. Function instances are normal
// functions in all regards.

// The process for instantiating a function is simple: the compiler essentially clones the
// primary template and replaces the template type (T) with the actual type we’ve specified (int).
// So when we call max<int>(1, 2), the function specialization that gets instantiated looks
// something like this:
/*
template<> // ignore this for now
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}
*/


// Whenever a function template for a particular type is called, the compiler instantiates the
// template for that type and then that instantiation, being a normal function, is called.
// Further calls to that particular type do not require re-instantiation. 

/*
#include <iostream>

template <typename T>
T max(T x, T y) // function template for max(T, T)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
*/


// Post all instantiations, the code snippet above looks like this
/*
#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

template<>
double max<double>(double x, double y) // the generated function max<double>(double, double)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
*/



// --------------------------- Template Argument Deduction -------------------------------
// In most casse, the type we want to use to instantiate the template function with, match the
// type of the function parameters we actually use. For example
/*
std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int> and 1 and 2 are int
*/

// n cases where the type of the arguments match the actual type we want, we do not need to
// specify the actual type -- instead, we can use ***template argument deduction*** to have
// the compiler deduce the actual type that should be used from the argument types in the
// function call.

// For example, instead of
/*
std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int>
*/
// we can use
/*
std::cout << max<>(1, 2) << '\n';
std::cout << max(1, 2) << '\n';
*/



// The difference between the two cases has to do with how the compiler resolves the function
// call from a set of overloaded functions. In the top case (with the empty angled brackets),
// the compiler will only consider max<int> template function overloads when determining which
// overloaded function to call. In the bottom case (with no angled brackets), the compiler will
// consider both max<int> template function overloads and max non-template function overloads.
// When the bottom case results in both a template function and a non-template function that are
// equally viable, the non-template function will be preferred.


/*
#include <iostream>

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<int>(int, int)\n";
    return (x < y) ? y : x;
}

int max(int x, int y)
{
    std::cout << "called max(int, int)\n";
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int) directly
    std::cout << max<>(1, 2) << '\n';    // deduces/instantiates max<int>(int, int) (non-template
                                         // functions not considered)
    std::cout << max(1, 2) << '\n';      // calls max(int, int)

    return 0;
}
*/


// The reason, in the last call, the compiler prefers the non-template function definition, i.e.
// the one where types are determined in the definition overload (and not template) is that these
// functions are more optimized in terms of implementation generally speaking. They could aslo
// be more specialized. For example

/*
#include <iostream>

// This function template can handle many types, so its implementation is generic
template <typename T>
void print(T x)
{
    std::cout << x; // print T however it normally prints
}

// This function only needs to consider how to print a bool, so it can specialize how it handles
// printing of a bool
void print(bool x)
{
    std::cout << std::boolalpha << x; // print bool as true or false, not 1 or 0
}

int main()
{
    print<bool>(true); // calls print<bool>(bool) -- prints 1
    std::cout << '\n';

    print<>(true);     // deduces print<bool>(bool) (non-template functions not considered) -- prints 1
    std::cout << '\n';

    print(true);       // calls print(bool) -- prints true
    std::cout << '\n';

    return 0;
}
*/



// It’s possible to create function templates that have both template parameters and
// non-template parameters. The type template parameters can be matched to any type, and the
// non-template parameters work like the parameters of normal functions.

// T is a type template parameter
// double is a non-template parameter
// We don't need to provide names for these parameters since they aren't used
/*
template <typename T>
int someFcn(T, double)
{
    return 5;
}

int main()
{
    someFcn(1, 3.4); // matches someFcn(int, double)
    someFcn(1, 3.4f); // matches someFcn(int, double) -- the float is promoted to a double
    someFcn(1.2, 3.4); // matches someFcn(double, double)
    someFcn(1.2f, 3.4); // matches someFcn(float, double)
    someFcn(1.2f, 3.4f); // matches someFcn(float, double) -- the float is promoted to a double

    return 0;
}
*/

// ---------- Function templates and defulat arguments for nontemplate parameters ---------

/*
#include <iostream>

template <typename T>
void print(T val , int times = 1){
    while (times--)         // (times--) gets processed AND after that times = times - 1 
        std:: cout << val << " ";
}

int main(){
    double x { 3.9 };
    int times = 15;
    char c { 'W' };

    print(x , times);
    print("\n");
    print(c , times - 10);
    std::cout << std::endl;

    return 0;
}
*/




// =================================== Static local variables ===================================

// A static local variable is a variable declared inside a function that retains its value
// between different function calls. Unlike regular local variables that are destroyed each
// time a function exits, a static local variable persists for the program's entire lifetime
// but remains hidden outside its function's scope.

// Example: In C or C++, a function can use a static variable to count how many times it
// has been called

/*
#include <stdio.h>
void trackCalls() {
    static int callCount = 0; // Initialized to 0 only on the first call
    callCount++;

    printf("Function is called %d times\n" , callCount);

}

int main() {
    trackCalls(); // Output: Function called 1 times
    trackCalls(); // Output: Function called 2 times
    trackCalls(); // Output: Function called 3 times

    return 0;
}

*/

// Initialization: callCount = 0 only happens during the very first time trackCalls() runs. The
//                 reason is the compiler handles static variables differently than regular 
//                 local variables.
// Persistence:    Every subsequent time the function is called, the line is skipped, and
//                 callCount resumes exactly where it left off.
// Scope:          Even though callCount persists throughout the program, you cannot access
//                 or modify it from main() or any other function.


// Here is how it works behind the scene:
/*
1. Dedicated Memory Allocation

Regular local variables are created on the stack and get destroyed
when the function exits. Static local variables are stored in the data segment (global memory).
This memory area persists for the entire lifetime of the program.

2. One-Time Initialization

The line static int callCount = 0; is executed only once, when the program first loads or when
the function is hit for the very first time.On all subsequent function calls, the runtime
environment skips the initialization line entirely.Instead, the function immediately executes
the next line, looking up the existing value already sitting in that permanent memory slot.
*/
// ==============================================================================================


// ------- Beware function templates with modifiable static local variables --------

// When a static local variable is used in a function template, each function instantiated
// from that template will have a separate version of the static local variable. This is
// rarely a problem if the static local variable is const. But if the static local variable
// is one that is modified, the results may not be as expected.

#include <iostream>

// Here's a function template with a static local variable that is modified
template <typename T>
void printIDAndValue(T value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);
    printIDAndValue(13);

    printIDAndValue(14.5);

    return 0;
}

// result: 1) 12
//         2) 13
//         1) 14.5

// You may have been expecting the last line to print 3) 14.5. However, this is what the
// compiler actually compiles and executes:

/*
#include <iostream>

template <typename T>
void printIDAndValue(T value);

template <>
void printIDAndValue<int>(int value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

template <>
void printIDAndValue<double>(double value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);   // calls printIDAndValue<int>()
    printIDAndValue(13);   // calls printIDAndValue<int>()

    printIDAndValue(14.5); // calls printIDAndValue<double>()

    return 0;
}
*/
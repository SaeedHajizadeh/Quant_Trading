// We have looked at Function templates. We learned that if we want to work with multiple types
// of input and/or output data, we need to overload the functions, i.e. define a separate 
// function definition for each set of pairs of types. For example, supppose we want to look
// at the maximum of two numbers

/*
#include <iostream>

// We need one function if inputs and outputs are integers
int max(int x , int y) {
    return (x < y) ? y : x;
}

// almost identical function to calculate the greater of two double values the only 
// difference is the type information

double max(double x , double y){
    return (x < y) ? y : x;
}

int main() {
    std::cout << max(5, 6);     // calls max(int, int)
    std::cout << '\n';
    std::cout << max(1.2, 3.4); // calls max(double, double)
    std::cout << '\n';

    return 0;
}
*/

// Having to overload function definitions for each set of function parameters is a maintenance 
// headache, and error prone. More importantly, if the user would like to apply the max funciton
// to a new argument type the developer did not anticipate, things stop working. 

// We can utilize a feature in C++ that allows us to definie *one* function that captures any
// type for the inputs and outputs ---> C++ templates. We have seen that all so here is the solution

/*
#include <iostream>

// define the template then the function
template <typename T>
T max(T x , T y){
    return (x < y) ? y : x;
}

int main() {
    std::cout << max(5, 6);     // calls max(int, int)
    std::cout << '\n';
    std::cout << max(1.2, 3.4); // calls max(double, double)
    std::cout << '\n';

    return 0;
}
*/



// -------------------------- Aggregate Types Have Similar Challenges --------------------------
// We run into similar challenges with aggregate types (both structs/classes/unions and arrays).

// For example:

/*
#include <iostream>

struct Pair {
    int first {};
    int second {};
};

int max(Pair p){  // pass by value because Pair is small
    return (p.first < p.second ? p.second : p.first);
}   

int main(){
    Pair p1 { 5 , 6 };

    std::cout << max(p1) << '\n';

    return 0;
}
*/


// Later, we discover that we also need pairs of double values. So we update our program
// to the following:

/*
#include <iostream>

struct Pair
{
    int first{};
    int second{};
};

struct Pair // compile error: erroneous redefinition of Pair
{
    double first{};
    double second{};
};

constexpr int max(Pair p)
{
    return (p.first < p.second ? p.second : p.first);
}

constexpr double max(Pair p) // compile error: overloaded function differs only by return type
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair p1{ 5, 6 };
    std::cout << max(p1) << " is larger\n";

    Pair p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n";

    return 0;
}

*/


// Unfortunately, this program won’t compile, and has a number of problems that need to be
// addressed.

// First, unlike functions, type definitions can’t be overloaded. The compiler will treat
// double second definition of Pair as an erroneous redeclaration of the first definition
// of Pair. Second, although functions can be overloaded, our max(Pair) functions only differ
// by return type, and overloaded functions can’t be differentiated solely by return type.
// Third, there is a lot of redundancy here. Each Pair struct is identical (except for the
// data type) and same with our max(Pair) functions (except for the return type).

// We could solve the first two issues by giving our Pair structs different names
// (e.g. PairInt and PairDouble). But then we both have to remember our naming scheme,
// and essentially clone a bunch of code for each additional pair type we want, which doesn’t
// solve the redundancy problem. We have a solution:

// ------------------------------------ Class Templates -------------------------------------
// Much like a function template is a template definition for instantiating functions, a
// class template is a template definition for instantiating class types.

// =========================================Reminder======================================

// A “class type” is a struct, class, or union type. Although we’ll be demonstrating
// “class templates” on structs for simplicity, everything here applies equally well
// to classes.

// =======================================================================================

// Let's use class templates in the above examples as a solution to overloading
/*
#include <iostream>

template <typename T>
struct Pair{
    T first  {};
    T second {};
};

template <typename T>
constexpr T max(Pair<T> p){
    return (p.first < p.second ? p.second : p.first);
}

int main(){

    Pair<int> p1{ 5, 6 };                    // instantiates Pair<int> and creates object p1
    std::cout << max(p1) << " is larger\n";

    Pair<double> p2{ 1.2, 3.4 };             // instantiates Pair<double> and creates object p2
    std::cout << max(p2) << " is larger\n";

    Pair<double> p3 { 2.3 , -1.22 };  // creates object p3 using prior definition for Pair<double>

    return 0;
}
*/


// Just like with function templates, we start a class template definition with a template
// parameter declaration. We begin with the template keyword. Next, we specify all of the
// template types that our class template will use inside angled brackets (<>). For each
// template type that we need, we use the keyword typename (preferred) or class (not preferred),
// followed by the name of the template type (e.g. T). In this case, since both of our members
// will be the same type, we only need one template type.

// Next we define our struct as usual, except we use our template type T wherever we foresee
// new types could be used in the code.

// Inside the main function, we instantiate our Pair objects using the Pair<type> syntax. For
// example, a Pair of integers would be instantiated by Pair<int>. The compiler then uses
// the class template to instantiate a struct type definition named Pair<int>.




// Here’s the same example as above, showing what the compiler actually compiles after all
// template instantiations are done:


/*
#include <iostream>

// A declaration for our Pair class template
// (we don't need the definition any more since it's not used)
template <typename T>
struct Pair;

// Explicitly define what Pair<int> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<int>
{
    int first{};
    int second{};
};

// Explicitly define what Pair<double> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<double>
{
    double first{};
    double second{};
};

int main()
{
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
*/




// The code above, which is equivalent to the one above it, works because Pair<int> and
// Pair<double> are two genuinely different types with two different names, not one name
// defined twice. So the structure of the code above is
/*
template <typename T>
struct Pair;   // primary template declaration

template <>
struct Pair<int> { int first{}; int second{}; };      // defines the type "Pair<int>"

template <>
struct Pair<double> { double first{}; double second{}; }; // defines the type "Pair<double>"
*/



// Notice that we could not overload our max function a few blocks above since the only 
// difference between the overloading defintions was the return type and C++ requires new
// parameters for accepting overloading. The definition of Pair<int> and Pair<double>, either
// through class template definition and initialization at compile time or through explicit
// specialization (defining Pair<int> and Pair<double> explicitly), allows us to overload
// max() deinition since max(Pair<int>) and max(Pair<double>) have now different parameters.

/*
constexpr int max(Pair<int> p)
{
    return (p.first < p.second ? p.second : p.first);
}

constexpr double max(Pair<double> p) // okay: overloaded function differentiated by parameter type
{
    return (p.first < p.second ? p.second : p.first);
}
*/

// While this compiles, it doesn’t solve the redundancy problem. What we really want is a
// function that can take a pair of any type. In other words, we want a function that takes
// a parameter of type Pair<T>, where T is a template type parameter. And that means we need
// a ******function template******* for this job!

/*
#include <iostream>

template <typename T>
struct Pair{
    T first {};
    T second {};
};

template <typename T>
T max(Pair<T> p){
    return p.first < p.second ? p.second : p.first;
}

int main() {

    Pair<int> p1 {-2 , -1};                  // instantiates Pair<int> and creates object p1
    Pair<double> p2 {-5.5 , -3.3};           // instantiates Pair<int> and creates object p2

    std::cout << "max of p1: " << max<int>(p1) << '\n'; // explicit call to max<int>

    // call to max<double> using template argument deduction (prefer this)
    std::cout << "max of p2: " << max(p2) << '\n';

    return 0;
}
*/



// When the max() function is called with a Pair<int> argument, the compiler will instantiate
// the function int max<int>(Pair<int>) from the function template, where template type T is
// replaced with int. The following snippet shows what the compiler actually instantiates in
// such a case:

/*
template <>
constexpr int max(Pair<int> p)
{
    return (p.first < p.second ? p.second : p.first);
}
*/



// ****** As with all calls to a function template, we can either be explicit about the template
// type argument (e.g. max<int>(p1)) or we can be implicit (e.g. max(p2)) and let the compiler
// use template argument deduction to determine what the template type argument should be.*****




// -------- Class templates with template type and non-template type members -----------

// class types can be defined with a mixture of template types (like T ,etc.) and non-template
// types (like int, double, std::string etc)

/*
template <typename T>
struct Pair{
    T first {};
    int second {};
};
*/

// We can also use a mixture of *** distinct *** template types

/*
template <typename T , typename U>
struct Pair{
    T first {};
    U second {};
};
*/



// Exercise: Using the framework above, write a program that defines a class template with
// multiple template types and define a print function to print that (assuming things are 
// not std::string since a new print is needed for that.)

/*#include <iostream>

template <typename T , typename U>
struct Pair{
    T first {};
    U second {};
};

template <typename T , typename U>
void print(Pair<T , U> p){
    std::cout << "[ " << p.first << " , " << p.second << " ]" << '\n';
}

int main() {
    Pair<int , double> p1 {-5 , -1.235};
    Pair<long , long> p2 {-232564165132151 , 313122132321544561}; 

    print(p1);
    print(p2);

    return 0;
}
*/



// Now suppose you want to redefine print() such that it takes ANY type as parameter not just
// Pair<T , U>. Then

/*
#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

struct Point
{
    int first{};
    int second{};
};

template <typename T>
void print(T p) // type template parameter will match anything
{
    std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
}

int main()
{
    Pair<double, int> p1{ 4.5, 6 };
    print(p1); // matches print(Pair<double, int>)

    std::cout << '\n';

    Point p2 { 7, 8 };
    print(p2); // matches print(Point)

    std::cout << '\n';

    return 0;
}
*/



// With this in mind, one case can be misleading:

/*
template <typename T, typename U>
struct Pair // defines a class type named Pair
{
    T first{};
    U second{};
};

template <typename Pair> // defines a type template parameter named Pair (shadows Pair class type)
void print(Pair p)       // this refers to template parameter Pair, not class type Pair
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}
*/



// You might expect that this function will only match when called with a Pair class type
// argument. But this version of print() is functionally identically to the prior version
// where the template parameter was named T, and will match with any type. The issue here is
// that when we define Pair as a type template parameter, it shadows other uses of the name
// Pair within the global scope. So within the function template, Pair refers to the template
// parameter Pair, not the class type Pair. And since a type template parameter will match
// to any type, this Pair matches to any argument type, not just those of class type Pair!

// This is a good reason to stick to simple template parameter names, such a T, U, N, as they
// are less likely to shadow a class type name.




// ---------------------------------- std::pair ------------------------------------------
// Because working with pairs of data is common, the C++ standard library contains a class
// template named std::pair (in the <utility> header) that is defined identically to the
// Pair class template with multiple template types in the preceding section.

/*
#include <iostream>
#include <utility>

template <typename T , typename U>
void print(std::pair<T , U> p){
    // the members of std::pair have predefined names `first` and `second`
    std::cout << '[' << p.first << ", " << p.second << ']' << '\n';
}

int main(){
    std::pair<int, double> p1 { 1 , 3.5 };
    std::pair<double ,  int> p2 { -1.2245 , 0 };
    std::pair<int , int> p3 { 0 , 0 };

    print(p2);

    return 0;
}
*/



// In real code, you should favor std::pair over writing your own.


// ------------------ Using class templates in multiple files ----------------------
// Just like function templates, class templates are typically defined in header files so
// they can be included into any code file that needs them. Both template definitions and
// type definitions are exempt from the one-definition rule, so this won’t cause problems:

/*
// pair.h:
#ifndef PAIR_H
#define PAIR_H

template <typename T>
struct Pair{
    T first {};
    T second {};
};

template <typename T>
constexpr T max(Pair<T> p){
    return (p.first < p.second ? p.second : p.first);
}

#endif


// foo.cpp:
#include "pair.h"
#include <iostream>

void foo()
{
    Pair<int> p1{ 1, 2 };
    std::cout << max(p1) << " is larger\n";
}

// main.cpp:
#include "pair.h"
#include <iostream>

void foo(); // forward declaration for function foo()

int main(){
    Pair<double> p2 { 3.4, 5.6 };
    std::cout << max(p2) << " is larger\n";

    foo();
    
    return 0;
}
*/
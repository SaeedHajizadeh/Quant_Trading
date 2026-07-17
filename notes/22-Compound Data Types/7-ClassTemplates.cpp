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
// solve the redundancy problem.
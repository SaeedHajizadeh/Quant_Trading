// We have seen how structs are used to bundle multiple member variables into a single object
// that can be initialized and passed around as a unit. In other words, structs provide a 
// package for storing and moving related data values.

// Structs are a class type  (which includes classes, structs, and unions) but lacks the 
// class invariants:


// Consider the following struct:
/*
#include <iostream>

struct Date
{
    int day{};
    int month{};
    int year{};
};

void printDate(const Date& date)
{
    std::cout << date.day << '/' << date.month << '/' << date.year; // assume DMY format
}

int main()
{
    Date date{ 4, 10, 21 }; // initialize using aggregate initialization
    printDate(date);        // can pass entire struct to function

    return 0;
}
*/

// In the above example, we create a Date object and then pass it to a function that prints
// the date. This program prints a date 4/10/21

// As useful as structs are, structs have a number of deficiencies that can present 
// challenges when trying to build large, complex programs (especially those worked on
// by multiple developers).

// ------------------------------- The class invariant problem -------------------------------
// Perhaps the biggest difficulty with structs is that they do not provide an effective
// way to *** document and enforce class invariants ****. 

// *******In lesson 9.6 -- Assert and static_assert, we defined an invariant as, 
// “a condition that must be true while some component is executing”. ******

// In the context of class types (which include structs, classes, and unions), a
// *** class invariant *** is a condition that must be true throughout the lifetime of an
// object in order for the object to remain in a valid state. An object that has a violated
// class invariant is said to be in an invalid state, and unexpected or undefined behavior
// may result from further use of that object.


// Consider the following struct defined below:
/*
#include <iostream>

struct Fraction
{
    int numerator { 0 };
    int denominator { 1 }; // class invariant: should never be 0
};

void printFractionValue(const Fraction& f)
{
     std::cout << f.numerator / f.denominator << '\n';
}

int main()
{
    Fraction f { 5, 0 };   // create a Fraction with a zero denominator
    printFractionValue(f); // cause divide by zero error

    return 0;
}
*/


// There is no systematic way, outside of putting comment and trying to remember to set a
// *non-zero value to the denominator* in the code snippet above. Hence, we cannot document
// and enforce class invariant property. Initializing a struct with denominator equal to 0
// violates the class invariant and pushes the struct into an *** invalid state *** without
// us knowing (this is true in very large programs.)

// Relying on the user of an object to maintain class invariants is likely to result in problems.
// Structs (as aggregates) just don’t have the mechanics required to solve this problem in 
// an elegant way.


// ------------------------------ Intro to Classes ------------------------------
// Just like structs, a class is a program-defined compound type that can have many member
// variables with different types.

// *****************************************************************************
/*
From a technical standpoint, structs and classes are almost identical -- therefore, any
example that is implemented using a struct could be implemented using a class, or vice-versa.
However, from a practical standpoint, we use structs and classes differently.
*/
// *****************************************************************************


// Because a class is a program-defined data type, it must be defined before it can be used.
// Classes are defined similarly to structs

/*
class Employee{
    int m_id {};
    int m_age {};
    double m_wage {};
};
*/

// ************************
/*
It is not an incident that we prefixed the member variables of the class definition above
with m_. We will see the reason later.
*/
// ************************

// We used a struct to define a Date object. We use a class to define a date object. You
// can observe how similar the two are sytactically.

/*
#include <iostream>
class Date{                // we changed struct to class
    public:                // and added this line, which is called an *** access specifier ***
    int m_day {};          // and added "m_" prefixes to each of the member names
    int m_month {};
    int m_year {};
};


void printDate(const Date& date){
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year << '\n';
}

int main(){
    Date date { 4 , 10 , 21 };
    printDate(date);

    return 0;
}
*/

// ----------- Most of the C++ standard library is classes ---------
// obkects like std::string, std:: string_view are class objects we have been using

// ---------------------------------- Member Functions ------------------------------------
// We have noticed that structs have member * variables *. Any class type (structs, classes, and
// unions) can also have member functions. 

#include <iostream>

struct Date{
    int year {};
    int month {};
    int day {};

    void print()            // defines a member function called print
    {
        std::cout << year << '/' << month << '/' << day << '\n';
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    today.print();  // member functions also accessed using member selection operator (.)

    return 0;
}


// There are three differences between member functions and non-member functions
/*
    1. Where we declare (and define) the print() function
    2. How we call the print() function
    3. How we access members inside the print() function
*/
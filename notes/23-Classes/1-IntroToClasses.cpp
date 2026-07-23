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

/*
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
*/


// There are three differences between member functions and non-member functions
/*
    1. Where we declare (and define) the print() function
    2. How we call the print() function
    3. How we access members inside the print() function
*/




// Member functions defined inside the class type definition are implicitly inline,
// so they will not cause violations of the one-definition rule if the class type
// definition is included into multiple code files.

// In the member example, we call today.print(). This syntax, which uses the 
// *** member selection operator (.) *** to select the member function to call, is consistent
// with how we access member variables (e.g. today.day = 16;).


// ----------- Member variables and functions can be defined in any order --------------
// The C++ compiler normally compiles code from top to bottom. For each name encountered,
// the compiler determines whether it has already seen a declaration for that name, so that
// it can do proper type checking.

// Non-members must be declared before they can be used, or the compiler will complain:
/*
int x()
{
    return y(); // error: y not declared yet, so compiler doesn't know what it is
}

int y()
{
    return 5;
}
*/

// To address this, we typically either define our non-members in rough order of use
// (which requires work whenever we need to change the order), or use forward declarations
// (which requires work to add).

// However, inside a class definition, this restriction doesn’t apply: you can access
// member variables and member functions before they are declared. This means you can define
// member variables and member functions in any order you like!

/*
struct Foo
{
    int z() { return m_data; } // We can access data members before they are defined
    int x() { return y(); }    // We can access member functions before they are defined

    int m_data { y() };        // This even works in default member initializers (see warning below)
    int y() { return 5; }
};
*/

/*
struct Foo
{
    int z() { return m_data; } // We can access data members before they are defined
    int x() { return y(); }    // We can access member functions before they are defined

    int m_data { y() };        // This even works in default member initializers (see warning below)
    int y() { return 5; }
};
*/

// it’s generally a good idea to avoid using other members inside default member initializers.
// Using uninitialized member variables inside member functions is ok but not other member vars


// ------------------------- Member functions can be overloaded -----------------------------
/*
#include <iostream>
#include <string_view>

struct Date {
    int year {};
    int month {};
    int date {};

    void print(){
        std::cout << year << '/' << month << '/' << date;
    }

    void print(std::string_view prefix){
        std::cout << prefix << year << '/' << month << '/' << date;
    }

};


int main(){
    Date today { 2020, 10, 14 };

    today.print(); // calls Date::print()
    std::cout << '\n';

    today.print("The date is: "); // calls Date::print(std::string_view)
    std::cout << '\n';

    return 0;
}
*/



// --------------------------- Class types with no data members -----------------------------
// It is possible to create class types with no data members (e.g. class types that only have
// member functions). It is also possible to instantiate objects of such a class type:

/*
#include <iostream>

struct Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo f{};
    f.printHi(); // requires object to call

    return 0;
}
*/


// However, if a class type does not have any data members, then using a class type is
// probably overkill. In such cases, consider using a namespace (containing non-member
// functions) instead. This makes it clearer to the reader that no data is being managed
// (and does not require an object to be instantiated to call the functions).

/*
#include <iostream>

namespace Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo::printHi(); // no object needed

    return 0;
}
*/

// ******* Best Practice ******** 
// ******* If your class type has no data members, prefer using a namespace. ********



/*
#include <iostream>

struct IntPair{
    int val1 {};
    int val2 {};

    void print(){
        std::cout << "Pair(" << val1 << ", " << val2 << ")\n";
    }

    bool isEqual(IntPair p){
        return (true ? (val1 == p.val1 & val2 == p.val2) : false);
    }
};


// Provide the definition for IntPair and the print() member function here

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();


    std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");
	return 0;
}
*/





// ----------------- Constant class objects and const member functions ---------------------
// Objects of fundamental types like int, double, char, etc. can be made constant via const
// keyword. All constant variables MUST be initialized at the time of definition

/*
const int x;      // compile error: not initialized
const int y{};    // ok: value initialized
const int z{ 5 }; // ok: list initialized
*/

/*  ************************************************************************************
    Similarly, class type objects (class, struct, unions) can be made constant using
    the const keyword. Such objects must also be initialized at the time of *creation*.
    Remember that creating in the class sense means when the *object* is created i.e.
    when the class itself is instantiated.
    ************************************************************************************
*/ 

/*
struct Date{
    int year {};
    int month {};
    int day {};
};

int main() {
    const Date today {2020 , 10 , 14}; // const class type object

    return 0;
}

*/

// Just like with normal variables, you’ll generally want to make your class type objects const
//  (or constexpr) when you need to ensure they aren’t modified after creation.

// -------------- Modifying the data members of const objects is disallowed ----------------
// Once a const class type object has been initialized, any attempt to modify the data
// members of the object is disallowed, as it would violate the const-ness of the object.
// This includes both changing member variables directly (if they are public), or calling
// member functions that set the value of member variables.

/*
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay()
    {
        ++day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.day += 1;        // compile error: can't modify member of const object
    today.incrementDay();  // compile error: can't call member function that modifies member of const object

    return 0;
}
*/

// ----------------- Const objects may not call non-const member functions ------------------
// You may be surprised to find that this code also causes a compilation error:

/*
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // compile error: can't call non-const member function

    return 0;
}
*/

// Even though print() does not try to modify a member variable, our call to today.print()
// is still a const violation. This happens because the print() member function itself is
// not declared as const. The compiler won’t let us call a non-const member function on a
// const object.


// To address the above issue, we need to make print() a const member function. A const
// member function is a member function that guarantees it will not modify the object or
// call any non-const member functions (as they may modify the object).
// Making print() a const member function is easy -- we simply append the const keyword
// to the function prototype, after the parameter list, but before the function body:

// ***************************************** THIS IS SYNTAX-STRANGE
/*
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now a const member function
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // ok: const object can call const member function

    return 0;
}
*/


// A const member function that attempts to change a data member or call a non-const member
// function will cause a compiler error to occur. For example:

/*
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay() const // made const
    {
        ++day; // compile error: const function can't modify member
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.incrementDay();

    return 0;
}
*/



// *********************************************************************************
// Const member functions can modify non-members (such as local variables and function
// parameters) and call non-member functions per usual. The const only applies to members.
// *********************************************************************************


// ------------ Const member functions may be called on non-const objects --------------
/*
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // non-const

    today.print();  // ok: can call const member function on non-const object

    return 0;
}
*/

// Therefore, the *** best practice *** is the following
/*
    A member function that does not (and will not ever) modify the state of the object 
    should be made const, so that it can be called on both const and non-const objects.
*/

// ----------------- Member function const and non-const overloading -------------------
// Finally, although it is not done very often, it is possible to overload a member
// function to have a const and non-const version of the same function. This works
// because the const qualifier is considered part of the function’s signature, so two
// functions which differ only in their const-ness are considered distinct.

/*
#include <iostream>

struct Something
{
    void print()
    {
        std::cout << "non-const\n";
    }

    void print() const
    {
        std::cout << "const\n";
    }
};

int main()
{
    Something s1{};
    s1.print(); // calls print()

    const Something s2{};
    s2.print(); // calls print() const

    return 0;
}
*/

// This overloading of a member function is only done when we want the output in both constant
// and nonconstant version. This is pretty rare.



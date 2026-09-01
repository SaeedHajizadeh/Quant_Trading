// So far we have defined the member functions inside the body of the class. Such 
// implementations, if short, are ok. However, long and detailed implementations can
// clutter up the public interface of the class. For example, when writing a class for a
// transformer, you want to know about all the public member functions, e.g. data preparation,
// data split, training, validation, etc. in one look without worrying about implementations.
// In other words, when it comes to "using" the class, those implementation details do not
// matter. As an example:
/*
#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day)
        : m_year { year }
        , m_month { month }
        , m_day { day}
    {
    }

    void print() const { std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n"; }

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

int main()
{
    Date d { 2015, 10, 14 };
    d.print();

    return 0;
}
*/
// Even in this short problem, the implementations clutter up the intuition one gets about 
// what the class does.


// To help address this, C++ allows us to separate the “declaration” portion of the class
// from the “implementation” portion by defining member functions outside of the class
// definition.

// Here is the same Date class as above, with the constructor and print() member functions
// defined outside the class definition. Note that the prototypes for these member functions
// still exist inside the class definition (as these functions need to be declared as part of
// the class type definition), but the actual implementation has been moved outside:




/*
#include <iostream>

class Date{
    private:
        int m_year {};
        int m_month{};
        int m_day{};

    public:
        Date(int year, int month, int day); // constructor declaration

        void print() const;                 // print function declaration
 
        int getYear() const { return m_year; }
        int getMonth() const { return m_month; }
        int getDay() const { return m_day; }
};

Date::Date(int year, int month, int day)   // constructor definition
        : m_year { year }
        , m_month { month }
        , m_day { day }
 {
 }

 void Date::print() const           // print function definition
 {
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
 }

 int main()
{
    const Date d{ 2015, 10, 14 };
    d.print();

    return 0;
}
*/

// Member functions can be defined outside the class definition just like non-member
// functions. The only difference is that we must prefix the member function names with
// the name of the class type (in this case, Date::) so the compiler knows we’re defining
// a member of that class type rather than a non-member.

// Note that we left the access functions defined inside the class definition. Because
// access functions are typically only one line, defining these functions inside the
// class definition adds minimal clutter, whereas moving them outside the class definition
// would result in many extra lines of code. For this reason, the definitions of access
// functions (and other trivial, one-line functions) are often left inside the class definition.


// ---------------------- Putting class definitions in a header file -------------------------
// If you define a class inside a source (.cpp) file, that class is only usable within
// that particular source file. In larger programs, it’s common that we’ll want to use
// the classes we write in multiple source files.

// We have learned that we can put function declarations in a header files. Then we can
// #include those functions declarations into multiple code files (or even multiple projects).
// Classes are no different. A class definitions can be put in a header files, and then
// #included into any other files that want to use the class type.


// Unlike functions, which only need a forward declaration to be used, the compiler
// typically needs to see the full definition of a class (or any program-defined type)
// in order for the type to be used. This is because the compiler needs to understand
// how members are declared in order to ensure they are used properly, and it needs to be
// able to calculate how large objects of that type are in order to instantiate them.
// So our header files usually contain the full definition of a class rather than just a
// forward declaration of the class.




// ------------------------- Naming your class header and code files ----------------------
// Most often, classes are defined in header files of the same name as the class, and any
// member functions defined outside of the class are put in a .cpp file of the same name
// as the class.

// Here is our Date class again, broken into a .cpp and .h file:
/*
// Date.h
#ifndef DATE_H
#define DATE_H

class Date{
    private:
        int m_year{};
        int m_month{};
        int m_day{};
    
    public:
        Date(int year, int month, int day);

        void print() const;

        int getYear() const { return m_year; }
        int getMonth() const { return m_month; }
        int getDay() const { return m_day; }
}; 


#endif

// Date.cpp
#include "Date.h"     // #include header "filename" not header name DATE_H
#include <iostream>

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};
*/

// **************************************************************************************
/*
    Now any other header or code file that wants to use the Date class can simply #include
    "Date.h". Note that Date.cpp also needs to be compiled into any project that uses Date.h
    so that the linker can connect calls to the member functions to their definitions.
*/
// **************************************************************************************


// ------------------------- Best Practice ---------------------------
// Prefer to put your class definitions in a header file with the same name as the class.
// Trivial member functions (such as access functions, constructors with empty bodies,
// etc…) can be defined inside the class definition.

// Prefer to define non-trivial member functions in a source file with the same name as the class.
// -------------------------------------------------------------------


// Doesn’t defining a class in a header file violate the one-definition rule if the header
// is #included more than once?

// Types are exempt from the part of the one-definition rule (ODR) that says you can only
// have one definition per program. Therefore, there isn’t an issue #including class
// definitions into multiple translation units. If there was, classes wouldn’t be of much use.



// ------------------------------ Inline member functions ----------------------------------
// Member functions are not exempt from the ODR, so you may be wondering how we avoid ODR
// violations when member functions are defined in a header file (that may then be
// included into more than one translation unit).

// Member functions defined inside the class definition are implicitly inline. Inline
// functions are exempt from the one definition per program part of the one-definition rule.

// Member functions defined outside the class definition are not implicitly inline
// (and thus are subject to the one definition per program part of the one-definition rule).
// This is why such functions are usually defined in a code file (where they will only
// have one definition across the whole program).

// Alternatively, member functions defined outside the class definition can be left in
// the header file if they are made inline (using the inline keyword). Here’s our Date.h
// header again, with the member functions defined outside the class marked as inline:

// Our example with inline modifications look like below
/*
// Date.h
#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date{
    private:
        int m_year {};
        int m_month {};
        int m_day {};

    public:
        Date(int year , int month , int day);
        
        void print() const;

        int getYear() { return m_year; }
        int getMonth() { return m_month; }
        int getDay() { return m_day; }
};

inline Date::Date(int year , int month , int day)
        : m_year { year }
        , m_month { month }
        , m_day { day }
        {}

inline void Date::print() const
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};

#endif
*/

// This Date.h can be included into multiple translation units without issue.

// ********************************** Key Insight ****************************************
/*
    Functions defined inside the class definition are implicitly inline, which allows them
    to be #included into multiple code files without violating the ODR.

    Functions defined outside the class definition are not implicitly inline. They can be
    made inline by using the inline keyword.
*/
// ***************************************************************************************


// -------------------------- Inline expansion of member functions --------------------------
// The compiler must be able to see a full definition of a function in order to perform
// inline expansion. Most often, such functions (e.g. access functions) are defined inside
// the class definition. However, if you want to define a member function outside the class
// definition, but still want it to be eligible for inline expansion, you can define it as
// an inline function just below the class definition (in the same header file). That way
// the definition of the function is accessible to anybody who #includes the header.


// ------------------- So why not put everything in a header file? -------------------------
// You might be tempted to put all of your member function definitions into the header file,
// either inside the class definition, or as inline functions below the class definition.
// While this will compile, there are a couple of downsides to doing so.

// First, as mentioned above, defining members inside the class definition clutters up
// your class definition.

// Second, if you change any of the code in the header, then you’ll need to recompile
// every file that includes that header. This can have a ripple effect, where one minor
// change causes the entire program to need to recompile. The cost of recompilation can
// vary significantly: a small project may only take a minute or less to build, whereas
// a large commercial project can take hours.

// Conversely, if you change the code in a .cpp file, only that .cpp file needs to be
// recompiled. Therefore, given the choice, it’s generally better to put non-trivial code
// in a .cpp file when you can.

// There are a few cases where it might make sense to violate the best practice of
//putting the class definition in a header and non-trivial member functions in a code file.


// First, for a small class that is used in only one code file and not intended for general
// reuse, you may prefer to define the class (and all member functions) directly in the
// single .cpp file it is used in. This helps make it clear that the class is only used
// within that single file, and is not intended for wider use. You can always move the
// class to a separate header/code file later if you later find you want to use it in more
// than one file, or are finding that the class and member function definitions are cluttering
// your source file.

// Second, if a class only has a small number of non-trivial member functions that are unlikely
// to change, creating a .cpp file that contains only one or two definitions may not be worth
// the effort (as it clutters your project). In such cases, it may be preferable to make the
// member functions inline and place them beneath the class definition in the header.

// Third, in modern C++, classes or libraries are increasingly being distributed as
// “header-only”, meaning all of the code for the class or library is placed in a header
// file. This is done primarily to make distributing and using such files easier, as a
// header only needs to be #included, whereas a code file needs to be explicitly added
// to every project that uses it, so that it can be compiled. If intentionally creating a
// header-only class or library for distribution, all non-trivial member functions can be
// made inline and placed in the header file beneath the class definition.

// Finally, for template classes, template member functions defined outside the class
// are almost always defined inside the header file, beneath the class definition. Just
// like non-member template functions, the compiler needs to see the full template definition
// in order to instantiate it. 




// --------------------- Default arguments for member functions -----------------------------
// We discussed the best practice for default arguments of non-member functions: “If the
// function has a forward declaration (especially one in a header file), put the default
// argument there. Otherwise, put the default argument in the function definition.”

// Because member functions are always declared (or defined) as part of the class definition,
// the best practice for member functions is actually simpler: always put the default
// argument inside the class definition.



// -------------------------------------------------------------------------------------------
// -------------------------------- Nestetd Types (member types) -----------------------------
// -------------------------------------------------------------------------------------------

// Suppose we have a class type in which we need to utilize another user-defined type. This is
// the framework we are going to build now. Consider the following example
/*
#include <iostream>

// Below is a scoped enum type
enum class FruitType
{
    apple,
    banana,
    cherry,
};

class Fruit
{
    private:
        FruitType m_type {};
        int m_percentageEaten { 0 };

    public:
        Fruit(FruitType ftype)
        :   m_type { ftype }
        {
        }
    
        FruitType getType() { return m_type; }
        int getPercentageEaten() { return m_percentageEaten; }

        bool isCherry() { return m_type == FruitType::cherry; }
};

int main(){
    Fruit apple { FruitType::apple };

	if (apple.getType() == FruitType::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";
    std::cout << std::endl;

	return 0;
}
*/


// There’s nothing wrong with this program. But because enum class FruitType is meant to
// be used in conjunction with the Fruit class, having it exist independently of the class
// leaves us to infer how they are connected. 


// ----------------------------- Nested Types (member types) ---------------------------------
// So far we have seen that classes have two types of *members*: *data members* and 
// *member functions*. 

// Class types accept another kind of member: *nested type* or *member type*. To define a nested
// type you simply define the type inside the class, under the appropriate access specifier (e.g.
// public or private)
/*
#include <iostream>

class Fruit{
    public:
        // FruitType has been moved inside the class, under the public access specifier
        // We've also renamed it Type and made it an enum rather than an enum class
        enum Type
        {
            apple,
            cherry,
            banana,
        };

    private:
        Type m_type {};
        int m_percentageEaten { 0 };
        
    public:
        Fruit(Type f)
        :   m_type { f }
        {
        }

        Type getType() { return m_type; }
        int getPercentageEaten() { return m_percentageEaten; }

        // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
        bool isCherry() { return m_type == cherry; }
};

int main()
{
	// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
	Fruit apple { Fruit::apple };

	if (apple.getType() == Fruit::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

    std::cout << std::endl;

	return 0;
}
*/



// Few things to consider as the above nested type example is written: 
// 1. FruitType was changed to Fruit for reasons we will make clear
// 2. nested type Type is defined at the *top* of the class as nested types need to be
//    fully defined before being used. 
// 3. Nested types are defined using normal access rules. Nested types need to be defined 
//    with a public access specifier to be directly accessible by the public
// 4. Class types act as a *scope region* for names declared within. Therefore the fully
//    qualified name of Type is Fruit::Type, and the fully qualified name of the apple
//    enumerator is Fruit::apple.
// 5. Within the members of the class, we do not need to use the fully qualified name.
//    For example, in member function isCherry() we access the cherry enumerator without
//    the Fruit:: scope qualifier.

// Outside the class, we must use the fully qualified name (e.g. Fruit::apple)

// Finally, we changed our enumerated type from scoped to unscoped. Since the class
// itself is now acting as a scope region, it’s somewhat redundant to use a scoped
// enumerator as well. Changing to an unscoped enum means we can access enumerators
// as Fruit::apple rather than the longer Fruit::Type::apple we’d have to use if the
// enumerator were scoped.








// ---------------------------- Nested typedefs and type aliases ---------------------------------
// Before continuting, let's recall what a typedef is. In C++, typedef is a keyword used to
// create an alias or nickname for an existing data type. It does not create a new data type;
// it simply gives a new name to a type that already exists to make your code shorter, more
// readable, and easier to maintain. Syntax as follows
/*
typedef existing_type new_alias_name
*/

// Example Usecases:
// 1. Simplifying Long Standard Library Types
/*
#include <iostream>
#include <vector>
typedef std::vector<std::pair<std::string , int>> StudentList;
*/

// 2. Improving Readability for Native Types
/*
typedef unsigned long ulong;
ulong distance = 50000;
*/

// Now look at this exmaple:
/*
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int;

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {
    }

    const std::string& getName() { return m_name; }
    IDType getId() { return m_id; } // can use unqualified name within class
};

int main()
{
    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.getId() }; // must use fully qualified name outside class

    std::cout << john.getName() << " has id: " << id << '\n';

    return 0;
}
*/

// Exercise: What does this print?

// Note that inside the class we can just use IDType, but outside the class we must
// use the fully qualified name Employee::IDType.

// --------------------- Nested classes and access to outer class members ---------------------
// It is fairly uncommon for classes to have other classes as a nested type, but it is
// possible. In C++, a nested class does not have access to the this pointer of the outer
// (containing) class, so nested classes can not directly access the members of the outer
// class. Remember that "this" pointer is an internal mechanism through which C++ can 
// distinguish various instantiations of a class type apart from each other. 
// This is because a nested class can be instantiated independently of the outer
// class (and in such a case, there would be no outer class members to access!)

// However, because nested classes are members of the outer class, they can access any
// private members of the outer class that are in scope. Let's look at an example:

/*
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int;

    class Printer
    {
    public:
        void print(const Employee& e) const
        {
            // Printer can't access Employee's `this` pointer
            // so we can't print m_name and m_id directly
            // Instead, we have to pass in an Employee object to use
            // Because Printer is a member of Employee,
            // we can access private members e.m_name and e.m_id directly
            std::cout << e.m_name << " has id: " << e.m_id << '\n';
        }
    };

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name{ name }
        , m_id{ id }
        , m_wage{ wage }
    {
    }

    // removed the access functions in this example (since they aren't used)
};

int main()
{
    const Employee john{ "John", 1, 45000 };
    const Employee::Printer p{}; // instantiate an object of the inner class
    p.print(john);

    return 0;
}
*/



// ---------------------------- Nested types and forward declarations ---------------------------
// A nested type can be forward declared within the class that encloses it. The nested
// type can then be defined later, either within the enclosing class, or outside of it.
// For example:
/*
#include <iostream>

class outer
{
    public:
        class inner1;     // okay: forward declaration inside the enclosing class okay
        class inner1 {};  // okay: definition of forward declared type inside the enclosing class
        class inner2 {};  // okay: forward declaration inside the enclosing class okay
};

class inner2{};     // okay: definition of forward declared type outside the enclosing class

int main()
{
    return 0;
}
*/


// However, a nested type cannot be forward declared prior to the definition of the
// enclosing class.

/*
#include <iostream>

class outer;         // okay: can forward declare non-nested type
class outer::inner1; // error: can't forward declare nested type prior to outer class definition

class outer
{
public:
    class inner1{}; // note: nested type declared here
};

class outer::inner1; // okay (but redundant) since nested type has already been declared as part of outer class definition

int main()
{
    return 0;
}
*/


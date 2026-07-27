// Each member of a class type has a property called an access level that determines who can
// access that member.
// C++ has three different access levels: public, private, and protected.  We cover public and
// private in this less as the two most commonly used access levels

// Whenever a member is accessed, the compiler checks the access level if the member can
// be accessed. If the access is not permitted, the compiler will generate a compilation error.
// This access level system is sometimes referred to as *** access controls ***

// Members that have the public access level are called public members. Public members are members
// of a class type that do not have any restrictions on how they can be accessed. Public members
// can be accessed by other members of the same class. Notably, public members can also be
// accessed by the public, which is what we call code that exists outside the members of a
// given class type. Examples of the public include non-member functions, as well as the
// members of other class types.

// By default, all members of a **** struct **** are public members.

/*
#include <iostream>

struct Date
{
    // struct members are public by default, can be accessed by anyone
    int year {};       // public by default
    int month {};      // public by default
    int day {};        // public by default

    void print() const // public by default
    {
        // public members can be accessed in member functions of the class type
        std::cout << year << '/' << month << '/' << day;
    }
};

// non-member function main is part of "the public"
int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    // public members can be accessed by the public
    today.day = 16; // okay: the day member is public
    today.print();  // okay: the print() member function is public

    return 0;
}
*/


// ------------------ The members of a class are private by default ------------------------
// Members that have the private access level are called private members. *** Private members ***
// are members of a class type that can only be accessed by other members of the same class.

/*
#include <iostream>

class Date // now a class instead of a struct
{
    // class members are private by default, can only be accessed by other members
    int m_year {};     // private by default
    int m_month {};    // private by default
    int m_day {};      // private by default

    void print() const // private by default
    {
        // private members can be accessed in member functions
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization

    // private members can not be accessed by the public
    today.m_day = 16; // compile error: the m_day member is private
    today.print();    // compile error: the print() member function is private

    return 0;
}
*/


// The most unexpected part was the compilation error when doing aggregate initialization. 
// Private members are a promise that outside code can't reach in and set them directly.
// If aggregate init still worked, { 2020, 10, 14 } would be a wide-open backdoor that writes
// straight into your private state, bypassing any invariant you wanted to enforce
// (like "month must be 1–12"). So types with private data are simply excluded from
// aggregate-ness rather than being given a special-case exception.

// Below is not aggregate initialization but rather value initialization and works for private
/*
Date today {};  // still compiles
*/ 

// This aggregate initialization prohibition is about access level not class vs struct type
/*
struct Foo { private: int x; };  // also NOT an aggregate
class Bar  { public:  int x; };  // IS an aggregate
*/




// ---------------------- Naming your private member variables -----------------------------
// In C++, it is a common convention to name private data members starting with an “m_” prefix.
// This is done for a couple of important reasons.

// 1st reason:
// Consider the following member function of some class:
/*
// Some member function that sets private member m_name to the value of the name parameter
void setName(std::string_view name)
{
    m_name = name;
}
*/

// First, the “m_” prefix allows us to easily differentiate data members from function
// parameters or local variables within a member function. We can easily see that “m_name”
// is a member, and “name” is not. This helps make it clear that this function is changing
// the state of the class. And that is important because when we change the value of a data
// member, it persists beyond the scope of the member function (whereas changes to function
// parameters or local variables typically do not).

// This is the same reason we recommend using “s_” prefixes for local static variables,
// and “g_” prefixes for globals.

// 2nd reason:
// The “m_” prefix helps prevent naming collisions between private member variables
// and the names of local variables, function parameters, and member functions.


// ***********************************************************************************
// By default, the members of structs (and unions) are public, and the members of
// classes are private.
// ***********************************************************************************

// However, we can explicitly set the access level of our members by using an
// *** access specifier ***. An access specifier sets the access level of all members
// that follow the specifier. C++ provides three access specifiers: public:, private:, and
// protected: 

/*
class Date
{
// Any members defined here would default to private

public: // here's our public access specifier

    void print() const // public due to above public: specifier
    {
        // members can access other private members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }

private: // here's our private access specifier

    int m_year { 2020 };  // private due to above private: specifier
    int m_month { 14 }; // private due to above private: specifier
    int m_day { 10 };   // private due to above private: specifier
};

int main()
{
    Date d{};
    d.print();  // okay, main() allowed to access public members

    return 0;
}
*/

// we can access print() because it has been attached with a public access specifier
// Because we have private members, we can not aggregate initialize d

// Since classes default to private access, you can delete the private specifier above
// It could be a good practice to still include private since it absolves us of having
// to chase to infer the access level of the members


// --------------------------- Access Level Summary ---------------------------------------
/*
Access level	Access specifier	Member access	Derived class access	Public access
Public	           public:	          yes           	   yes	                yes
Protected	       protected:	      yes	               yes                	no
Private            private:	          yes	               no	                no
*/


// ------------------------------ Access Level Best Practices --------------------------------
// 1. Classes should generally make member variables private (or protected), and member
//    functions public.
// 2. Structs should generally avoid using access specifiers (all members will default
//    to public).


// --------- The technical and practical difference between structs and classes -----------
// A class defaults its members to private, whereas a struct defaults its members to public.
// That is it!!!



// As a rule of thumb, use a struct when all of the following are true:

//  1. You have a simple collection of data that doesn’t benefit from restricting access.
//  2. Aggregate initialization is sufficient.
//  3. You have no class invariants, setup needs, or cleanup needs.


/*
#include <iostream>
class Point3d{
    int m_x {};
    int m_y {};
    int m_z {};

    public:
        void setValues(int x , int y , int z){
            m_x = x;
            m_y = y;
            m_z = z;
        }
        void print(){
            std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">";
        }
};






int main()
{
    Point3d point;
    point.setValues(1, 2, 3);

    point.print();
    std::cout << '\n';

    return 0;
}
*/




// ----------------------------------- Access Functions -----------------------------------
// An *** access function *** is a trivial public member function whose job is to retrieve 
// or change the value of a private member variable.
// Access functions come in two flavors: *getters* and *setters*. *Getters* (also sometimes
// called *accessors*) are public member functions that return the value of a private member
// variable. *Setters* (also sometimes called *mutators*) are public member functions that
// set the value of a private member variable.

/*
#include <iostream>

class Date{
    int m_year {2020};
    int m_month {10};
    int m_day {14};

    public:
        void print()
        {
            std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
        }
        int getYear() const {return m_year;}    // getter for year
        void setYear(int year) {m_year = year;} // setter for year

        int getMonth() const  { return m_month; }     // getter for month
        void setMonth(int month) { m_month = month; } // setter for month

        int getDay() const { return m_day; }          // getter for day
        void setDay(int day) { m_day = day; }         // setter for day
};


int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';

    return 0;
}
*/



// Getters should provide “read-only” access to data. Therefore, the best practice is that
// they should return by either value (if making a copy of the member is inexpensive) or by
// const lvalue reference (if making a copy of the member is expensive).

// Returning data members by reference is a non-trivial topic. We'll cover it later.




// --------------- Member functions returning references to data members ------------------
// We have covered return by reference. In particular, we noted, “The object being returned
// by reference must exist after the function returns”. This means we should not return
// local variables by reference, as the reference will be left dangling after the local
// variable is destroyed. However, it is generally okay to return by reference either function
// parameters passed by reference, or variables with static duration (either static local
// variables or global variables), as they will generally not be destroyed after the function
// returns. Look at the example below for a reminder:
/*
// Takes two std::string objects, returns the one that comes first alphabetically
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

int main()
{
	std::string hello { "Hello" };
	std::string world { "World" };

	std::cout << firstAlphabetical(hello, world); // either hello or world will be returned by reference

	return 0;
}
*/

// These were the rules and constraints for ** non-member functions ** that also hold for 
// member functions. However, member functions have one additional case we need to discuss:
// *** member functions that return data members by reference. ***

// ------------------- Returning data members by value can be expensive ----------------------
/*
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	std::string getName() const { return m_name; } //  getter returns by value
};

int main()
{
	Employee joe{};
	joe.setName("Joe");
	std::cout << joe.getName();

	return 0;
}
*/

// In this example, the getName() access function returns std::string m_name by value.
// Solution:
// ------------------------- Returning data members by lvalue reference -----------------------
/*
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

int main()
{
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");

	std::cout << joe.getName(); // returns joe.m_name by reference

	return 0;
}
*/

// *******************************************************************************
// The return type of a member function returning a reference to a data member should
//  match the data member’s type.
// *******************************************************************************

// In general, the return type of a member function returning by reference should match
// the type of the data member being returned.

// If in the above code, for instance, the caller wants a std::string_view, they can do
// the conversion themselves.

//Returning a std::string_view would require a temporary std::string_view to be created
//  and returned every time the function was called. That’s needlessly inefficient. 



// One way to ensure that no conversion occurs is to use *** auto *** to have the compiler
// deduce the return type from the member being returned.

/*
#include <iostream>
#include <string> 

class Employee{
    std::string m_name {};    // a private (by default) member

    public:
        void setName(std::string_view name) { m_name = name; }
        // uses `auto` to deduce return type from m_name
        const auto& getName() const { return m_name; } 
        
};

int main(){
    Employee joe {};
    joe.setName("Joe");

    std::cout << joe.getName() << '\n';

    return 0;
}

*/

// However, using an auto return type obscures the return type of the getter from
// a documentation perspective. 

// It’s unclear what kind of string this function actually returns (it could be a
// std::string, std::string_view, C-style string, or something else entirely!).

// ********* For this reason, we’ll generally prefer explicit return types. *************


/* #######################################################################################
Question: In defining getName() member function below, should we not just return &m_name
instead of m_name itself?

Good question — this gets at a distinction that trips up a lot of people: the & in a type
means something completely different from the & used as an operator on a variable.

In the return type const auto&, the & declares the return type to be a *reference*. To return
a reference, you just return the object itself (m_name), and the compiler binds the reference
to it. You do *not* take its address.


The & in &m_name is the ***address-of operator***. It produces a pointer (std::string*),
which is a different thing entirely. If you wrote return &m_name;, you'd have a type
mismatch: you'd be trying to initialize a const std::string& (reference) from a
std::string* (pointer).
   #######################################################################################
*/









// In the above example, joe is an lvalue object that exists until the end of the main function.
// What if our implicit object is an rvalue instead (e.g. the return value of some function that
// returns by value)? Rvalue objects are destroyed at the end of the full expression in which
// they are created. When an rvalue object is destroyed, any references to members of that
// rvalue will be invalidated and left dangling, and use of such references will produce
// undefined behavior. Look at the example below


/*#include <iostream>
#include <string>
#include <string_view>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e;
	e.setName(name);
	return e;
}

int main()
{
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName() << '\n';

	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref << '\n'; // undefined behavior

	// Case 3: okay: copy referenced value to local variable for use later
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val << '\n'; // okay: val is independent of referenced member

	return 0;
}
*/

// When createEmployee() is called, it will return an Employee object by value. This returned
// Employee object is an rvalue that will exist until the end of the full expression
// containing the call to createEmployee(). When that rvalue object is destroyed, any
// references to members of that object will become dangling.

// In case 1, we call createEmployee("Frank"), which returns an rvalue Employee object.
// We then call getName() on this rvalue object, which returns a reference to m_name. This
// reference is then used immediately to print the name to the console. At this point, the
// full expression containing the call to createEmployee("Frank") ends, and the rvalue
// object and its members are destroyed. Since neither the rvalue object or its members
// are used beyond this point, this case is fine.

// In case 2, we run into problems. First, createEmployee("Garbo") returns an rvalue object.
// We then call getName() to get a reference to the m_name member of this rvalue. This m_name
// member is then used to initialize ref. At this point, the full expression containing the
// call to createEmployee("Garbo") ends, and the rvalue object and its members are destroyed.
// This leaves ref dangling. Thus, when we use ref in the subsequent statement, we’re accessing
// a dangling reference, and undefined behavior results.

// In case 3, we’re using the returned reference to initialize non-reference local variable
// val. This will cause the member being referenced to be copied into val. After initialization,
// val exists independently of the reference. So when the rvalue object is subsequently
// destroyed, val is not impacted by this. Thus val can be output in future statements
// without issue.

// Best practice: Case 1 above:
// Prefer to use the return value of a member function that returns by reference immediately,
// to avoid issues with dangling references when the implicit object is an rvalue.

// ------------ Do not return non-const references to private data members --------------
/*
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member

public:
    int& value() { return m_value; } // returns a non-const reference (don't do this)
};

int main()
{
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5
    std::cout << f.value(); // prints 5

    return 0;
}
*/


/*
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member

public:
    int& value() { return m_value; } // returns a non-const reference (don't do this)
};

int main()
{
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5
    std::cout << f.value() << '\n'; // prints 5

    return 0;
}
*/


// Because value() returns a non-const reference to m_value, the caller is able to use that
// reference to directly access (and change the value of) m_value.
// This allows the caller to subvert the access control system. : NOT GOOD!

// -------- Const member functions can’t return non-const references to data members ---------
// If a const member function was allowed to return a non-const reference to a member,
// it would be handing the caller a way to directly modify that member. This violates
// the intent of a const member function. Changing the function value() above to const creates
// a compile-time error
/*
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member

public:
    int& value() const { return m_value; } // compile error: cannot return nonconst reference
};

int main()
{
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5
    std::cout << f.value() << '\n'; // prints 5

    return 0;
}
*/



// ----------------- 14.8 — The benefits of data hiding (encapsulation) ---------------------
// TBD -- Later
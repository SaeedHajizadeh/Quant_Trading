// Let us first say what class types (unions, structs, and class) can be called an aggregate'
// type: 
// To be classified as an aggregate class, a structure or class must meet strict structural rules
//  that guarantee its simplicity:
// 1. No user-declared constructors (the compiler must completely handle construction).
// 2. All non-static data members must be public (no private or protected variables).
// 3. No virtual functions (ensures a standard, straightforward memory layout).
// 4. No private/protected base classes (and restricted to public base classes only since C++17).

// Key Benefits:
// 1. *Aggregate Initialization*: You can instantly initialize its fields via a comma-separated
// list inside curly braces {}.
// 2. *Designated Initializers*: Since C++20, fields can be assigned explicitly by name
//  (e.g., .x = 10).
// 3. *Structured Binding*: Fields can be cleanly unpacked or decomposed directly into
// separate variables.

/*
#include <iostream>
#include <string>

// This is an aggregate class type
struct UserProfile {
    std::string username;
    int account_id;
    bool is_active;
};

int main() {
    // 1. Direct Aggregate Initialization
    UserProfile user1{"Alice", 9021, true}; 

    // 2. Designated Initialization (C++20 style)
    UserProfile user2{.username = "Bob", .account_id = 4432, .is_active = false};

    // 3. Structured Binding
    auto [name, id, active] = user1;
}

*/




// With that reminder, note that Aggregate inititalization does memberwise initialization
// (members are initialized in the order in which they are defined). So when foo is
// instantiated in the above example, foo.x is initialized to 6, and foo.y is initialized to 7.

// However, as soon as we make any member variables private (to hide our data), our class
// type is no longer an aggregate (because aggregates cannot have private members). And
// that means we’re no longer able to use aggregate initialization:

/*
class Foo // Foo is not an aggregate (has private members)
{
    int m_x {};
    int m_y {};
};

int main()
{
    Foo foo { 6, 7 }; // compile error: can not use aggregate initialization

    return 0;
}
*/

// Not allowing class types with private members to be initialized via aggregate initialization
// makes sense for a number of reasons:
// 1. Aggregate initialization requires knowing about the implementation of the class (since
// you have to know what the members are, and what order they were defined in), which we’re
// intentionally trying to avoid when we hide our data members.
// 2. If our class had some kind of invariant, we’d be relying on the user to initialize the
// class in a way that preserves the invariant.

// *************************************************************************************
/*
So then how do we initialize a class with private member variables? The error message given
by the compiler for the prior example provides a clue: “error: no matching constructor for
initialization of ‘Foo'”
*/
// *************************************************************************************


// We must need a matching constructor. But what the heck is that?
// A ***constructor*** is a special *member function* that is automatically called after a
// non-aggregate class type object is created.

// For those familiar with Python, when you are definitng a class, the member function
// __init__ is your constructor. 

// When a non-aggregate class type object is defined, the compiler looks to see if it can
// find an accessible constructor that is a match for the initialization values provided
// by the caller (if any).
// 1. If an accessible matching constructor is found, memory for the object is allocated,
//    and then the constructor function is called.
// 2. If no accessible matching constructor can be found, a compilation error will be generated.


// ***************************************************************************************
/*
Many new programmers are confused about whether constructors create the objects or not.
They do not -- the compiler sets up the memory allocation for the object prior to the
constructor call. The constructor is then called on the uninitialized object.
*/
// ***************************************************************************************

// Beyond determining how an object may be created, constructors generally perform two functions:
// 1. They typically perform initialization of any member variables (via a
//    member initialization list)
// 2. They may perform other setup functions (via statements in the body of the constructor).
//    This might include things such as error checking the initialization values, opening a
//    file or database, etc…


// **********************
// After the constructor finishes executing, we say that the object has been “constructed”,
// and the object should now be in a consistent, usable state.
// **********************


// Note that aggregates are not allowed to have constructors -- so if you add a constructor
// to an aggregate, it is no longer an aggregate.


// ----------------------------------- Naming Constructors ----------------------------------
// Unlike normal member functions, constructors have specific rules for how they must be named:
// 1. Constructors must have the same name as the class (with the same capitalization).
//    For template classes, this name excludes the template parameters.
// 2. Constructors have no return type (not even void).

// constructors are a part of your class definition so are usually public

// ---------------------------- A basic constructor example -------------------------------
// The only thing you need to do is to define a member function with exactly the same name
// as your class name (and usually set to be public)


/*
 #include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y) // here's our constructor function that takes two initializers
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
    foo.print();

    return 0;
}
 */


/*
output:
    Foo(6, 7) constructed
    Foo(0, 0)
*/


/*
When the compiler sees the definition Foo foo{ 6, 7 }, it looks for a matching Foo constructor
that will accept two int arguments. Foo(int, int) is a match, so the compiler will allow the
definition.

At runtime, when foo is instantiated, memory for foo is allocated, and then the Foo(int, int)
constructor is called with parameter x initialized to 6 and parameter y initialized to 7.
The body of the constructor function then executes and prints Foo(6, 7) constructed.

When we call the print() member function, you’ll note that members m_x and m_y have value 0.
 This is because although our Foo(int, int) constructor function was called, it did not
 actually initialize the members. We’ll show how to do that in the next lesson.
*/


// ------------------ Constructor implicit conversion of arguments --------------------------
// the compiler will perform implicit conversion of arguments in a function call (if needed)
// in order to match a function definition where the parameters are a different type:
/*
void foo(int, int)
{
}

int main()
{
    foo('a', true); // will match foo(int, int)

    return 0;
}
*/


// This is no different for constructors: the Foo(int, int) constructor will match any
// call whose arguments are implicitly convertible to int:

/*
class Foo
{
public:
    Foo(int x, int y)
    {
    }
};

int main()
{
    Foo foo{ 'a', true }; // will match Foo(int, int) constructor

    return 0;
}
*/




// ---------------------------- Constructors should not be const ----------------------------
// A constructor needs to be able to initialize the object being constructed -- therefore,
// a constructor must not be const.

/*
#include <iostream>

class Something
{
private:
    int m_x{};

public:
    Something() // constructors must be non-const
    {
        m_x = 5; // okay to modify members in non-const constructor
    }

    int getX() const { return m_x; } // const
};

int main()
{
    const Something s{}; // const object, implicitly invokes (non-const) constructor

    std::cout << s.getX(); // prints 5

    return 0;
}
*/



// Normally a non-const member function can’t be invoked on a const object. However,
// the C++ standard explicitly states (per class.ctor.general#5) that const doesn’t
// apply to an object under construction, and only comes into effect after the constructor ends.

// -------------------------------- Constructors vs setters ---------------------------------
// Constructors are designed to initialize an entire object at the point of instantiation.
// Setters are designed to assign a value to a single member of an existing object.


// -------------------------------------------------------------------------------------------
// -------------------------- Constructor member initializer lists ---------------------------
// -------------------------------------------------------------------------------------------

// ------------------ Member initialization via a member initialization list -----------------
// To have a constructor initialize members, we do so using a *member initializer list*
// (often called a “member initialization list”). Do not confuse this with the similarly
// named “initializer list” that is used to initialize aggregates with a list of values.
// Member initialization lists are something that is best learned by example. In the
// following example, our Foo(int, int) constructor has been updated to use a member
// initializer list to initialize m_x, and m_y:

/*
#include <string>

class Player {
private:
    std::string name;
    int score;

public:
    // Member initialization list starts with ':'
    Player(std::string p_name, int p_score) : name{p_name}, score{p_score} {
        // Constructor body remains empty or handles secondary tasks
    }
};
*/

// You must use a direct form of initialization here (preferably using braces, but
// parentheses works as well) -- using copy initialization (with an equals) does not
// work here. Also note that the member initializer list does not end in a semicolon.

// Another example:
/*
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
*/

/*
output:
Foo(6, 7) constructed
Foo(6, 7)
*/

// ------------------------- Member initializer list formatting ----------------------------
// The following styles are all valid (and you’re likely to see all three in practice):

/*
Foo(int x, int y) : m_x { x }, m_y { y }
{
}



Foo(int x, int y) : m_x { x }, m_y { y }
{
}




Foo(int x, int y)
    : m_x { x }
    , m_y { y }
{
}
*/

// We recommend the third style
// Put the colon on the line after the constructor name, as this cleanly separates the member
// initializer list from the function prototype.
// Indent your member initializer list, to make it easier to see the function names.

// ------------------------------- Member initialization order --------------------------------
// By default, the members in a members initializers list are initialized in the order that
// they are defined. Changing this order leads to subtle errors.

/*
#include <algorithm>       // for std::max
#include <iostream>

class Foo
{
    private:
        int m_x {};
        int m_y {};

    public:
        Foo(int x , int y)
            : m_y { std::max(x , y) } , m_x { m_y } // issue on this line
        {
        }

        void print() const
        {
            std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
        }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
*/

// In the above example, our intent is to calculate the larger of the initialization values
// passed in (via std::max(x, y) and then use this value to initialize both m_x and m_y.
// However, on the author’s machine, the following result is printed:
// Foo(0, 7)
// What happened? Even though m_y is listed first in the member initialization list,
// because m_x is defined first in the class, m_x gets initialized first. And m_x gets
// initialized to the value of m_y, which hasn’t been initialized yet (which means that
// it is value initialized to 0). So best practice is:

// Member variables in a member initializer list should be listed in order that they are
// defined in the class.

// It’s also a good idea to avoid initializing members using the value of other members
// (if possible). That way, even if you do make a mistake in the initialization order,
// it shouldn’t matter because there are no dependencies between initialization values.

// ----------------- Member initializer list vs default member initializers -----------------
// If a member has both a default member initializer and is listed in the member initializer list
// for the constructor, the member initializer list value takes precedence.


/*
#include <iostream>

class Foo
{
private:
    int m_x {};      // default member initializer (will be ignored)
    int m_y { 2 };   // default member initializer (will be used)
    int m_z;         // no initializer

public:
    Foo(int x)
        : m_x { x } // member initializer list
    {
        std::cout << "Foo constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }
};

int main()
{
    Foo foo { 6 };
    foo.print();

    return 0;
}
*/

// Here’s what’s happening. When foo is constructed, only m_x appears in the member initializer
// list, so m_x is first initialized to 6. m_y is not in the member initialization list, but
// it does have a default member initializer, so it is initialized to 2. m_z is neither in the
// member initialization list, nor does it have a default member initializer, so it is
// default-initialized (which for fundamental types, means it is left uninitialized).




// -------------------------------- Constructor function bodies --------------------------------
// The bodies of constructors functions are most often left empty. This is because we primarily
// use constructor for initialization, which is done via the member initializer list. If that
// is all we need to do, then we don’t need any statements in the body of the constructor.

// However, because the statements in the body of the constructor execute after the member
// initializer list has executed, we can add statements to do any other setup tasks required.

// New programmers sometimes use the body of the constructor to assign values to members:

/*
#include <iostream>

class Foo
{
private:
    int m_x { 0 };
    int m_y { 1 };

public:
    Foo(int x, int y)
    {
        m_x = x; // incorrect: this is an assignment, not an initialization
        m_y = y; // incorrect: this is an assignment, not an initialization
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
*/



// Although in this simple case this will produce the expected result, in case where members
// are required to be initialized (such as for data members that are const or references)
// assignment will not work.

// Best practice
// Prefer using the member initializer list to initialize your members over assigning values
// in the body of the constructor.

// ------------------ Detecting and handling invalid arguments to constructors -------------------
// We have seen that structs have no way of preserving class invariant, i.e. for the class type
// to remain valid. Classes do. Consider the following
/*
class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};

public:
    Fraction(int numerator, int denominator):
        m_numerator { numerator }, m_denominator { denominator }
    {
    }
};
*/

// In order for the class Fraction to be in a valid state, the denuminator need to be nonzero.
// So what do we do when the user tries to create a Fraction with a zero denominator
// (e.g. Fraction f { 1, 0 };)?

// Inside a member initializer list, our tools for detecting and handling errors are quite
// limited. We can use the conditional operator to detect an error, but then what?

/*
class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};

public:
    Fraction(int numerator, int denominator):
        // // what do we do here?
        m_numerator { numerator }, m_denominator { denominator != 0.0 ? denominator : ??? } 
    {
    }
};
*/

// We could change the denominator to a valid value, but then the user is going to get a
// Fraction that doesn’t contain the values they asked for, and we don’t have any way to
// notify them that we did something unexpected. Thus, we typically won’t try to do any
// kind of validation in the member initializer list -- we’ll just initialize the members
// with the values passed in, and then try to deal with the situation.

// Inside the body of the constructor, we can use statements, so we have more options for
// detecting and handling errors. This is a good place to assert or static_assert that the
// arguments passed in are semantically valid, but that doesn’t actually handle runtime errors
// in a production build.

// When a constructor cannot construct a semantically valid object, we say it has failed.


// ---------------------- When constructors fail (a prelude) --------------------------------
// Key insight
// Throwing an exception is usually the best thing to do when a constructor fails
// (and cannot recover). Other solutions


#include <iostream>

class Ball{
    private:
        std::string m_color {"none"};
        double m_radius {0.0};

    public:
        Ball(std::string_view c , double r)
            : m_color {c}
            , m_radius { r }
            {
            }
        void print(Ball b){
            
        }
        const std::string& getColor() const {return m_color;}
        const double& getRadius() const {return m_radius;}

};

void print(const Ball& b) {
            std::cout << "Ball(" << b.getColor() << ", " << b.getRadius() << ")" << '\n';
        }


int main()
{
	Ball blue { "blue", 10.0 };
	print(blue);

	Ball red { "red", 12.0 };
	print(red);

	return 0;
}


// let’s say you’re writing a program that needs to keep track of whether an apple is red,
// yellow, or green, or what color a shirt is (from a preset list of colors). You might store
// the color as an integer value, using some kind of implicit mapping
// (0 = red , 1 = green, 2 = blue):


// An enumeration (also called an enumerated type or an enum) is a compound data type whose
// values are restricted to a set of named symbolic constants (called enumerators).

// C++ supports two kinds of enumerations: unscoped enumerations (which we’ll cover now) 
// and scoped enumerations (which we’ll cover later in this chapter). Each enumeration needs
// to be fully defined before we can use it (a forward declaration is not sufficient).

// Unscoped enumerations are defined via the enum keyword.

// Have in mind that enumeration is a *** type *** like int, double, std::string etc
// Define a new unscoped enumeration named Color

/*
enum Color {
    // These symbolic constants define all the possible values this type can hold
    red, 
    green,
    blue,   // trailing comma optional but recommended
};          // definition must end w a semicolon

int main(){
    // Define a few variables of enumerated type Color
    Color apple { red };
    Color shirt { green };
    Color eyes { blue };

    Color socks { white }; // error since white is not an enumerator of Color
    Color hat {2 };        // error since 2 is not an enumerator of Color

    return 0;
}
*/




// ********* Best Practice *********
// Name your enumerated types starting with a capital letter. Name your enumerators starting
// with a lower case letter.



// Each enumerated type you create is considered to be a distinct type, meaning the compiler
// can distinguish it from other types. Because enumerated types are distinct, enumerators
// defined as part of one enumerated type can’t be used with objects of another enumerated type:
/*
enum Pet
{
    cat,
    dog,
    pig,
    whale,
};

enum Color
{
    black,
    red,
    blue,
};

int main()
{
    Pet myPet { black }; // compile error: black is not an enumerator of Pet
    Color shirt { pig }; // compile error: pig is not an enumerator of Color

    return 0;
}
*/



// Enumerations are used to describe a documentatio
/*
enum DaysOfWeek
{
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
};

enum CardinalDirections
{
    north,
    east,
    south,
    west,
};

enum CardSuits
{
    clubs,
    diamonds,
    hearts,
    spades,
};
*/



// One application of enum is to explain errors in a code clearly. For example, having
/*
int readFileContents()
{
    if (!openFile())
        return -1;
    if (!readFile())
        return -2;
    if (!parseFile())
        return -3;

    return 0; // success
}
*/
// is not very descriptive since erros are sheer numbers. However, using enumerations
/*
enum FileReadResult
{
    readResultSuccess,
    readResultErrorFileOpen,
    readResultErrorFileRead,
    readResultErrorFileParse,
};

FileReadResult readFileContents()
{
    if (!openFile())
        return readResultErrorFileOpen;
    if (!readFile())
        return readResultErrorFileRead;
    if (!parseFile())
        return readResultErrorFileParse;

    return readResultSuccess;
}
*/
// which results in more descriptive error handling messages. We can also use it to test the error
/*
if (readFileContents() == readResultSuccess)
{
    // do something
}
else
{
    // print error message
}
*/


// ---------------------------- Scope of unscoped enumerations ----------------------------
// Unscoped enumeration are named such because they put the enumeration names in the same scope
// they put the enumeration definition in. Look at codes above
// One consequence of this is that any enumerator name that is used once cannot be used again
// since they are defined at the global scope. This also creates global scope pollution.
/*
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

enum Feeling
{
    happy,
    tired,
    blue, // error: naming collision with the above blue
};

int main()
{
    Color apple { red }; // my apple is red
    Feeling me { happy }; // I'm happy right now (even though my program doesn't compile)

    return 0;
}
*/




// Unscoped enumerations also provide a named scope region for their enumerators
// This means we can access the enumerators of an unscoped enumeration as follows:
/*
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

int main()
{
    Color apple { red }; // okay, accessing enumerator from global namespace
    Color raspberry { Color::red }; // also okay, accessing enumerator from scope of Color

    return 0;
}
*/



// ------------------ avoiding enumerator naming collision ------------------------
// Best practice to avoid naming collision is to wrap the enumerating definition inside a
// different scope region, say a namespace
/*
namespace Colro{
    enum Color {
        red,
        blue,
        green,
    };
}

namespace Feeling{
    enum Feeling{
        happy,
        tired,
        blue,   // Feeling::blue does not collide with Color::blue
    };
}


int main()
{
    Color::Color paint{ Color::blue };
    Feeling::Feeling me{ Feeling::blue };

    return 0;
}
*/

// We can use equality operators (operator== and operator!=) to test whether an enumerations has
// the value of a particular enumerator
/*
#include <iostream>

enum Color {
    red,
    green,
    blue,
};

int main() {
    Color shirt { blue };

    if (shirt == blue )
        std::cout << "You shirt is blue!";
    else
        std::cout << "Your shirt is not blue!";

    std::cout << std::endl;

    return 0;
}
*/


// ------------------------- Unscoped enumerators integral conversions -------------------------
// We know enumerators are symbolic constants. Do they have values of integral type?
// This is similar to chars. For example
/*
char c { 'A' };
*/
// is really just a 1-byte integral value. The character 'A' is converted into an integral
// value (which is 65 in this case) and stored.

// When we define an enumeration, each enumerator is automatically associated with an integer
// value based on its position in the enumeration list. By default, these integral values start
// from 0 and move onwards
/*
enum Color {
    black,   // 0
    red,     // 1
    blue,    // 2
    green,   // 3
    white,   // 4
    cyan,    // 5
    yellow,  // 6
    magenta, // 7
};

int main()
{
    Color shirt{ blue }; // shirt actually stores integral value 2

    return 0;
}
*/

// It is possible to explicitly define the value of enumerators. These integral values can
// be positive or negative, and can share the same value as other enumerators. Any non-defined
// enumerators are given a value one greater than the previous enumerator.
/*
enum Animal
{
    cat = -3,    // values can be negative
    dog,         // -2
    pig,         // -1
    horse = 5,
    giraffe = 5, // shares same value as horse
    chicken,     // 6
};
*/

// Note in this case, horse and giraffe have been given the same value. When this happens,
// the enumerators become non-distinct -- essentially, horse and giraffe are interchangeable.
// Although C++ allows it, assigning the same value to two enumerators in the same enumeration
// should generally be avoided.

// *** best practice *** Avoid assigning explicit values to your enumerators unless you have
//  a compelling reason to do so.

// If an enumeration is zero-initialized (which happens when we use value-initialization),
// the enumeration will be given value 0

/*
#include <iostream>

enum Animal
{
    cat = -3,    // -3
    dog,         // -2
    pig,         // -1
    // note: no enumerator with value 0 in this list
    horse = 5,   // 5
    giraffe = 5, // 5
    chicken,     // 6
};

int main()
{
    Animal a {}; // value-initialization zero-initializes a to value 0
    std::cout << a; // prints 0

    return 0;
}
*/


// *** best practice ***
// Make the enumerator representing 0 the one that is the best default meaning for your
// enumeration. If no good default meaning exists, consider adding an “invalid” or “unknown”
// enumerator that has value 0, so that state is explicitly documented and can be explicitly
// handled where appropriate.





// ------------------------ Implicit conversion to integral value ---------------------------
// Enumerations store integral values but they are not of integral type: they are of a 
// compound type. However, an unscoped enumeration will implicitly convert to an integral value
// Please have in mind that enumerators are compile-time constants so this is a constexpr 
// conversion

// Notice that the operator<< knows how to print a char type to std::cout so we see a printed
/*
#include <iostream>
int main() {
    char c { 'a' };

    std::cout << c << std::endl;   // a

    return 0;
}
*/


// BUT
/*
#include <iostream>

enum Color
{
    black, // assigned 0
    red, // assigned 1
    blue, // assigned 2
    green, // assigned 3
    white, // assigned 4
    cyan, // assigned 5
    yellow, // assigned 6
    magenta, // assigned 7
};

int main()
{
    Color shirt{ blue };

    std::cout << "Your shirt is " << shirt << '\n'; // what does this do?

    return 0;
}
*/

// result: Your shirt is 2
// When the compiler tries to compile std::cout << shirt, the compiler will first look to see
// if operator<< knows how to print an object of type Color (because shirt is of type Color)
// to std::cout. It doesn’t. Since the compiler can’t find a match, it will then then check
// if operator<< knows how to print an object of the integral type that the unscoped enumeration
// converts to. Since it does, the value in shirt gets converted to an integral value and
// printed as integral value 2.



// ------------------ Enumeration size and underlying type (base) ---------------------
// Enumerators have values that are of an integral type. But what integral type? The specific
// integral type used to represent the value of enumerators is called the enumeration’s
// underlying type (or base).

// For unscoped enumerations, the C++ standard does not specify which specific integral type
// should be used as the underlying type, so the choice is implementation-defined. Most
// compilers will use int as the underlying type (meaning an unscoped enum will be the same
// size as an int), unless a larger type is required to store the enumerator values. But
// you shouldn’t assume this will hold true for every compiler or platform.
// It is possible to explicitly specify an underlying type for an enumeration. The underlying
// type must be an integral type. For example, if you are working in some bandwidth-sensitive
// context (e.g. sending data over a network) you may want to specify a smaller type for your
// enumeration:


/*
#include <cstdint>  // for std::int8_t
#include <iostream>

// Use an 8-bit integer as the enum underlying type
enum Color : std::int8_t
{
    black,
    red,
    blue,
};

enum Color32 
{
    green,
    yellow,
};

int main()
{
    Color c{ black };
    Color32 x { green };

    std::cout << sizeof(c) << '\n'; // prints 1 (byte)
    std::cout << sizeof(x) << '\n'; // prints 4 (bytes)

    return 0;
}
*/


// **** best practice **** Specify the base type of an enumeration only when necessary.

// While the compiler will implicitly convert an unscoped enumeration to an integer, it
// will not implicitly convert an integer to an unscoped enumeration.

/*
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
    pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

    return 0;
}
*/



// How to get around this???? 

// Method 1: Explicitly convert an integer to an unscoped enumerator using static_cast:
enum Pet // no specified base
{
    cat,    // assigned integral value 0
    dog,    // assigned integral value 1
    pig,    // assigned integral value 2
    whale,  // assigned integral value 3
};

int main() {
    Pet pet { static_cast<Pet>(2) };
    pet = static_cast<Pet>(3);

    return 0;
}


// It is safe to static_cast any integral value that is represented by an enumerator of the
// target enumeration. Since our Pet enumeration has enumerators with values 0, 1, 2, and 3,
// static_casting integral values 0, 1, 2, and 3 to a Pet is valid.

// We will skip method 2
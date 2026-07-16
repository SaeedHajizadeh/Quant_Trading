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



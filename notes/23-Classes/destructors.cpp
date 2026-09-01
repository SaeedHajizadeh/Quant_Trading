// Just as a constructor is a special member function that is called when an object is created,
// a destructor is a special member function that is called when an object is destroyed.
// The purpose of a destructor is to perform any necessary cleanup tasks before the object
// is removed from memory e.g. maybe the object has allocated some dynamic memory or
// opened a file, and the destructor is responsible for releasing that memory or closing the
// file when the object is no longer needed.

// Like constructors, destructors have specific naming rules:
/*
    1. A destructor has the same name as the class, but it is preceded by a tilde (~).
    2. A destructor does not take any parameters
    3. A destructor does not return a value, not even void.
*/

// A class can only have a single destructor.

// Generally you should not call a destructor explicitly (as it will be called automatically
// when the object is destroyed), since there are rarely cases where you’d want to clean up
// an object more than once.

// Destructors may safely call other member functions since the object isn’t destroyed
// until after the destructor executes.

#include <iostream>

class Simple {
    private:
        int m_value;

    public:
        // Building the constructor and destructor for the Simple class
        Simple(int value) : m_value { value } {
            std::cout << "Constructing Simple: " << m_value << std::endl;
        }

        ~Simple() {
            std::cout << "Destructing Simple: " << m_value << std::endl;
        }

        int getValue() const { return m_value; }
};

int main() {

    // Allocate simple1
    Simple simple1 { 5 };

    {
        Simple simple2 { 10 };
    }   // simple2 dies here, and its destructor is called automatically

    std::cout << "simple1 is still alive: " << simple1.getValue() << std::endl;

    return 0;

}   // simple1 dies here, and its destructor is called automatically





// ----------------------------- An implicit destructor ------------------------------
// If a non-aggregate class type object has no user-declared destructor, the compiler will
// generate a destructor with an empty body. This destructor is called an implicit destructor,
// and it is effectively just a placeholder.

//If your class does not need to do any cleanup on destruction, it’s fine to not define
// a destructor at all, and let the compiler generate an implicit destructor for your class.


// We have seen that static member variables are shared by all instances of a class. 
// Moreover, if a static member variable is declared as public, it can be accessed directly
// using the class name and the scope resolution operator, without creating an object of the class.
/*
#include <iostream>
class Something {
    public:
        static inline int s_value { 1 }; // declare and initialize s_value as static
};

int main() {
    // note: we're not instantiating any objects of type Something
    std::cout << Something::s_value << '\n';
    return 0;
}
*/

// What if a static member variable is private? We cannot access that through the class
// name and the scope resolution operator.

/*
#include <iostream>
class Something {
    private:
        static inline int s_value { 1 }; // declare and initialize s_value as static
};

int main() {
    std::cout << Something::s_value << '\n'; // error: s_value is private
    return 0;
}
*/


// Normally, we would need a public member function to access a private member variable. 
// While we could create a public member function to access a private static member variable,\
// in this case s_value, we would need to instantiate an object of the class to call that 
// member function. 
/*
#include <iostream>
class Something {
    private:
        static inline int s_value { 1 }; // declare and initialize s_value as static
    public:
        int getValue() const { return s_value; } // public member function 
};

int main() {
    Something object {};  // instantiate an object of type Something to access getValue()
    std::cout << object.getValue() << '\n'; // works, but we had to instantiate an object
    return 0;
}
*/





// In order to access a private static member variable without instantiating an object
// of the class, we can create a public static member function. 
/*
#include <iostream>
class Something {
    private:
        static inline int s_value { 22 }; // declare and initialize s_value as static
    public:
        static int getValue() { return s_value; } // public static member function
};

int main() {
    std::cout << Something::getValue() << '\n'; // works, and we did not have to instantiate

    return 0;
}
*/



// Since static member functions belong to the class itself rather than to any specific
// object instance, they operate at the class level and can even be called when zero
// instances of the class.

// When you call a standard non-static member function, the compiler automatically passes 
// the memory address of the calling object into the function as a hidden argument 
//(the this pointer). Because a static member function can be invoked using just the
//  class name (e.g., MyClass::myFunction()), there is no object instance to pass.
// As a result, the compiler does not generate a this pointer for it.

// --------------- Static members defined outside the class definition ----------------
// Static member functions can also be defined outside of the class declaration. This
// works the same way as for normal member functions.
/*
#include <iostream>
class IDGenerator {
    private:
        static inline int s_nextID { 1 }; // declare and initialize s_nextID as static
    public:
        static int getNextID(); // public static member function (declaration)
};

// Here is the definition of the static function outside of the class. Note that we
// do not use the static keyword here. 
int IDGenerator::getNextID() {
    return s_nextID++; // return the current value of s_nextID and then increment it
}

int main() {
    for (int count { 0 }; count < 5; ++count) {
        std::cout << "The next ID is: " << IDGenerator::getNextID() << "\n";
    }

    return 0;
}
*/



// As noted in lesson 15.2 -- Classes and header files, member functions defined inside
// the class definition are implicitly inline. Member functions defined outside the class
// definition are not implicitly inline, but can be made inline by using the inline keyword.
// Therefore a static member function that is defined in a header file should be made
// inline so as not to violate the One Definition Rule (ODR) if that header is then included
// into multiple translation units.
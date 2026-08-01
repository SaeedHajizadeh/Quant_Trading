// ---------------------------------------------------------------------------------------------
// --------------------- Hidden "this" Pointer -- Member Function Chaining ---------------------
// ---------------------------------------------------------------------------------------------

// When a member function is called, how does C++ keep track of which object it was called on?

// First, let’s define a simple class to work with. This class encapsulates an integer value,
// and provides some access functions to get and set that value:

/*
#include <iostream>

class Simple{
    private:
        int m_id {};

    public:
        Simple(int id)
        : m_id { id }
        {
        }

        int getID() { return m_id; }
        void setID(int id) { m_id = id; }

        void print() const { std::cout << m_id << '\n'; } 
};

int main(){

    Simple simple { 1 };
    simple.setID(4);

    simple.print();

    return 0;
}
*/


// The program above prints 2 as expected. 
// The question is how does C++ know which instantiation/object does the call of a member 
// function should invoke. This is done via the "this" pointer. "This" pointer is a hidden
// local pointer inside a non-static member function.  It stores the memory address of the
// specific object instance currently invoking that function.

// ------------------------------ The Hidden "this" Pointer -------------------------------
// Inside every member function, the keyword this is a ** const pointer *** that holds the 
// address of the current implicit object. Most of the time, we do not mention "this" but
// if we were to, we could:

#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    // // use `this` pointer to access the implicit object and operator-> to select 
    // member m_id
    void print() const { std::cout << this-> m_id << '\n'; }
};

int main()
{
    Simple simple{1};
    simple.setID(2);

    simple.print();

    return 0;
}


// This works exactly as the previous program
// The following two lines are equivalent:
/*
void print() const { std::cout << m_id; }       // implicit use of this
void print() const { std::cout << this->m_id; } // explicit use of this
*/

// It turns out that the former is shorthand for the latter. When we compile our programs,
// the compiler will implicitly prefix any member referencing the implicit object with
// this->. This helps keep our code more concise and prevents the redundancy from having
// to explicitly write this-> over and over.

// What happens behind the scenes when you call simple.setID(2)?
/*
    1. When we call simple.setID(2), the compiler actually calls Simple::setID(&simple, 2),
       and simple is passed by address to the function.
    2. The function has a hidden parameter named this which receives the address of simple.
    3. Member variables inside setID() are prefixed with this->, which points to simple. So
       when the compiler evaluates this->m_id, it’s actually resolving to simple.m_id.
*/

// All non-static member functions have a this const pointer that holds the address of
// the implicit object.

// ----------------- this always points to the object being operated on -------------------
// New programmers are sometimes confused about how many this pointers exist. Each member
// function has a single this pointer parameter that points to the implicit object. Consider:

/*
int main()
{
    Simple a{1}; // this = &a inside the Simple constructor
    Simple b{2}; // this = &b inside the Simple constructor
    a.setID(3); // this = &a inside member function setID()
    b.setID(4); // this = &b inside member function setID()

    return 0;
}
*/

// ------------------------------ Explicitly referencing this -------------------------------
// Skipping



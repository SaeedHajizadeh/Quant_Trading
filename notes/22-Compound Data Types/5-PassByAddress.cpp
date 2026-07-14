// In the previous chapters, we learned how to pass to a function a reference to an object instead
// of the object itself. This would save us the overhead of the function copying the object prior
// to processing it. In other words, pass by value vs pass by refeernce

/*
#include <iostream>
#include <string>

void printByValue(std::string val) { // The function parameter is a copy of str
    std::cout << val << std::endl;   // print the value via the copy
}

void printByReference(const std::string& ref) { // The function parameter is a reference that binds to str
    std::cout << ref << '\n'; // print the value via the reference
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str

    return 0;
}
*/

// If we pass by value: the function parameter val receives a new copy of the argument. This
// creates a computational overhead, but any changes made to the argument (string here), will
// NOT be made to the original object (string here).

// If we pass by reference, a reference to the object is passed as an argument to the function.
// No computational overhead, but any chaneg the function makes to the argument will be applied
// to the original object as well


// ----------------------------- Third way: pass by address ---------------------------------
// In this scheme, the caller does not provide the object itself as an argument, but rather the
// caller provides an object's "address" (via a pointer). The pointer stores the address to the
// object and is copied into the pointer parameter of the called function and the object can be
// easily accessed through dereferencing

/*
#include <iostream>
#include <string>


void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr){
    std::cout << *ptr << '\n';
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    return 0;
}
*/


// In the above, we passed the address of str: &str. We can also create the object prior to 
// calling the function. In that case, we can simply pass on the pointer object itself (which
// is a 4B or 8B holding the address to the original object).

// If the function parameter is a pointer to non-const, the function can modify the argument 
// via the pointer parameter:

/*
#include <iostream>

void changeValue(int* ptr) // note: ptr is a pointer to non-const in this example
{
    *ptr = 6; // change the value to 6
}

int main()
{
    int x{ 5 };

    std::cout << "x = " << x << '\n';

    changeValue(&x); // we're passing the address of x to the function

    std::cout << "x = " << x << '\n';

    return 0;
}

*/


// If a function is not supposed to modify the object being passed in, the function parameter
// should be made a pointer-to-const:


/*
void changeValue(const int* ptr) // note: ptr is now a pointer to a const
{
    *ptr = 6; // error: can not change const value
}
*/


// ***** Best Practice ***** 
// Prefer pointer-to-const function parameters over pointer-to-non-const function parameters, 
// unless the function needs to modify the object passed in. Do not make function parameters
// const pointers unless there is some specific reason to do so.



// -------------------------------- Null Address Checking --------------------------------
// When passing a parameter by address, care should be taken to ensure the pointer is not a
// null pointer before you dereference the value. One way to do that is to use a conditional
// statement:

/*
#include <iostream>

void print(int* ptr)
{
    if (ptr) // if ptr is not a null pointer
    {
        std::cout << *ptr << '\n';
    }
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}

*/


// In most cases, it is more effective to do the opposite: test whether the function parameter
// is null as a precondition (9.6 -- Assert and static_assert) and handle the negative case
// immediately:

/*
#include <iostream>

void print(int* ptr)
{
    if (!ptr) // if ptr is a null pointer, early return back to the caller
        return;

    // if we reached this point, we can assume ptr is valid
    // so no more testing or nesting required

    std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
*/



// The above snippet does not handle null cases very well since if a null is passed, the function
// print will simply ignore it and not run. This risk is not there for passing by reference
// Even better than pass by reference is pass by const reference. For two reasons:

// First, because an object being passed by address must have an address, only lvalues can be
// passed by address (as rvalues don’t have addresses). Pass by const reference is more flexible,
// as it can accept lvalues and rvalues:

/*
#include <iostream>

void printByValue(int val) // The function parameter is a copy of the argument
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const int& ref) // The function parameter is a reference that binds to the argument
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const int* ptr) // The function parameter is a pointer that holds the address of the argument
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    printByValue(5);     // valid (but makes a copy)
    printByReference(5); // valid (because the parameter is a const reference)
    printByAddress(&5);  // error: can't take address of r-value

    return 0;
}
*/









// ---------------------- Pass by address for optional arguments --------------------

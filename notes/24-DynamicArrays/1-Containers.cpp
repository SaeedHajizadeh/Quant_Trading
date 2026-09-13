// Containters in C++ are a way to create and manage a collection of objects (called elements).
// Note that a container is a *data type* itself.

// One of the containers in C++ is a string. A string is a sequence of characters 
// encasulated in a single object. The standard C++ library provides a string class that is
// part of the <string> header file. 
/*
#include <iostream>
#include <string>

int main(){
    std::string Name {  "Saeed Hajizadeh" };
    std::cout << "The name is: " << Name << std::endl;

    return 0;
}
*/



// --------------------- The elements of a container are unnamed ---------------------
// This is so that we can add or remover elements from the container without having to
// worry about the names of the elements. This lack of named elements is important, and
// is what distinguishes containers from other types of data structures. It is why plain
// structs (those that are just a collection of data members, like our testScores struct
// above) typically aren’t considered containers -- their data members require unique names.

// --------------------- The length of a container -----------------------------
// The length of a container is the number of elements it contains. The length of a string
// is the number of characters it contains, for example. We can use the length() member
// function in the std::string class to get the length of a string. 
/*
#include <iostream>
#include <string>

int main() {
    std::string Name{ "Saeed Hajizadeh" };
    std::cout << "The name is: " << Name << std::endl;
    std::cout << "The length of the name is: " << Name.length() << " characters." << std::endl;
    std::cout << sizeof(Name) << " bytes." << std::endl;

    return 0;
}
*/



// --------------------------------- Container operations ---------------------------------
// ------------------------------------ Element Types ----------------------------------------
// In most programming languages (including C++), containers are homogenous, meaning the
// elements of a container are required to have the same type.

// Some containers use a preset element type (e.g. a string typically has char elements),
// but more often the element type can be set by the user of the container. In C++,
// containers are typically implemented as class templates, so that the user can provide
// the desired element type as a template type argument.


// -------------------------------- Containers in C++ ------------------------------------
// The *Containers library* is a part of the C++ standard library that contains various class
// types that implement some common types of containers. A class type that implements a
// container is sometimes called a container class.

// The full list of containers in the Containers library is documented here:
// https://en.cppreference.com/w/cpp/container

// --------------------------------- Arrays ------------------------------------
// An array is a container data type that stores a sequence of values contiguously
// (meaning each element is placed in an adjacent memory location, with no gaps).
// Arrays allow fast, direct access to any element.

// C++ contains three primary array types: (C-style) arrays, the std::vector container class,
// and the std::array container class.

// By modern standards, C-style arrays behave strangely and they are dangerous.

// std::vector is the most flexible of the three array types, and has a bunch of useful
// capabilities that the other array types don’t. It was introduced in C++03

// std::array container class was introduced in C++11 as a direct replacement for C-style
// arrays. It is more limited than std::vector, but can also be more efficient, especially
// for smaller arrays.


// ---------------------------------------------------------------------------------------
// --------------- Introduction to std::vector and list constructors --------------------
// ---------------------------------------------------------------------------------------

// std::vector is one of the container classes in the C++ standard containers library that
// implements an array. std::vector is defined in the <vector> header as a class template,
// with a template type parameter that defines the type of the elements. Thus,
// std::vector<int> declares a std::vector whose elements are of type int.

// Instantiating a std::vector
/*
#include <vector>

int main(){
    // Value initialization (uses default constructor)
    std::vector<int> numbers {}; // creates an empty vector of integers containing no elements

    return 0;
}
*/
// Variable empty is defined as a std::vector whose elements have type int. Because we’ve
// used value initialization here, our vector will start empty (that is, with no elements).


// ------------------- Initializing a std::vector with a list of values -------------------
/*
#include <vector>
#include <string>

int main(){
    std::vector<int> numbers { 1 , 2 , 3 , 4 , 5 }; // create and initialize a vector of integers
    std::vector<char> letters { 'a' , 'b' , 'c' , 'd' , 'e' }; // a vector of characters
    std::vector<std::string> names { "Saeed" , "Ali" , "Hassan" , "Hussein" }; // vector of strings

    // Use CTAD (Class Template Argument Deduction) to create a vector of doubles (C++17 feature)
    // CTAD is *preferred method*
    std::vector numbers2 { 1.1 , 2.2 , 3.3 , 4.4 , 5.5 }; // vector of doubles

    return 0;
}
*/




// Containers typically have a special constructor called a list constructor that allows
// us to construct an instance of the container using an initializer list. The list
// constructor does three things:

// 1. Ensures the container has enough storage to hold all the initialization values (if needed).
// 2. Sets the length of the container to the number of elements in the initializer list (if needed).
// 3. Initializes the elements to the values in the initializer list (in sequential order).

// This is the best practice way to initialize a container in C++.

// ----------- Accessing array elements using the subscript operator (operator[]) ----------------
// In C++, the most common way to access array elements is by using the name of the array
// along with the subscript operator (operator[]).

// Because the indexing starts with 0 rather than 1, we say arrays in C++ are zero-based.

// For example, numbers[0] accesses the first element of the vector numbers
/*
#include <iostream>
#include <vector>

int main(){
    std::vector numbers { 2 , 3 , 5 , 7 , 11 };

    std::cout << "The first number is: " << numbers[0] << '\n';
    std::cout << "The second number is: " << numbers[1] << '\n';
    std::cout << "The third number is: " << numbers[2] << '\n';
    
    std::cout << "The sum of the numbers are " << numbers[0] + numbers[1] + numbers[2]
    + numbers[3] + numbers[4] << '\n';

    return 0;
}
*/





// ---------------------- Subscript out of bounds --------------------------
// Passing an invalid index to operator[] will return in undefined behavior.

// -------------------------------- Arrays are contiguous in memory --------------------------
// One of the defining characteristics of arrays is that the elements are always
// allocated contiguously in memory, meaning the elements are all adjacent in memory
// (with no gaps between them). This allows for O(1) access to its elements.
/*
#include <iostream>
#include <vector>

int main(){
    std::vector primes { 2 , 3 , 5 , 7 , 11 };

    std::cout << "An integer is " << sizeof(int) << " bytes." << '\n';
    std::cout << "The address of the first (to the first bit) of each primes element" << '\n';
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    return 0;
}
*/



// Arrays are one of the few container types that allow for random access, meaning any
// element in the container can be accessed directly

// ----------------- Constructing a std::vector of a specific length -----------------------
// Suppose you want to create a vector with a fixed length of say 10
// One way to do is to value initialize this with 10 placeholder values
/*
std::vector<int> data { 0 , ... , 0 };
*/

// This is laborious and error-prone and not scalable.

// Solution: std::vector has a special constructor * explicit std::vector<T>(std::size_t) *
// that takes a single std::size_t value defining the length of the std::vector to construct:

/*
std::vector<int> data ( 10 ); // vector containing 10 int elements, value-initialized to 0 
*/

// Each of the created elements are value-initialized, which for int does
// zero-initialization (and for class types calls the default constructor).

// ------------------ Non-empty initializer lists prefer list constructors -----------------
// Let's look at different examples
/*
// Copy init
std::vector<int> v1 = 10;     // 10 not an initializer list, copy init won't match explicit constructor: compilation error

// Direct init
std::vector<int> v2(10);      // 10 not an initializer list, matches explicit single-argument constructor

// List init
std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor

// Copy list init
std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v5({ 10 });  // { 10 } interpreted as initializer list, matches list constructor

// Default init
std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor
*/

// In case v1, the initialization value of 10 is not an initializer list, so the list
// constructor isn’t a match. The single-argument constructor explicit
// std::vector<T>(std::size_t) won’t match either because copy initialization won’t
// match explicit constructors. Since no constructors match, this is a compilation error.

// In case v2, the initialization value of 10 is not an initializer list, so the
// list constructor isn’t a match. The single-argument constructor explicit
// std::vector<T>(std::size_t) is a match, so the single-argument constructor is selected.

// In case v3 (list initialization), { 10 } can be matched with the list constructor or
// explicit std::vector<T>(std::size_t). The list constructor takes precedence over
// other matching constructors and is selected.

// In case v4 (copy list initialization), { 10 } can be matched with the list constructor
// (which is a non-explicit constructor, so can be used with copy initialization).
// The list constructor is selected.

// Case v5 surprisingly is an alternate syntax for copy list initialization
// (not direct initialization), and is the same as v4.

// v6 and v7 are both initialized using empty initializer lists. In this case,
// the default constructor takes precedence.



// ********************************* best practice *************************************
// When constructing a container (or any type that has a list constructor) with initializers
// that are not element values, use direct initialization.


// Create a vector of size 10
/*
#include <vector>
#include <iostream>

int main(){
    std::vector<int> numbers(10);

    std::cout << numbers[0] << '\n';

    return 0;
}
*/

// However, When a std::vector is a member of a class type, it is not obvious how to
// provide a default initializer that sets the length of a std::vector to some initial value:

/*
#include <vector>

struct Foo
{
    std::vector<int> v1(8); 
    // compile error: direct initialization not allowed for member default initializers
};
*/

// This doesn’t work because direct (parenthesis) initialization is disallowed for
// member default initializers.

// When providing a default initializer for a member of a class type:

// 1. We must use either copy initialization or list initialization (direct or copy).
// 2. CTAD is not allowed (so we must explicitly specify the element type).


// Solution is as follows:
/*
struct Foo
{
    std::vector<int> v1 { std::vector<int>(8) };   // ok
};
*/

// The line above creates a std::vector with a capacity of 8, and then uses that as
// the initializer for v.

// ------------------------------ Const and constexpr std::vector ----------------------------
// const std::vector
/*
#include <vector>

int main() {
    const std::vector<int> prime {2 , 3 , 5 , 7};  // prime and its elements cannot be modified

    return 0;
}
*/
// A const std::vector must be initialized, and then cannot be modified. The elements of
// such a vector are treated as if they were const.

// The element type of a std::vector must not be defined as const
// (e.g. std::vector<const int> is disallowed).


// Using a std::vector, write a program that asks the user to enter 3 integral
// values. Print the sum and product of those values.
// Solution below:
/*
#include <vector>
#include <iostream>

int main() {
    std::vector<double> values(3);
    int sum = 0;
    int prod = 1;
    std::cout << "Enter 3 integers: " << '\n';
    std::cin >> values[0] >> values[1] >> values[2];

    
    sum = values[0] + values[1] + values[2];
    prod = values[0] * values[1] * values[2];
    std::cout << "The sum is: " << sum << '\n';
    std::cout << "The product is: " << prod << '\n';

    return 0;
}
*/



// --------------------------------------------------------------------------------------
// -------------- std::vector and the unsigned length and subscript problem -------------
// --------------------------------------------------------------------------------------\
// We noticed we can use operater[] to access an element in std::vector
// Here we look at other ways to access an element or the length of std::vector

// The data type used for subscripting an array should match the data type used for
// storing the length of the array. The C++ developers choose to make the array length and
// subscript variables into "unsigned" which was a poor decision. Now, an implicit sign
// conversion is necessary. 

// ----- A review: sign conversions are narrowing conversions, except when constexpr ------
// Sign conversions are considered to be ***narrowing conversions*** because a signed or
// unsigned type cannot hold all the values contained in the range of the opposing type. 
// When such a conversion would be performed at runtime, the compiler will issue an error
// in contexts where narrowing conversions are disallowed (such as in list initialization),
// and may or may not issue a warning in other contexts where such a conversion is performed.

/*
    Note that [[...]] is the syntax for attributes introduced in C++11.
    maybe_unused is the name of a standard attribute. The line of code below

    [[maybe_unused]] unsigned int u { 5 };

    means: Declare u as an unsigned int, and tell the compiler that it is intentional if u
    is never used so no warnings is raised.
*/
/*
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    int s { 5 };

    // compile error: list initialization disallows narrowing conversion
    [[maybe_unused]] unsigned int u { s }; 

    // possible warning: copy initialization allows narrowing conversion
    foo(s);                                

    return 0;
}
*/




// However, if the value to be sign converted is constexpr and can be converted to an
// equivalent value in the opposing type, the sign conversion is not considered to be narrowing.
/*
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    constexpr int s { 5 };                 // now constexpr
    
    // ok: s is constexpr and can be converted safely, not a narrowing conversion
    [[maybe_unused]] unsigned int u { s }; 

    // ok: s is constexpr and can be converted safely, not a narrowing conversion
    foo(s);                                

    return 0;
}
*/
// In this case, since s is constexpr and the value to be converted (5) can be represented
// as an unsigned value, the conversion is not considered to be narrowing and can be
// performed implicitly without issue.

// This non-narrowing constexpr conversion (from constexpr int to constexpr std::size_t)
// will be something we make use of a lot.

// ------------------ The length and indices of std::vector have type size_type ---------------
// size_type is a nested typedef defined in standard library container classes, used as
// the type for the length (and indices, if supported) of the container class.

// size_type defaults to std::size_t, and since this is almost never changed, we can
// reasonably assume size_type is an alias for std::size_t.

// ************************************************************************************
//      When accessing the size_type member of a container class, we must scope qualify it
//      with the fully templated name of the container class. For example,
//      std::vector<int>::size_type.
// ************************************************************************************

// Question: Getting the length of a std::vector using the size() member function or std::size()?
// We can ask a container class object for its length using the size() member function
// (which returns the length as unsigned size_type). Example below (container class std::vector)
/*
#include <iostream>
#include <vector>

int main() {
    std::vector<int> primes { 2 , 3 , 5 , 7 , 11 };

    // // returns length as type `size_type` (alias for `std::size_t`)
    std::cout << "length: " << primes.size() << '\n';

    return 0;
}
*/



// Unlike std::string and std::string_view, which have both a length() and a size()
// member function (that do the same thing), std::vector (and most other container types
// in C++) only has size(). And now you understand why the length of a container is
// sometimes ambiguously called its size.

// In C++17, we can also use the std::size() non-member function (which for container
// classes just calls the size() member function).
/*
#include <iostream>
#include  <vector>

int main()
{   
    std::vector<int> primes { 2 , 3 , 5 , 7 , 11 };
    std::cout << "length: " << std::size(primes) << '\n';

    return 0;
}
*/


// If we want to use either of the above methods to store the length in a variable with
// a signed type, this will likely result in a signed/unsigned conversion warning or error.
// The simplest thing to do here is static_cast the result to the desired type:

/*
    Note that static_cast<int> is a *type casting* operator used to explicitly convert 
    an expression from its current data type into integer. It is the modern C++
    equivalent of int() of Python.
*/

/*
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    int length { static_cast<int>(prime.size()) };
    std::cout << "length: " << length ;

    return 0;
}
*/




// -------------- Getting the length of a std::vector using std::ssize() ------------------
// C++20 introduces the ***std::ssize()*** non-member function, which returns the
// length as a large signed integral type (usually std::ptrdiff_t, which is the type
// normally used as the signed counterpart to std::size_t):

// You need to run the following snippet using C++20. Simply run
// g++ -std=c++20 1-Containers.cpp -o main 
// instead of 
// g++ 1-Containers.cpp -o main
// which runs as C++17 


/*
#include <iostream>
#include <vector>

int main() 
{
    std::vector<int> primes { 2 , 3 , 5 , 7 , 11 };

    // C++20, returns length as a large signed integral type
    std::cout << "length: " << std::ssize(primes) << '\n'; 
    return 0;
}
*/




// This is the only function of the three which returns the length as a signed type.

// If you want to use this method to store the length in a variable with a signed type,
// you have a couple of options.

// First, because the int type may be smaller than the signed type returned by std::ssize(),
// if you are going to assign the length to an int variable, you should static_cast the
// result to int to make any such conversion explicit (otherwise you might get a narrowing
// conversion warning or error):
/*
#include <iostream>
#include <vector>

int main(){
    std::vector<int> primes { 2 , 3 , 5 , 7 , 11 };

    // static_cast return value to int
    int length { static_cast<int>(std::ssize(primes)) };
    std::cout << "length: " << length << '\n';
    return 0;
}
*/


// Alternatively, you can use auto to have the compiler deduce the correct signed type
// to use for the variable:
/*
#include <iostream>
#include <vector>

int main(){
    std::vector<int> primes { 2 , 3 , 5 , 7 , 11 };

    // use auto to deduce signed type, as returned by std::ssize()
    auto length { std::ssize(primes) };
    std::cout << "length: " << length << '\n';
    return 0;
}
*/



// --------- / use auto to deduce signed type, as returned by std::ssize() -----------
/*
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3] <<'\n';  // print the value of element with index 3 (7)
    std::cout << prime[9] <<'\n'; // invalid index (undefined behavior)

    return 0;
}
*/





// --- Accessing array elements using the at() member function does runtime bounds checking ---
// The array container classes support another method for accessing an array. The at() member
// function can be used to do array access with runtime bounds checking:
/*
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime.at(3); // print the value of element with index 3
    std::cout << prime.at(9); // invalid index (throws exception)

    return 0;
}
*/

// Note that at() returns a run-time error not a compile time error. More precisely,
// it actually throws an exception of type std::out_of_range. 

// Just like operator[], the index passed to at() can be non-const.

// Because it does runtime bounds checking on every call, at() is slower (but safer)
// than operator[]. Despite being less safe, operator[] is typically used over at(),
// primarily because it’s better to do bounds checking prior to indexing, so we don’t
// try to use an invalid index in the first place.



// ----------------- Indexing std::vector with a constexpr signed int --------------------
// When indexing a std::vector with a constexpr (signed) int, we can let the compiler
// implicitly convert this to a std::size_t without it being a narrowing conversion:

/*
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3] << '\n';     // okay: 3 converted from int to std::size_t, not a narrowing conversion

    constexpr int index { 3 };         // constexpr
    std::cout << prime[index] << '\n'; // okay: constexpr index implicitly converted to std::size_t, not a narrowing conversion

    return 0;
}
*/





// --------------------- Indexing Challenge ----------------------
// ------------------ Indexing std::vector with a non-constexpr value --------------------
// The subscripts used to index an array can be non-const:
/*
    #include <iostream>
    #include <vector>

    int main()
    {
        std::vector prime{ 2, 3, 5, 7, 11 };

        std::size_t index { 3 };           // non-constexpr
        std::cout << prime[index] << '\n'; // operator[] expects an index of type std::size_t, no conversion required

        return 0;
    }
*/









// However, best practice is we generally want to avoid using unsigned types to hold quantities.
// When our subscript is a non-constexpr signed value, we run into problems:

/*
    #include <iostream>
    #include <vector>

    int main()
    {
        std::vector prime{ 2, 3, 5, 7, 11 };

        int index { 3 };                   // non-constexpr
        std::cout << prime[index] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion

        return 0;
    }
*/



// In this example, index is a non-constexpr signed int. The subscript of operator[] defined
// as part of std::vector has type size_type (an alias for std::size_t). Therefore, when we
// call prime[index], our signed int must be converted to std::size_t.

// All in all this is subscripting complexity in C++ that do not exist in scripting languages

// There are many possible ways to avoid this issue 
// (e.g. static_cast your int to a std::size_t every time you index an array),
// but all inevitably end up cluttering or complicating your code in some way.

// *****************************************************************************************
// The simplest thing to do in this case is use a variable of type std::size_t as your
// index, and do not use this variable for anything but indexing. 
// *****************************************************************************************


// a) What is size_type and what is it used for?
// size_type is a nested typedef that is an alias for the type used to store the
// length (and indices, if supported) of a standard library container.

// b) What type does size_type default to? Is it signed or unsigned?
// std::size_t, which is an unsigned type.

// c) Which functions to get the length of a container return size_type?
// The size() member function and std::size both return size_type.

// d) Write a binary search code
#include <iostream>
#include <vector>
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int l = 0, r = static_cast<int>(nums.size()) - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) l = mid + 1;
            else r = mid - 1;
        }
        return -1;
    }
};

int main(){

    Solution test;
    std::vector<int> nums { 1 , 3 , 8 , 11 , 12};
    int target = 8;
    int result = test.search(nums , target);
    if (result == -1){
        std::cout << "The target value " << target << " was not found!";
    }
    else{
        std::cout << "The target value " << target << " was found at index " << result << '\n';
    }
    // std::cout << test.search(nums , target) << '\n';
    
    return 0;
}
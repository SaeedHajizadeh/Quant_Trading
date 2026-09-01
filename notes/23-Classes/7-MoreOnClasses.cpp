// -------------------------------------------------------------------------------------------
//                             Class templates with member functions
// -------------------------------------------------------------------------------------------

// We recall that function templates are functions that can operate with generic types
/*
#include <iostream>

template <typename T>
T FindMax(T a , T b) {
    return (a > b) ? a : b;
}

int main() {
    // 1. Explicit type specification
    std::cout << FindMax<int>(3 , 7) << std::endl; // Output: 7

    // 2. Implicit type specification
    std::cout << FindMax(2.44 , 3.14) << std::endl; // Output: 3.14
    std::cout << FindMax('A' , 'B') << std::endl; // Output: B

    return 0;
}
*/

// We recently learned that template classes are those that include data members with template
// types. 

/*
#include <iostream>

template <typename T>
struct Pair {
    T first {};
    T second {};
};

// Here's a deduction guide for our Pair (required in C++17 or older)
// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair(T , T) -> Pair<T>;

int main() {
    Pair<int> p1 { 1 , 2 }; // instantiates Pair<int> and creates the object p1
    std::cout << p1.first << " " << p1.second << std::endl;

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
*/



// -------------------- Class templates with member functions --------------------

// Type template parameters defined as part of a class template parameter declaration can
// be used both as the type of data members and as the type of member function parameters.
/*
#include <ios>         // for std::boolalpha
#include <iostream>

template <typename T>
class Pair {
    private:
        T m_first {};
        T m_second {};

    public:
        // When we define a member function inside the class definition,
        // the template parameter declaration belonging to the class applies
        Pair(const T& first , const T& second)
        : m_first { first }
        , m_second { second } 
        {
        }

        bool isEqual(const Pair<T>& pair);
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair) {
    return m_first == pair.m_first && m_second == pair.m_second;
}

int main() {
    Pair p1{ 5, 6 }; // uses Class Template Argument Deduction (CTAD) to infer type Pair<int>
    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

    return 0;
}
*/


// Two things worth noting about the above code:
// First, because our class has private members, it is not an aggregate, and therefore can’t
// use aggregate initialization. Instead, we have to initialize our class objects using
// a constructor.

// Since our class data members are of type T, we make the parameters of our constructor
// type const T&, so the user can supply initialization values of the same type. Because
// T might be expensive to copy, it’s safer to pass by const reference than by value.

// We also defined the member function isEqual() outside the class definition
// Since this member function definition is separate from the class template definition,
// we need to resupply a template parameter declaration (template <typename T>) so
// the compiler knows what T is.

// Also, when we define a member function outside of the class, we need to qualify the
// member function name with the fully templated name of the class template
// (Pair<T>::isEqual, not Pair::isEqual).

// ---------------------------------- Injected class names ---------------------------------
// In prior lessons, we learned that a class name must be the same as the name of the
// constructor. However, in our class template for Pair<T> above, we named our constructor
// Pair, not Pair<T>. Somehow this still works, even though the names don’t match.

// Within the scope of a class, the unqualified name of the class is called an *injected
// class name*. In a class template, the injected class name serves as shorthand for the
// fully templated name. Hence, the injected class name "Pair" serves as a shorthand for 
// the fully template name "Pair<T>". 

// Because Pair is the injected class name of Pair<T>, within the scope of our Pair<T>
// class template, any use of Pair will be treated as if we had written Pair<T> instead.
// Therefore, although we named the constructor Pair, the compiler treats it as if we
// had written Pair<T> instead. The names now match!

// As another example, we can define the template function isEqual() to take a parameter of
// type Pair instead of Pair<T>. Because Pair is the injected class name of Pair<T>, the
// compiler treats Pair as if we had written Pair<T> instead. Hence, the parameter type
// of isEqual() is Pair<T>, which is what we want.

/*
template <typename T>
bool Pair<T>::isEqual(const Pair& pair) // note the parameter has type Pair, not Pair<T>
{
    return m_first == pair.m_first && m_second == pair.m_second;
}
*/

// -------- Where to define member functions for class templates outside the class ----------
// With member functions for class templates, the compiler needs to see both the class
// definition (to ensure that the member function template is declared as part of the class)
// and the template member function definition (to know how to instantiate the template).
// Therefore, we typically want to define both a class and its member function templates
//in the same location.

// When a member function template is defined inside the class definition, the template member
// function definition is part of the class definition, so anywhere the class definition can
// be seen, the template member function definition can also be seen. This makes things easy
// (at the cost of cluttering our class definition).

// When a member function template is defined outside the class definition, it should generally
// be defined immediately below the class definition. That way, anywhere the class definition
// can be seen, the member function template definitions immediately below the class
// definition will also be seen.

// ****** best practice ****
// Any member function templates defined outside the class definition should be defined
// just below the class definition (in the same file).



/*
#include <iostream>
#include <string>

template <typename T , typename U , typename V>
class Triad {
    private:
        T m_first {};
        U m_second {};
        V m_third {};

    public:
        Triad(const T& first , const U& second , const V& third)
            : m_first { first }
            , m_second { second }
            , m_third { third }
            {
            }
        
    const T& first() const { return m_first; }
    const U& second() const { return m_second; }
    const V& third() const { return m_third; }

    void print() const;
};

template <typename T , typename U , typename V>
void Triad<T , U , V>::print() const {
    std::cout << "[" << m_first << ", " << m_second << ", " << m_third << "]";
}


int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.first() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}
*/




// A few notes on the code above:
// We can access m_first, m_second, and m_third directly in the print() member function because
// print() is a *member* function of the Triad class template. However, we cannot access these
// data members directly in main() because they are private. 
// Instead, we have to use the public member functions first(), second(), and third() to
// access the values of these data members.

// When you write void Triad<T, U, V>::print() const { ... }, the Triad<T, U, V>:: qualifier
// is you saying "this is the definition of the print member that I already declared inside
// the class." It's still a member function of Triad. The out-of-line definition is just
// the body being placed elsewhere for readability; the function's identity as a class
// member was fixed by the declaration inside the class body.

// string-literal suffixes are only available in C++14 and later. The "s" suffix is defined
// in the std::literals::string_literals namespace, so we need to bring that namespace into
// scope before we can use the "s" suffix.

// The s suffix "Hello" by itself is a C-style string literal — its type is *const char[6]*,
// essentially a raw array of characters. It is not a std::string.

// "Hello"s (with the s glued right onto the closing quote) is a user-defined literal
// that produces an actual std::string object. The s is a suffix that means "make this
// a std::string." So:
/*
"Hello"     // const char[6]  — C-string
"Hello"s    // std::string    — the real class
*/





// In C++, compound data types (also known as composite data types) are any data types defined
// in terms of other existing data types. According to the ISO C++ standard, every data type
// is either a fundamental type (like int, char, or bool) or a compound type.


// ---------------------- Group 1: Reference and Pointer Types ---------------------

// ******** References (&) ***********
// An alias or alternative name for an existing variable. It must be initialized when created.
/*
int mainNumber = 42;
int& refNumber = mainNumber; // refNumber is now an alias for mainNumber
*/



// Pointers (*): A variable that holds the raw memory address of another object.
/*
int mainNumber = 42;
int* ptrNumber = &mainNumber; // Stores the memory address of mainNumber
*/




// ---------------------- Group 2: User-Defined Aggregate Types ---------------------
// These types allow developers to group multiple variables (and sometimes functions)
// together into a single, cohesive unit. We studied an example of them in last chapter.



// ******* Structures (struct) *********
// A collection of heterogeneous variables grouped under a single name. Members are public
// by default.

/*
struct Point {
    int x;
    int y;
};
*/




// ******** Classes (class) ***********
// The core of Object-Oriented Programming in C++. Similar to structs, but members are private
// by default and typically include member functions.
/*
class BankAccount {
    private:
        double balance;
    public:
        void deposit(double amount) { balance += amount; }
};
*/





// ********* Unions (union) ***********
// A special type where all members share the exact same memory location. Only one member
// can hold a value at any given time.
/*
union Data {
    int intVal;
    float floatVal;
};
*/




// ----------------------------- Group 3: Arrays and Enumerations -----------------------------
// These types handle collections of data or sets of named constants.



// ********** Arrays ***********
//A fixed-size, sequential collection of elements belonging to the same exact data type.
/*
int scores[5] = {25 , 35 , 40 , 45 , 60};
*/



// ********** Enumerations (enum & enum class) ***********
// User-defined types consisting of a set of named integer constants.
/*
enum class Color { Red, Green, Blue };
Color myFavorite = Color::Blue;
*/






// ----------------------------- Group 4: Functions -----------------------------
// : In C++, functions themselves are technically categorized as compound data types
// because they combine a return type and a sequence of parameter types.
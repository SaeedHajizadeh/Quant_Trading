// There are instances in programming where we would like to store multiple variables
// to represent something of interest. For example, suppose we want to have a program
// that stores information about a company's employees. The employee information have
// multiple dimensions to it, say, age, employee id, managerId, title, birthYear, etc.

// If we decide to use independent variables to represent each employee we'd have
/*
std::string name;
std::string title;
int age;
int Id;
int managerId;
double wage;
int birthYear;

*/

// There are a bunch of problems with this approach: first, we need to handle x 
// number of attributes for each employee; second, passing them to a function 
// needs to be in order, hence burdensome; third, we would not know which Id,
// say, is related to which employee etc. so many variables for each employee

// *** We need to wrap these attributes into a box, each box representing an employee ***
// Fortunately, C++ has two compound data types to resolve this challenge
// structs and classes
// *** A struct, shorthand for structure, is a program-defined data type that allows 
// us to bundle multiple variables together into a single type ***
// A struct is a class type (as are classes and unions). As such, anything that 
// applies to class types applies to structs.

// structs are program-defined data types, so we MUST tell the compiler first how
// it will look like -- example below

// struct Employee {
//     int id {};
//     int age {};
//     double wage {};
// };

// struct keyword tells the compiler we are defining a struct; the name comes right after
// Program-defined types are typically given names starting with a capital letter.
// This particular struct wraps three variables: age, id, and wage. 
// *** These variables are called "data members" or "member variables" ***

/*
    In everyday language, a member is a individual who belongs to a group. For example,
    you might be a member of the basketball team, and your sister might be a member of
    the choir.

    In C++, a member is a variable, function, or type that belongs to a struct (or
    class). All members must be declared within the struct (or class) definition.

    We’ll use the term member a lot in future lessons, so make sure you remember what
    it means.
*/

// Just like a set of curly braces allow us to initialize a variable we have just 
// defined, the empty curly braces after each member variable ensures these variables
// are initialized after an Employee object is created. 

// Finally, we end the type definition with a semicolon and since Employee (a struct) is
// a type, we need to end it with a semicolon;

// ---------------- defining the struct "object"  --------------------
// *** In order to use the Employee type, we simply define a variable of type Employee ***

// Employee Saeed {};
// When the line above is executed, the Employee object is instantiated and contains
// three data members. The empty braces ensures our object is value-initialized. Thus
// *** We need the braces in front of the Employee object as well ***




// ----------------- The Program  --------------------
#include <iostream>

struct Employee {
    std::string id {};
    int age {};
    double wage {};
};


int main () {
    Employee Saeed {};
    Saeed.id = "shajiz2";
    Saeed.age = 38;
    Saeed.wage = 1123.32;


    // We define the second Employee an alternative way
    Employee James {"jhull22" , 33 , 12606.75};

    int total_age {Saeed.age + James.age};
    std::cout << "Saeed and James have lived a total of " << total_age << " years.\n";

    if (Saeed.wage > James.wage)
        std::cout << "Saeed earns more than James";
    else if (James.wage > Saeed.wage)
        std::cout << "James earns more than Saeed";
    else
        std::cout << "Saeed and James earn the same amount.";

    
    // Saeed gets a promotion
    Saeed.wage += 5000.0;

    // Today is James' birthday
    ++James.age;     // Use pre-increment to increment James's age by 1

    std::cout << std::endl;

    return 0;
}
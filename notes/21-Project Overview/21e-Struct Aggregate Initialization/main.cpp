// In the previous chapter, 21d, we talked about how structs are defined, how to 
// instantiate struct objects, and how to access their member variables.

// Here we will discuss how structs are initializec

// ----------------- What is aggregate? ----------------------------
// In general programming, an *aggregate data type* (also called an aggregate) is any
// type that can contain multiple data members. 
// Some types of aggregates allow "data members"/"member variables" to have different
// types (such as structs) and some other aggregates require all members to be of
// the same type (such as std::array )

// Definition of aggregate in C++ is more specific. Look at the link below for details:
// https://en.cppreference.com/cpp/language/aggregate_initialization


// ------------------- Aggregate initialization of a struct ------------------

// Aggregates use a form of initialization called "aggregate initialization", which
// allows us to initialize the members of the aggregate simultaneously
// To do this, we provide an "initializer list" which is just a braced list of
// comma-separated values. 

// We touched on this in the last chapter, but there are two primary forms of 
// aggregate initialization

/*
struct Employee {
    int age {};
    std::string id {};
    double wage {};
};

int main() {
    // copy-list initialization using braced list
    Employee Saeed = {22 , "shajiz2" , 1100.00}; 

    // list initialization using braced list (preferred)
    Employee James {28 , "jh2234" , 12000.00};
    return 0;
}
*/

// These are called "memberwise initialization" -- initialize member variables in the
// order that they are defined. 

// In C++20, we can initialize (some) aggregates using a parenthesized list of vals
// We recommend avoiding this as much as possible since it does not work for arrays
// Employee Robert (31 , "R2235" , 1123.22);



// ----------------------- Missing an initialization in a list ---------------------
// If an aggregate is initialized but the number of initialization values is fewer than
// the number of member variables, then each member WITHOUT an explicit initializer is 
// initialized as follows:
// 1. If the member has a default member initializer, that is used.
// 2. Otherwise, the member is copy-initialized from an empty initializer list. In most
//    cases this will be a value-initialization (e.g. 0.0 for double)

#include <iostream>
struct Employee {
    int id {};
    int age {};
    double wage {75000.0};
    double whatever; 
    std::string whatever2;
};

int main () {
    Employee Saeed {11 , 29}; // Saeed.whatever will be initialized at 0.0
                              // Saeed.whatever2 will be initialized at ""

    std::cout << "Saeed.whatever : " << Saeed.whatever;
    std::cout << " and Saeed.whatever2 is " << (Saeed.whatever2 ==  "") << std::endl;
    return 0;
}
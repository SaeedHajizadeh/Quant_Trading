// Passing a struct, which, as we stated before, is an aggregate, allows us to pass
// multiple member variables to a function, process members, and return another struct.
// *** Structs are generally passed by reference (typically by const reference) to 
// avoid making copies.

/*
#include <iostream>

struct Employee {
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& e) // note pass by reference here
{        
    std::cout << "ID:      " << e.id   << '\n';
    std::cout << "Age:     " << e.age  << '\n';
    std::cout << "wage     " << e.wage << '\n';
}

int main() {
    Employee Joe {1 , 33 , 5522.0};
    printEmployee(Joe);

    std::cout << std::endl;

    // Print Saeed's info without creating the object, i.e. using a temporary object
    // construct a temporary Employee to pass to function (type explicitly specified) (preferred)
    printEmployee(Employee {2 , 29 , 4299.0});

    std::cout << std::endl;

    // construct a temporary Employee to pass to function (type deduced from parameter)
    printEmployee({3 , 36 , 33.11});

    return 0;
}
*/


// We can create a temporary Employee in two ways. In the first call, we use the syntax
// Employee { 14, 32, 24.15 }. This tells the compiler to create an Employee object and
// initialize it with the provided initializers. This is the preferred syntax because it
// makes clear what kind of temporary object we are creating, and there is no way for
// the compiler to misinterpret our intentions.
// In the second call, we use the syntax { 15, 28, 18.27 }. The compiler is smart enough
// to understand that the provided arguments must be converted to an Employee so that the
// function call will succeed. Note that this form is considered an implicit conversion,
// so it will not work in cases where only explicit conversions are acceptable.



// A few more things about temporary objects: they are created and initialized at the
// point of definition, and are destroyed at the end of the full expression in which
// they are created. And evaluation of a temporary object is an rvalue expression, it
// can only be used in places where rvalues are accepted. When a temporary object is used
// as a function argument, it will only bind to parameters that accept rvalues. This
// includes pass by value and pass by const reference, and excludes pass by non-const
// reference and pass by address.



// --------------------------- Returning structs --------------------------------------
// Consider a function that accepts a struct and returns a struct. An example would be
// points in 3-d space, processed, and a new point returned.

/*
#include <iostream>

struct Point3d {
    double x {0.0};
    double y {0.0};
    double z {0.0};
};

Point3d AddOneEachDimension(Point3d p) {
    p.x += 1;
    p.y += 1;
    p.z += 1;
    return p;
}

Point3d GetZeroPoint() {
    // Point3d temp {0.0 , 0.0 , 0.0};
    // return temp;
    // return an unnamed temporary object instead
    // In this case, a temporary Point3d is constructed, copied back to the caller,
    // and then destroyed at the end of the expression. Note how much cleaner this
    // is (one line vs two, and no need to understand whether temp is used more
    // than once).
    return Point3d {0.0 , 0.0 , 0.0};
}

int main() {
    Point3d zero = GetZeroPoint();
    Point3d Added = AddOneEachDimension(zero);
    std::cout << "x: " << Added.x << " y: " << Added.y << " z: " << Added.z << '\n';

    return 0;
}
*/





// --------------------------- Deducing return type ---------------------------------------
// In cases where the function has an *explicit* return type, we can omit the type in the 
// return statement. This is called an *** implicit conversion ***
/*
Point3d getZeroPoint() {
    return {0.0 , 0.0 , 0.0};
}
*/ 


// Also, since we are returning all zero values, we can allow value initialization do it
// bby simply returning an empty braces
/*
Point3d getZeroPoint() {
    // We can use empty curly braces to value-initialize all members
    return {};
}
*/



// ---------------------------------- Quiz ---------------------------------------
// You are running a website, and you are trying to calculate your advertising revenue.
// Write a program that allows you to enter 3 pieces of data:
// 1. How many ads were watched.
// 2. What percentage of users clicked on an ad.
// 3. The average earnings per clicked ad.
// Store these vallues in a struct and pass them to a function to print each member value
// and ALSO print how much revenue you made in the day

#include <iostream>

struct Advertising {
    int AdsWatched {};
    double ClickRatePercentage {};
    double EarningsPerClick {};
};

// A function to receive advertising
Advertising GetAdvertising() {
    Advertising temp {};
    std::cout << "Please enter the number of Ads Watched Today: ";
    std::cin >> temp.AdsWatched;
    std::cout << "\nPlease enter the percentage of clicks on the ads watched: ";
    std::cin >> temp.ClickRatePercentage;
    std::cout << "\nPlease enter earnings per click: ";
    std::cin >> temp.EarningsPerClick;
    std::cout << '\n';
    return temp;
}

// print revenue
void PrintRevenue(Advertising ad) {
    double revenue = ad.AdsWatched * ad.ClickRatePercentage * ad.EarningsPerClick;
    std::cout << "Total Revenue: $" << revenue << std::endl;
}

int main() {

    auto ad = GetAdvertising();
    PrintRevenue(ad);

    return 0;
}
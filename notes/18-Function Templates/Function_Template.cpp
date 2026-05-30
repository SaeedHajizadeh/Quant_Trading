// Function templates in C++ are blueprints that allow you to write a single function capable
// of operating on multiple data types without duplicating code. Instead of manually overloading
// a function for int, double, and string, you define a generic function using placeholder types
// that the compiler instantiates on demand.

// Let's start describing function templates

// #include <iostream>

// // Let's say we want to consider the max function
// // ternary operator: condition ? expression_if_true : expression_if_false
// int max(int x , int y) {
//     return (x > y) ? x : y;     // ternary operator == return x if x > y else y (Python)
// }

// // We need function overloads to include other variable types
// double max(double x , double y) {
//     return (x > y) ? x : y;     
// }
// char max(char x , char y) {
//     return (x > y) ? x : y;     
// }

// int main() {
//     std::cout << max(1 , 2) << std::endl;
//     std::cout << max(1.5 , 2.33) << std::endl;
//     std::cout << max('5' , '6') << std::endl;  
//     // '1'  --> type : char  so on so on
//     // '15' --> type : int   literal '1' is char but '22' is a since multi-character literal
//     return 0;
// }



// // What if we define one function that accepts and return multiple data types
// // These are called function templates --> how to create one?
// // Take your function and replace any data type declaration with T. BUT compiler does NOT know
// // what T is. We need to add template parameter declaration
// #include <iostream>
// // template < ... >: introduces a template declaration to the compiler
// // typename T: This is the template type parameter declaration. It introduces T as a placeholder
// //  name for a data type that will be determined later at compile time.
// template <typename T>   // Template parameter declaration
// template <typename T , typename U>
// T max(T x , T y){
//     return (x > y) ? x : y;
// }

// int main() {
//     std::cout << max(1 , 2) << std::endl;
//     std::cout << max(1.5 , 2.33) << std::endl;
//     std::cout << max('5' , '6') << std::endl;

//     return 0;
// }




// What if we want to mix and match the data types for example max(1 , 2.25) ?? We can
// add another typename in our template parameter declaration
#include <iostream>
template <typename T , typename U>
auto max(T x , U y){
    return (x > y) ? x : y;
}

int main() {
    std::cout << max(1 , 2) << std::endl;
    std::cout << max(1.5 , 2.33) << std::endl;
    std::cout << max('5' , '6') << std::endl;
    std::cout << max(1 , 2.55) << std::endl;
    return 0;
}

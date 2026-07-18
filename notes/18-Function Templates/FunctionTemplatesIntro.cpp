// t’s say you wanted to write a function to calculate the maximum of two numbers.

/*
int max(int x, int y)
{
    return (x < y) ? y : x;
    // Note: we use < instead of > because std::max uses <
}
*/


// This function really only works for integers. If the user would like to enter and compare two
// doubles, another function definition needs to be provided. 

/*
double max(double x, double y)
{
    return (x < y) ? y: x;
}
*/


// Note that the code for the implementation of the double version of max is exactly the same as
// for the int version of max!

// Having to overload function definitions for each set of function parameters is a maintenance 
// headache, and error prone. More importantly, if the user would like to apply the max funciton
// to a new argument type the developer did not anticipate, things stop working. 

// We can utilize a feature in C++ that allows us to definie *one* function that captures any
// type for the inputs and outputs ---> C++ templates.

// ---------------------------------- C++ Templates ------------------------------------
// Instead of manually creating a bunch of mostly-identical functions or classes (one for each
// set of different types), we instead create a single template. Just like a normal definition,
// a template definition describes what a function or class looks like. Unlike a normal
// definition (where all types must be specified), in a template we can use one or more
// placeholder types. A placeholder type represents some type that is not known at the time the
// template is defined, but that will be provided later (when the template is used).

// Because the actual types aren’t determined until the template is used in a program
// (not when the template is written), the author of the template doesn’t have to try to
// anticipate all of the actual types that might be used. This means template code can be
// used with types that didn’t even exist when the template was written! We’ll see how this
// comes in handy later, when we start exploring the C++ standard library, which is absolutely
// full of template code!


// -------------------------------------- Function Templates -------------------------------
// A function template is a function-like definition that is used to generate one or more
// overloaded functions, each with a different set of actual types. This is what will allow
// us to create functions that can work with many different types. The initial function template
// that is used to generate other functions is called the primary template, and the functions
// generated from the primary template are called instantiated functions.

// When we create a primary function template, we use placeholder types (technically called
// type template parameters, informally called template types) for any parameter types, return
// types, or types used in the function body that we want to be specified later, by the user of
// the template.

// --------------------------------- Creating max() function -----------------------------------
// The int version of the max() function again
/*
int max(int x, int y)
{
    return (x < y) ? y : x;
}
*/


// To create a function template for max(), we’re going to do two things. First, we’re going to
// replace any actual types that we want to be specified later with type template parameters.
// In this case, because we have only one type that needs replacing (int), we only need one
// type template parameter (which we’ll call T):

/*
T max(T x , T y) {  // // won't compile because we haven't defined T
    return (x < y) ? y : x;
}
*/



// This is a good start. BUT it does not compile since the compiler does not know T! Also, this
// is still a normal function not a template function

// Second, we’re going to tell the compiler that this is a template, and that T is a type
// template parameter that is a placeholder for any type. Both of these are done using a
// ***template parameter declaration***, which defines any template parameters that will
// be subsequently used. The scope of a template parameter declaration is strictly limited
// to the function template (or class template) that follows. Therefore, each function template
// or class template needs its own template parameter declaration.

template <typename T> // this is the template parameter declaration defining T
T max(T x , T y){     // // this is the function template definition for max<T>
    return (x < y) ? y : x;
}

// ******** template parameter declaration **********
// In our template parameter declaration, we start with the keyword template, which tells
// the compiler that we’re creating a template. Next, we specify all of the template parameters
// that our template will use inside angled brackets (<>). For each type template parameter,
// we use the keyword typename (preferred) or class, followed by the name of the type
// template parameter (e.g. T).

// ---------------------------------- Naming template parameters -----------------------------
// Much like we often use a single letter for variable names used in trivial situations
// (e.g. x), it’s conventional to use a single capital letter (starting with T) when the
// template parameter is used in a trivial or obvious way. 


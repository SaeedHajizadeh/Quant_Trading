// ------------------- Default Member Initialization  -----------------------
// This is a very straightforward chapter. We want to initialize our member values so we can 
// (i) have them initialized, and possibly (ii) determine the default initialization

// In the program below, the struct Something has three members, each with a different initialization
/*
struct Something
{
    int x;       // no initialization value (***bad***)
    int y {};    // value-initialized by default  (default member initialization)
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1; // s1.x is uninitialized, s1.y is 0, and s1.z is 2

    return 0;
}
*/


// Explicit initialization takes precedent over default initializations
/*
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s2 { 5, 6, 7 }; // use explicit initializers for s2.x , s2.y, and s2.z
                              //(no default values are used)

    return 0;
}
*/



// In last chapter, we saw that if an aggregate is initialized but the number of initialized
// values is fewer than the number of member variables, the variables get initialized in the
// order they show up in the definition of the aggregate (here the struct) and the remaining
// members will be value-initialized (e.g. int will be 0, double will be 0.0, and std::string
// will be "")

// Hence, the program below captures all cases
/*
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1;             // No initializer list: s1.x is uninitialized, s1.y and s1.z use defaults
    Something s2 { 5, 6, 7 }; // Explicit initializers: s2.x, s2.y, and s2.z use explicit values (no default values are used)
    Something s3 {};          // Missing initializers: s3.x is value initialized, s3.y and s3.z use defaults

    return 0;
}
*/


// The case we want to watch out for is s1.x. Because s1 has no initializer list and x has no
// default member initializer, s1.x remains uninitialized (which is bad, since we should always
// initialize our variables).


// -------------------------------------- Best Practice ---------------------------------------
// Always provide default values for your members. This ensures that your members will be
// initialized even if the variable definition doesn’t include an initializer list.


struct Fraction
{
	int numerator { }; // we should use { 0 } here, but for the sake of example we'll use value initialization instead
	int denominator { 1 };
};

int main()
{   
    // default initialization
	Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1

    // value-initialization
	Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1

    // Explicit initialization
	Fraction f3 { 6 };    // f3.numerator initialized to 6, f3.denominator defaulted to 1
	Fraction f4 { 5, 8 }; // f4.numerator initialized to 5, f4.denominator initialized to 8

	return 0;
}



// ----------------------------------- Best Practice -----------------------------------------
// For aggregates, prefer value initialization (with an empty braces initializer) to default
// initialization (with no braces).
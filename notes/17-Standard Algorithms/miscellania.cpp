// To run and execute this separately, run g++ miscellania.cpp -o main on your VSCode
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

// Here we teach the prerequisites of functions in vector_algos.cpp of this chapter


int main() {
    // We start off by std::copy --> std::copy is a C++ Standard Library algorithm in <algorithm>
    // It copies elements from a source range to a destination range 
    // Header: #include <algorithm>
    // Time Complexity: O(N)
    // Syntax: std::copy(first , last , d_last)
    // first, last: Iterators marking the beginning and ending of a source range
    // d_last: Iterator marking the start of the destination

    // Example:
    std::cout << "Building the source as {1 ,2 , 3 , 4 , 5}" << std::endl;
    std::cout << "constructing an empty destination of size() 5" << std::endl;
    std::vector<int> source = {1 , 2 , 3 , 4 , 5};
    std::vector<int> dest(source.size());    // Allocates space for a vector of size source.size()

    std::cout << "std::copy(source.begin() , source.end() , dest.begin());" << std::endl;
    std::copy(source.begin() , source.end() , dest.begin());
    std::cout << "The destination now is :";
    for (auto num : dest)
        std::cout << " " << num;
    std::cout << std::endl;


    // Notice how we needed to allocate memory prior to copying
    // To avoid this, we can utilize std::back_inserter. It calls push_back() on the 
    // destination container, effectively handling dynamic resizing
    // std::back_inserter is from <iterator>
    
    std::cout << "Building the source1 as {1 ,2 , 3 , 4 , 5}" << std::endl;
    std::cout << "constructing an empty destination with no pre-allocated memory" << std::endl;
    std::vector<int> source1 = {1 , 2 , 3 , 4 , 5};
    std::vector<int> dest1;

    std::cout << "std::copy(source1.begin() , source1.end() , std::back_inserter(dest1));" << std::endl;
    std::copy(source1.begin() , source1.end() , std::back_inserter(dest1));
    std::cout << "The destination now is :";
    for (auto num : dest1)
        std::cout << " " << num;
    std::cout << std::endl;

    // Now let's see what std::istream_iterator is: Not all streams are created equal. They form a
    // hierarchy based on the operations they support. Below is their hirarchy:
    // 1. Random Access: Iterators like std::vector iterators jump freely from index i to index j,
    // compare with <, etc
    // 2. Bidirectional: Some are bidirectional: e.g. can go forward or backward 
    // (++it, --it, it = it + 5 etc etc)
    // Forward: Some can only go forward, but can revisit elements they pass on their forward move
    // Input: the most limited type of iterators. You can only ++iy, read *it (i.e. dereference), 
    // and check it (it == other). Once you move past an element, it is gone!

    // std::istream_iterator<int> is an "input iterator". You cannot go back to a number you have
    // already read from cin, and you cannot skip ahead 5 numbers without reading the ones in 
    // between.

    // Good news: std::copy only needs to increment, dereference, and compare--so input iterators 
    // are enough

    // Type{args} Syntax: Type{arg1 , arg2} constructs a "temporary" argument of that type e.g.
    std::vector<int>{1 , 2 , 15};          // temporary vector with 3 integer elements
    std::string{"Saeed"};                  // temporary string
    // std::istream_iterator<int>{stream}; // temporary iterator pointing at stream's current position
    std::istream_iterator<int>{};           // temporary "end" iterator (no args)
    std::vector<std::string>{"Saeed " , "loves " , "Razan " , "a " , "lot."}; // temporary
    std::vector<std::string> cheers = {"Saeed " , "loves " , "Razan " , "a " , "lot."}; 
    for (auto word : cheers)
        std::cout << word;
    std::cout << std::endl;


    // The last one with empty braces is a special version of istream_iterator
    // It represents the end of ANY stream: when a stream hits EOF or a read failure, it compares
    // equal to this iterator--that is how std::copy knows how to stop

    // SO, in order to keep reading the input stream and pushing it to a result integer vector 
    // that is NOT preoccupying some space, we use the following code snippet:
    std::istream& stream = std::cin;  // a reference to an input stream object with initial value std::cin
    std::vector<int> result;
    std::copy(
        std::istream_iterator<int>{stream} , // start: read ints from stream
        std::istream_iterator<int>{} , // stop: when stream is done
        std::back_inserter(result) 
    );
    std::cout << "The vector of integers you created via std::copy is ";
    for (auto num : result)
        std::cout << " " << num;
    std::cout << std::endl;

    // std::istream_iterator<int> means “an input iterator that reads integers from a stream

    // std::accumulate is from <numeric> library and is used to combine values in a range
    std::cout << "std::vector<int> v{1 , 2 , 3 , 4 , 5};" << std::endl; 
    std::vector<int> v{1 , 2 , 3 , 4 , 5};

    std::cout << "int sum = std::accumulate(v.begin() , v.end() , 0);" << std::endl;
    int sum = std::accumulate(v.begin() , v.end() , -9);

    // std::accumulate(iterator first , iterator last , init)
    // first and last are iterators that define the range the needs to be processed
    // In python, this'd be equivalent to arr[first:last].sum() + init 
    // init is the initial value --> set usually to 0
    std::cout << "Sum is " << sum << std::endl;


    // Let's look at UnaryPredicate --> 
    // "A CALLABLE object that takes ONE argument and returns something convertible to bool"
    // Example: 
    // bool is_even(int x){ return (x % 2 == 0);};
    // auto is_even [] (int x) { return (x % 2 == 0); };

    // Many standard algorithms expect a UnaryPredicate. Example
    // std::vector<int> v{1 , 2 , 3 , 4 , 5}; std::find_if(v.begin() , v.end() , is_even)
    // find_if asks if given "one element", a condition holds. The condition is a UnaryPredicate
    // That condition is a UnaryPredicate
    // UnaryPredicate can also be a lambda (anonymous function or a function without a name)
    // Structure of a lambda: 
    // [capture] (parameter) {
    //      body
    // }                               e.g. [](int x) { return (x % 2 == 0)}; 


    // Now let's look at std::all_of --> is a C++ Standard Library algorithm 
    // checks if a condition is true for "every element" in a range
    // std::all_of returns true if a uniary predicate returns true for all elements in the range
    // [first , last); If the range is empty --> it returns true by default
    // Returns: A boolean value—true if all elements satisfy the condition, otherwise false.

    std::cout << "The list of integers you just entered a few seconds ago :" << std::endl;
    for (auto num : result)
        std::cout << " " << num;
    std::cout << std::endl;

    std::cout << "Now let's check if all of them are positive using std::all_of " << std::endl;
    auto is_positive = [] (int x) { return (x > 0); };
    bool is_all_positive = std::all_of(result.begin() , result.end() , is_positive);
    std::cout << "Are all elements of result positive ? " << is_all_positive << std::endl;

    return 0;
}
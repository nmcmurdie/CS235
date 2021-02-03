#include <iostream>
#include <fstream>
#include "MyArray.h"
using namespace std;

// Determine if a number is prime
bool isPrime(int number) {
    if (number < 2) return false;
    for (int i = 2; i < number; ++i) {
        if (number % i == 0) return false;
    }
    return true;
}

// Determine if a number is composite
bool isComposite(int number) {
    return (number > 1 && !isPrime(number));
}

int main(int argc, const char * argv[]) {
    // Open Files
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    
    ifstream in(argv[1]);
    if (!in)  {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    ofstream out(argv[2]);
    
    // Create new MyArray and input data to it
    MyArray<int> numbers(MAX_ARRAY_SIZE);
    int input;
    while (in >> input) {
        numbers.push_back(input);
    }
    out << "myArray: " << endl << numbers << endl;
    
    // Print iterators
    out << "ITERATORS:";
    out << endl << "begin(): " << numbers.begin();
    out << endl << "end(): " << numbers.end();
    out << endl << endl;
    
    // Print array using iterator
    out << "SEQUENTIAL:" << endl;
    MyArray<int>::Iterator iter = numbers.begin();
    for (int i = 0; iter != numbers.end(); ++iter, ++i) {
        if (i > 0 && i % 10 == 0) out << endl;
        out << *iter << " ";
    }
    out << endl << endl;
    
    // Print prime numbers
    out << "PRIME:" << endl;
    iter = numbers.begin();
    for (int c = 0; iter != numbers.end(); ++iter) {
        if (isPrime(*iter)) {
            out << *iter << " ";
            if (++c % 10 == 0 && c > 0) out << endl;
        }
    }
    out << endl << endl;
    
    // Print composite numbers
    out << "COMPOSITE:" << endl;
    iter = numbers.begin();
    for (int c = 0; iter != numbers.end(); ++iter) {
        if (isComposite(*iter)) {
            out << *iter << " ";
            if (++c % 10 == 0 && c > 0) out << endl;
        }
    }
    out << endl << endl;
    
    // Print fibonacci numbers
    out << "FIBONACCI:" << endl;
    iter = ++++numbers.begin();
    MyArray<int>::Iterator first = numbers.begin(), second = ++numbers.begin();
    for (; iter != numbers.end(); ++iter, ++first, ++second) {
        if (*first + *second == *iter) {
            out << *iter << " = " << *first << " + " << *second << endl;
        }
    }
    
    return 0;
}

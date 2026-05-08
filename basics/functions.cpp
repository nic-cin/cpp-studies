// 01-basics/functions.cpp
// functions, overloading, default args
// compile: g++ functions.cpp -o functions && functions

#include <iostream>
#include <string>
using namespace std;

// basic function
int add(int a, int b) {
    return a + b;
}

// function overloading
double add(double a, double b) {
    return a + b;
}

// default arguments
void greet(string name, string prefix = "hello") {
    cout << prefix << ", " << name << "!\n";
}

// pass by value vs reference
void byValue(int x)  { x = 99; }
void byRef(int &x)   { x = 99; }

// return multiple values via reference params
void minMax(int arr[], int size, int &minVal, int &maxVal) {
    minVal = maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

// recursive function
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    cout << "add(3, 4)      = " << add(3, 4)       << "\n";
    cout << "add(1.5, 2.5)  = " << add(1.5, 2.5)   << "\n\n";

    greet("world");
    greet("c++", "what's up");

    int a = 10;
    byValue(a); cout << "\nbyValue -> a = " << a << " (unchanged)\n";
    byRef(a);   cout << "byRef   -> a = " << a << " (changed)\n";

    int arr[] = {4, 1, 9, 2, 7};
    int lo, hi;
    minMax(arr, 5, lo, hi);
    cout << "\nmin = " << lo << ", max = " << hi << "\n";

    cout << "\nfactorial(6) = " << factorial(6) << "\n";

    return 0;
}

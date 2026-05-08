// 01-basics/loops.cpp
// exploring loops and control flow in c++
// compile: g++ loops.cpp -o loops && loops

#include <iostream>
using namespace std;

int main() {
    // for loop
    cout << "for loop:\n";
    for (int i = 0; i < 5; i++) {
        cout << "  i = " << i << "\n";
    }

    // while loop
    cout << "\nwhile loop (countdown):\n";
    int n = 5;
    while (n > 0) {
        cout << "  " << n << "...\n";
        n--;
    }
    cout << "  go!\n";

    // range-based for (c++11)
    cout << "\nrange-based for:\n";
    int nums[] = {10, 20, 30, 40, 50};
    for (int x : nums) {
        cout << "  " << x << "\n";
    }

    // do-while
    cout << "\ndo-while:\n";
    int count = 0;
    do {
        cout << "  count = " << count << "\n";
        count++;
    } while (count < 3);

    // break and continue
    cout << "\nskipping evens with continue:\n";
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;
        cout << "  " << i << "\n";
    }

    return 0;
}

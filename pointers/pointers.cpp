// 02-pointers/pointers.cpp
// pointers, references, dynamic memory
// compile: g++ pointers.cpp -o pointers && pointers

#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "  arr[" << i << "] = " << *(arr + i)
             << "  (addr: " << (arr + i) << ")\n";
    }
}

void allocate(int **ptr, int value) {
    *ptr = new int(value);
}

int main() {
    int x = 42;
    int *p = &x;

    cout << "=== basics ===\n";
    cout << "x         = " << x  << "\n";
    cout << "&x (addr) = " << &x << "\n";
    cout << "p         = " << p  << "\n";
    cout << "*p        = " << *p << "\n";

    *p = 100;
    cout << "after *p = 100 -> x = " << x << "\n\n";

    cout << "=== null pointer ===\n";
    int *null_ptr = nullptr;
    if (null_ptr == nullptr)
        cout << "null_ptr is null -- safe to check\n\n";

    cout << "=== swap ===\n";
    int a = 5, b = 9;
    cout << "before: a=" << a << " b=" << b << "\n";
    swap(&a, &b);
    cout << "after:  a=" << a << " b=" << b << "\n\n";

    cout << "=== pointer arithmetic ===\n";
    int arr[] = {10, 20, 30, 40, 50};
    printArray(arr, 5);
    cout << "\n";

    cout << "=== dynamic memory ===\n";
    int *heap_int = new int(77);
    cout << "heap value = " << *heap_int << "\n";
    delete heap_int;
    heap_int = nullptr;
    cout << "freed heap_int\n\n";

    cout << "=== dynamic array ===\n";
    int size = 4;
    int *dyn = new int[size];
    for (int i = 0; i < size; i++) dyn[i] = (i + 1) * 11;
    for (int i = 0; i < size; i++) cout << "  dyn[" << i << "] = " << dyn[i] << "\n";
    delete[] dyn;
    cout << "freed dynamic array\n\n";

    cout << "=== double pointer ===\n";
    int *managed = nullptr;
    allocate(&managed, 999);
    cout << "allocated via double ptr -> " << *managed << "\n";
    delete managed;

    return 0;
}

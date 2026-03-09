/* test_cpp.cpp
 * Simple tests to observe C++ type compatibility rules.
 * Compile with: g++ -Wall test_cpp.cpp -o test_cpp.exe
 */
#include <iostream>
using namespace std;

int main() {
    int i = 42;
    double d = i; // implicit widening allowed
    cout << "int i = " << i << " -> double d = " << d << endl;

    double e = 3.1415;
    int j = (int)e; // explicit cast for narrowing
    cout << "double e = " << e << " -> int j = " << j << " (after cast)" << endl;

    int arr[3] = {1,2,3};
    void* pv = arr;
    // In C++ implicit void* -> int* is NOT allowed without cast; the next line would be error:
    // int* pi = pv; // error: ISO C++ forbids converting a void* to int* without a cast
    int* pi = static_cast<int*>(pv); // allowed with cast
    cout << "arr[0] via int* from void* (with cast) = " << pi[0] << endl;

    // list-initialization narrowing is forbidden (C++11): uncommenting would be an error
    // int x {3.14}; // error: narrowing conversion

    return 0;
}

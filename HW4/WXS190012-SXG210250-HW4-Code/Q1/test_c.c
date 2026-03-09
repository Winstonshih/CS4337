/* test_c.c
 * Simple tests to observe C type compatibility rules.
 * Compile with: gcc -Wall test_c.c -o test_c.exe
 */
#include <stdio.h>

int main(void) {
    int i = 42;
    double d = i; /* implicit widening: int -> double (allowed) */
    printf("int i = %d -> double d = %f\n", i, d);

    double e = 3.14;
    int j = (int)e; /* narrowing requires explicit cast to avoid warning/precision loss */
    printf("double e = %f -> int j = %d (after cast)\n", e, j);

    unsigned int ui = 0u;
    int negative = -1;
    ui = negative; /* allowed, but results in wrap (implementation-defined behavior printed) */
    printf("assign -1 to unsigned -> ui = %u\n", ui);

    int arr[3] = {1,2,3};
    void *pv = arr; /* object pointer to void* implicit in C (allowed) */
    int *pi = pv; /* implicit void* -> int* is allowed in C */
    printf("arr[0] via int* from void* = %d\n", pi[0]);

    /* The following examples would be illegal (compile errors) in C if uncommented:
    int *bad = 5; // error: integer to pointer without cast (not allowed)
    double *dp = &e; int *ip = dp; // incompatible pointer types (should cast)
    */

    return 0;
}

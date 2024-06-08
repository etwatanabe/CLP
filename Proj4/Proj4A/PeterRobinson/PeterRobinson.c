#include <stdio.h>

int A(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return A(m - 1, 1);
    } else if (m > 0 && n > 0) {
        return A(m - 1, A(m, n - 1));
    }
    return 0;
}

int main() {
    int m = 5, n = 0;
    /*
    (5,0)
    (4,1)
    (3,13)
    (2,...)
    */

    printf("A(%d, %d) = %d\n", m, n, A(m, n));
    return 0;
}

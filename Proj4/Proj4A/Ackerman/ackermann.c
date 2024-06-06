#include <stdio.h>

int ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else if (m > 0 && n > 0) {
        return ackermann(m - 1, ackermann(m, n - 1));
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

    printf("Ackermann(%d, %d) = %d\n", m, n, ackermann(m, n));
    return 0;
}

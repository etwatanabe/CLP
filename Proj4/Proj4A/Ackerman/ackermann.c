#include <stdio.h>

int phi(int m, int n, int p) {
    if (p == 0) {
        return m + n;
    } else if (n == 0) {
        if (p == 1) {
            return 0;
        }
        else if (p == 2) {
            return 1;
        }
        else {
            return m;
        }
    } else {
        return phi(m, phi(m, n - 1, p), p - 1);
    }
}

int main() {
    int m = 7, n = 1, p = 3;

    printf("phi(%d, %d, %d) = %d\n", m, n, p, phi(m, n, p));
    return 0;
}

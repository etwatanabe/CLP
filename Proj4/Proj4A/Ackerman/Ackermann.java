public class Ackermann {

    public static int phi(int m, int n, int p) {
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

    public static void main(String[] args) {
        int m = 3, n = 12;

        System.out.println("phi(" + m + ", " + n + ", " + p + ") = " + phi(m, n, p));
    }
}

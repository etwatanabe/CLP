public class Ackermann {

    public static int ackermann(int m, int n) {
        if (m == 0) {
            return n + 1;
        } else if (m > 0 && n == 0) {
            return ackermann(m - 1, 1);
        } else if (m > 0 && n > 0) {
            return ackermann(m - 1, ackermann(m, n - 1));
        }
        return 0;
    }

    public static void main(String[] args) {
        int m = 3, n = 12;
        /*
         * (3,12)
         * (2,...)
         */

        System.out.println("Ackermann(" + m + ", " + n + ") = " + ackermann(m, n));
    }
}

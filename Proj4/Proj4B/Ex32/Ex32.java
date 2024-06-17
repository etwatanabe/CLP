public class Ex32 {

    public static int fat(int n) {
        if (n == 1) {
            return 1;
        } else {
            return n * fat(n - 1);
        }
    }

    public static int pot(int x, int n) {
        if (n == 0) {
            return 1;
        } else {
            return x * pot(x, n - 1);
        }
    }

    public static double e(int x, int n) {
        if (n == 0) {
            return 1.0;
        } else {
            return e(x, n - 1) + (double) pot(x, n) / fat(n);
        }
    }

    public static void main(String[] args) {
        System.out.printf("%.20f", e(2, 27));
    }
}

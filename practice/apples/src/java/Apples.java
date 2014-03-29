import java.util.Scanner;

public class Apples
{
    public static void main(String[] args) {
        int P, p, K;
        long A, B, result;

        Scanner input = new Scanner(System.in);

        P = input.nextInt();

        for (p = 1; p <= P; p++) {
            K = input.nextInt();
            A = input.nextLong();
            B = input.nextLong();

            result = (A / 2L) + (B / 2L);

            if (A % 2L == 1 && B % 2L == 1)
                result += 1;

            System.out.println(K + " " + result);
        }
    }
}

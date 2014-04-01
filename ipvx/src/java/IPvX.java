import java.util.Scanner;
import java.math.BigInteger;

public class IPvX
{
    public static void main(String[] args) {
        int P, k, M, N;
        BigInteger mask, gap;

        Scanner in = new Scanner(System.in);

        /* Number of datasets */
        P = in.nextInt();

        for (k = 1; k <= P; k++) {
            /* Ignore data set number */
            in.nextInt();

            /* 2 <= M <= 64, 1 <= N < M */
            M = in.nextInt();
            N = in.nextInt();

            mask = BigInteger.ONE.shiftLeft(M).subtract(BigInteger.ONE);
            gap = mask.xor(mask.shiftRight(M-N));

            System.out.print(k);
            while (N-- >= 0) {
                System.out.print(" " + mask.andNot(gap));
                gap = gap.shiftRight(1);
            }
            System.out.println();
        }
    }
}

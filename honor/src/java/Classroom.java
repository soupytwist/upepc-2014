import java.util.ArrayList;
import java.util.List;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Classroom {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner input = new Scanner(System.in);
        int T, t, R, C, r, c, numSeats, s;
        long seats, row;
        
        /* Read the number of datasets */
        T = input.nextInt();
        
        /* Process each dataset */
        for (t = 1; t <= T; t++) {
            
            /* Ignore the dataset number */
            input.nextInt();
            
            /* Read in the number of rows and columns */
            R = input.nextInt();
            C = input.nextInt();
            
            List<SeatingArrangement> prev = new ArrayList<SeatingArrangement>(1);
            SeatingArrangement emptySeating = new SeatingArrangement(0L, 0);
            prev.add(emptySeating);
            
            /* Read each row */
            for (r = 0; r < R; r++) {
                
                /* Read in the empty seats in this row */
                seats = (1 << C) - 1;
                numSeats = input.nextInt();
                
                while (--numSeats >= 0) {
                    s = input.nextInt();
                    assert(s >= 0 && s < C);
                    
                    /* Set the bit in seats to flag this seat */
                    seats -= (1 << s);
                }
                
                List<SeatingArrangement> possibilities = validArrangements(seats, C);
                
                for (SeatingArrangement next : possibilities) {
                    int ct = -1;
                    SeatingArrangement bestFront = null;
                    for (SeatingArrangement front : prev)
                        if (next.validBehind(front) && front.getStudents() > ct) {
                            ct = front.getStudents();
                            bestFront = front;
                        }
                    
                    next.applyBehind(bestFront);
                }
                
                prev = possibilities;
            }
            
            SeatingArrangement best = emptySeating;
            for (SeatingArrangement arrangement : prev)
                if (arrangement.getStudents() > best.getStudents())
                    best = arrangement;

            System.out.println(t + " " + best.getStudents());
        }
        
        input.close();
    }
    
    public static List<SeatingArrangement> validArrangements(long seats, int C) {
        List<SeatingArrangement> sas = new ArrayList<SeatingArrangement>();
        sas.add(new SeatingArrangement(0L, 0));
        for (int i = 0; i < C; i++) {
            addValidArrangements(seats, C, sas, 0L, 0, i);
        }
        return sas;
    }
    
    public static void addValidArrangements(long seats, int C, List<SeatingArrangement> list, long row, int ct, int i) {
        if ((seats & (1L << i)) != 0) {
            long tmp = row | (1L << i);
            list.add(new SeatingArrangement(tmp, ct+1));
            for (int j = i+2; j < C; j++)
                addValidArrangements(seats, C, list, tmp, ct+1, j);
        }
    }
}

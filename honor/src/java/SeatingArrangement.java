import java.util.LinkedList;
import java.util.List;


public class SeatingArrangement {

	private int students;
	private long seating;
	private List<Long> history;
	
	public SeatingArrangement(long seating, int students) {
		this.seating = seating;
		this.students = students;
		this.history = new LinkedList<Long>();
	}
	
	public long getSeating() {
		return seating;
	}
	
	public int getStudents() {
		return students;
	}
	
	public List<Long> getHistory() {
		return history;
	}
	
	public void applyBehind(SeatingArrangement front) {
		this.students += front.getStudents();
		this.history.addAll(front.getHistory());
		this.history.add(front.getSeating());
	}
	
	public boolean validBehind(SeatingArrangement front) {
		long maybeValid = this.seating & ~(front.getSeating() & this.seating);
		return ((maybeValid >> 1 | maybeValid << 1) & front.getSeating()) == 0; 
	}
	
	public String toString() {
		String res = "";
		long s = seating;
		for (; s > 0; s >>= 1)
			res += ((s & 1) != 0 ? "x" : "-");
		return res;
	}
}

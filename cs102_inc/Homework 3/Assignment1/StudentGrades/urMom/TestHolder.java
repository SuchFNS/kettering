package urMom;
public class TestHolder {
	private int[] testScores;
	
	public TestHolder(int studentCount) {
		testScores = new int[studentCount];
		for (int i=0; i < studentCount; i++) {
			testScores[i] = (int) Math.floor(Math.random() * 101);
		}
	}

	// Constructor above is 3a
	
	public String toString() {
		String retVal = "Test scores for this class: ";
		for (int i : testScores) {
			retVal += i + " ";
		}
		return retVal;
	}
	
	public boolean equals(TestHolder other) {
		return other == this;
	}
	
	public int[] getScores() {
		return this.testScores;
	}
	
	public void setScores(int[] testScores) {
		this.testScores = testScores;
	}
	
	public int[] sortScores(int[] arr) {
		int n = arr.length; 
        for (int i = 0; i < n-1; i++) 
            for (int j = 0; j < n-i-1; j++) 
                if (arr[j] > arr[j+1]) 
                { 
                    // swap arr[j+1] and arr[j] 
                    int temp = arr[j]; 
                    arr[j] = arr[j+1]; 
                    arr[j+1] = temp; 
                }
        return arr;
	}
	
	public int getHighest(int[] scores) {
		int[] sorted = sortScores(scores);
		return sorted[sorted.length - 1];
	}
	
	public int getAverage(int[] scores) {
		int sum = 0;
		
		for (int i = 0; i < scores.length; i++) {
			sum += scores[i];
		}
		return sum / scores.length;
	}
	
	public int getMedian(int[] scores) {
		
	}
	
	public int getMode(int[] scores) {
		
	}
	
	// Everything above is 3b
	
	public static void main(String[] args) {
		TestHolder b = new TestHolder(50);
		System.out.println(b);
	}
}

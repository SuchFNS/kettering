/*
 * Programmed by: Colin Quinn
 * CS 203
 * The goal of this program is to efficiently solve 
 * the nQueens problem using iterative repair. By 
 * comparing diagonal collisions, swap queen locations
 * to minimize number of collisions until there are 
 * none left. Keep track of runtime and output results
 * in a readable format.
 */

import java.util.Scanner;
import java.util.Arrays;
import java.util.Collections;

public class iterativeRepair {

	static int N;
   static int numExecutions = 10;
   static int swapCount;
	
	public static void main(String args[]) {
		
		//get user input
		Scanner input = new Scanner(System.in);
		do {
			System.out.println("Input a number greater than 3.");
			N = input.nextInt();
		}while (N < 4);
		input.close();
		
      int[][] finalBoard = new int[N][N];
      
      double[] runTimes = new double[numExecutions];
      int[] swapCounts = new int[numExecutions];
      
      for (int i = 0; i < numExecutions; i++){
         long startTime = System.nanoTime();
		/*
		 * START MAIN ALGORITHM
		 */
	      finalBoard = mainAlgorithm();
         
		   //assign runtime to spot in array
         long totalTime = System.nanoTime() - startTime;
         double timeConverted = (double) totalTime / 1000000000.0;
         runTimes[i] = timeConverted;
         swapCounts[i] = swapCount;
         swapCount = 0;
         
      }
      printBoard(finalBoard);
      
      //output average runtime & swap count after 10 executions
      double sum = 0;
      int sumSwaps = 0;
      for (int i = 0; i < numExecutions; i++){
         System.out.println("Run " + i + ": " + runTimes[i]);
         sum += runTimes[i];
         sumSwaps += swapCounts[i];
         
      }
      System.out.println((sum / numExecutions) + " seconds average run time");
      System.out.println((sumSwaps/numExecutions) + " average swaps");
	}
	/*
	 * Start the main algorithm.
	 * Main will track runtime of this function
	 * since it will be the entire nQueens algorithm.
	 */
	public static int[][] mainAlgorithm() {      
		//create and initialize chess board
		int[][] board = initBoard();
		
		//get collision patterns from generated board
		int[] queensPD = checkPositiveDiag(board);
		int[] queensND = checkNegativeDiag(board);
		
      //main loop for algorithm
      //continue until there are no collisions
      while(countConflicts(queensPD, queensND) > 0){
         boolean swapPerformed = false;
         for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
               int currentNumConflicts = countConflicts(queensPD, queensND);
               
               board = swapQueens(i, j, board);
               queensPD = checkPositiveDiag(board);
               queensND = checkNegativeDiag(board);
               int tempConflicts = countConflicts(queensPD, queensND);
               
               if (tempConflicts < currentNumConflicts){
                  swapPerformed = true; 
                  swapCount++;
                  break;
               }else board = swapQueens(i, j, board);
               //^^^swap back to original board
               
               //update queensPD and queensND
               queensPD = checkPositiveDiag(board);
               queensND = checkNegativeDiag(board);
            }
         }
         if (!swapPerformed){
          	Collections.shuffle(Arrays.asList(board));
         }         
      }
      return board;
	}
	
   public static int countConflicts(int[] pD, int[] nD){
      int numConflicts = 0;
      //loop through positive diagonal array and count conflicts
      for (int i = 0; i < pD.length; i++){
         if (pD[i] > 1){
            numConflicts += pD[i] - 1;
         }
      }
      //loop through negative diagonals and count conflicts
      for (int i = 0; i < nD.length; i++){
         if (nD[i] > 1){
            numConflicts += nD[i] - 1;
         }
      }
      //return total amount of conflicts
      return numConflicts;
   }
   
	/*
	 * loop through an array 2n-1 size for each positive diagonal.
	 * walk through each element of matrix comparing indexes to  
	 * determine diagonals, positive diagonals have equal sums of
	 * indexes. Add each value at each given diagonal and store 
	 * number of queens on that diagonal in an array.
	 */
	public static int[] checkPositiveDiag(int[][] board) {
		
		int[] numQueens = new int[2*N - 1];
		int sum = 0;
		//index of diagonals array
		for (int i = 0; i < (2*N - 1); i++) {
			//nested loops for checking matrix
			for (int j = 0; j < N; j++) {
				for(int k = 0; k < N; k++) {
					//when on current diagonal, add element
					if (j + k == i) {
						sum += board[j][k];
					}
				}
			}
			//store number of queens in array and reset sum of queens
			numQueens[i] = sum;
			sum = 0;
		}
		
		return numQueens;//total num of queens on diagonals
	}
	
	/*
	 * loop through an array 2n-1 size for each negative diagonal.
	 * walk through each element of matrix comparing indexes to  
	 * determine diagonals, negative diagonals have equal differences of
	 * indexes. Add each value at each given diagonal and store 
	 * number of queens on that diagonal in an array.
	 */
	public static int[] checkNegativeDiag(int[][] board) {
		
		int[] numQueens = new int[2*N - 1];
		int sum = 0;
		//index of diagonals array
		//i starts at -N+1 due to difference relying on order
		for (int i = (0 - N + 1); i < N; i++) {
			//nested loop to check matrix values
			for (int j = 0; j < N; j++) {
				for(int k = 0; k < N; k++) {
					//when on current diagonal, add element
					if (j - k == i) {
						sum += board[j][k];
					}
				}
			}
			//store number of queens in array and reset sum of queens
			//adjust index for offset of original indexing	
			numQueens[i + N - 1] = sum;
			sum = 0;
		}
		return numQueens;//total num of queens on diagonals
	}
	
	/*
	 * swap 2 queen's locations by switching the contents of a column
	 */
	public static int[][] swapQueens(int column1, int column2, int[][] boardState) {
		//loop to swap desired columns
		for (int i = 0; i < N; i++) {
			int temp = boardState[i][column1];
			boardState[i][column1] = boardState[i][column2];
			boardState[i][column2] = temp;
		}
		//return state of board after swap
		return boardState;	
	}
	
	/*
	 * print the valid board in a viewable format
	 */
	public static void printBoard(int board[][]) {
		for (int i = 0; i < board.length; i++) {
			for (int j = 0; j < board.length; j++) {
				System.out.print(board[i][j] + "\t");
			}
			System.out.println("\n");
		}
	}
	
	/*
	 * initialize the board with queens on main diagonal
	 */
	public static int[][] initBoard(){
		
		int board[][] = new int[N][N];
		//place queens on main negative diagonal
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j) {
					board[i][j] = 1;
				}else board[i][j] = 0;
			}
		}
		//shuffle queens into random location
		//keeps queens off of vertical and horizontal collisions
		Collections.shuffle(Arrays.asList(board));
		//return shuffled board
		return board;
	}
	
}

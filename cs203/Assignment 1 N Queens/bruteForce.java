/*
 * Written by: Colin Quinn
 * CS 203
 *The goal of this program is to generate all possible
 *queen layouts for a give sized chess board. Once all 
 *queens are placed, check if the board is a valid 
 *solution to the problem and repeat until one is found.
 *Keep track of the time it took and the number of 
 *recursive calls to compare efficiency of algorithm.
 */

import java.util.Scanner;

public class bruteForce {
   //globals to keep consistent with recursion
	static int N;
   static int boardsGenerated;
   static long startTime, finishTime;
   static int boardsFound = 0;
	
	public static void main(String[] args) {
		
		//get user input for board size/number of queens
		System.out.println("How many queens would you like?");
		Scanner input = new Scanner(System.in);
		N = input.nextInt();
		
		//create and initialize empty array for the chess board
		int[][] board = new int[N][N];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j] = 0;
			}
		}
		
		//start recursive call to the placement algorithm
      startTime = System.nanoTime();
		int queenNum = 1;
		placeQueen(board, queenNum);
      
      //convert algorithm run time to seconds from nanoseconds
      double timeConverted = (double) (finishTime - startTime) / 1000000000.0;
      
      //output the converted data to console
      System.out.println(timeConverted + " seconds");
      System.out.println(boardsGenerated + " boards generated");
		
	}
	
	//recursive function to place queens in each position on the board
	public static boolean placeQueen(int[][] board, int queenNum) {
      //stop when first valid board is found
      if (boardsFound > 0){
         return true;
      }
		
		//loop through matrix
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < N; col++) {
				
				//check number of queens
				if (queenNum == N + 1) {
					//check board for validity
               if (checkBoard(board)){
                  //get time of board being found
                  finishTime = System.nanoTime();
                  boardsFound++;
                  //print board and break recursion
                  printBoard(board);
                  return true;
               }
					break;
            //else board not found, place queen in next spot and recurse
				}else {
					if (board[row][col] == 0) {
						board[row][col] = queenNum;
						placeQueen(board, queenNum + 1);
					}
				}
            //keep track of total boards generated
				boardsGenerated++;
				
				//reset last queen placed
				if (board[row][col] == queenNum) {
					board[row][col] = 0;
				}
				
			}
		}
		return false;
	}
   
   //check if the board is a valid solution based on columns,
   //rows, and diagonal based collisions.
   public static boolean checkBoard(int[][] board){
      
      int sum = 0;
      //check rows
      for (int i = 0; i < N; i++){
         for (int j = 0; j < N; j++){
            if (board[i][j] > 0){
              sum++; 
            }
         }
         if (sum > 1){
            return false;
         }
         sum = 0;
      }
      //check columns
      for (int i = 0; i < N; i++){
         for (int j = 0; j < N; j++){
            if (board[j][i] > 0){
              sum++; 
            }
         }
         if (sum > 1){
            return false;
         }
         sum = 0;
      }
      //check positive diagonals
      for (int i = 0; i < (2*board.length - 1); i++) {
			//nested loops for checking matrix
			for (int j = 0; j < board.length; j++) {
				for(int k = 0; k < board.length; k++) {
					//when on positive diagonal, increment
					if (j + k == i && board[j][k] > 0 ) {
						sum++;
					}
				}
            //return false if there is a collision
            if (sum > 1){
               return false;
            }
			}
         sum = 0;
		}
      //check negative diagonals
      //i starts at -N+1 due to difference relying on order
		for (int i = (0 - board.length + 1); i < board.length; i++) {
			//nested loop to check matrix values
			for (int j = 0; j < board.length; j++) {
				for(int k = 0; k < board.length; k++) {
					//when on current diagonal, add element
					if (j - k == i && board[j][k] > 0) {
						sum++;
					}
				}
            //return false if there is a collision
            if (sum > 1){
               return false;
            }
			}
			sum = 0;
		}
      //return true if a solution is found
      return true;
   }
	
	//call to print the board to the console
	public static void printBoard(int[][] board) {
		
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < N; col++) {
				System.out.print(board[row][col] + "\t");
			}
			System.out.println("\n");
		}
		
	}

}

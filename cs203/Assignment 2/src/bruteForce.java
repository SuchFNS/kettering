/*
 * Programmed by: Colin Quinn
 * CS 203 Assignment 2 Brute Force Algorithm
 * 
 * Brute force algorithm for finding the closest
 * pair of X,Y coordinates. Starting at the first 
 * point, compare with all following points, then
 * start again at 2nd point and continue until all
 * combinations of points have been calculated while
 * keeping track of the minimum distance and which
 * 2 points have the minimum distance. 
 * Output the run time, which 2 points, and the distance.
 */

import java.util.Scanner;
import java.util.Random;

public class bruteForce {
	
	//control scope of randomly generated points
	final static int MAX = 100000;
	static int index1, index2;

	public static void main(String[] args) {
		//get ready to perform the calculations for closest pair
		prepAlgorithm();
	}

	//gets the amount of points and generates list of points
	public static void prepAlgorithm() {
		//get number of points from user
		Scanner input = new Scanner(System.in);
		System.out.println("Input how many points you want: ");
		int n;
		do {
			n = input.nextInt();
		}while(n <= 1);
		
		//create random points array
		//X values in row 0, Y values in row 1
		int[][] points = initializePoints(n);
		
		//get the starting time of the algorithm
		long startTime = System.nanoTime();
		
		//main algorithm call to find minimum
		double min = findMinimum(points, n);
		
		//get finish time of algorithm
		double runTime = (double) ((System.nanoTime() - startTime) / 1000000.0);
		
		//output data to console
		System.out.println("The minimum distance " + min);
		System.out.println("The closest pair is: ("
				+ points[0][index1] + ", " + points[1][index1] + 
				") and (" + points[0][index2] + ", " + points[1][index2] + ")");
		System.out.println("Total run time is: " + runTime + " milliSeconds");
		
		
	}
	
	//randomly generate integers as coordinate points
	public static int[][] initializePoints(int n){
		
		Random num = new Random();
		int[][] array = new int[2][n];
		for (int i = 0;  i < n; i++) {
			array[0][i] = num.nextInt(MAX);
			array[1][i] = num.nextInt(MAX);
		}
		return array;
	}
	
	//brute force search for minimum distance between 2 points
	public static double findMinimum(int[][] points, int n) {
		
		double min = MAX;
		
		//quit loop at second to last index to avoid overstepping in next loop
		for (int i = 0; i < n - 1; i++) {
			//start loop at next index from current i index
			for (int j = i +  1; j < n; j++) {
				//calculate the distance between the 2 current points
				double distance = Math.sqrt(Math.pow(points[0][j] - points[0][i], 2) 
											+ Math.pow(points[1][j] -  points[1][i], 2));
				//update info when current is less than previous minimum
				if (distance < min) {
					min = distance;
					//update indexes of closest pair
					index1 = i;
					index2 = j;
				}
			}
		}
		//return the minimum distance
		return min;
	}
	
}

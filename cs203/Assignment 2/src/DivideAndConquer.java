/*
 * Programmed by: Colin Quinn
 * CS 203 Assignment 2, Divide and Conquer Algorithm
 * 
 * Divide and Conquer solution to finding the closest
 * pair of points in a 2d plane. Divides list in half 
 * based on sorted x coordinates, and compares points
 * on left and right side, then create a strip that is
 * minimum point distance wide of middle points, then
 * sort that strip based on y coordinates and compare
 * the coordinate points to the ones near itself within
 * the inner strip. Recursively repeat until there are 
 * 3 or less points and solve by brute force comparisons
 * and return minimum value found as well as indices that
 * compute this distance.
 */

import java.util.Scanner;
import java.util.Random;
import java.util.Arrays;

public class DivideAndConquer {

	//maximum variance of points
	static int MAX = 100000;
	//track indexes of the pair
	static int index1, index2;
	//minimum initialized to MAX^2 for first minimum calculation
	static float min = MAX * MAX;
	
	
	//swap info at two indexes for sorting algorithms
	public static void swap(Point[] p, int i, int j) {
			Point temp = p[i];
			p[i] = p[j];
			p[j] = temp;
	}
	
	/*
	 * Code for Hoare Partitioning quicksort adjusted from:
	 * https://www.techiedelight.com/quick-sort-using-hoares-partitioning-scheme/
	 * Adjustments were made in order to accommodate an array of points
	 * and sort based on the X values of the points
	 */
	//implements Hoare partitioning
	public static int Partition(Point[] p, int low, int high) {
	
		int pivot = p[low].getX();
		int i = low - 1;
		int j = high + 1;
		
		//loop and swap until indices have inverted
		while (true) {
			//find indices where left index is < pivot value
			do {
				i++;
			}while(p[i].getX() < pivot);
			
			do {
				//find indices where right index is > pivot value
				j--;
			}while(p[j].getX() > pivot);
			//case to break out of loop
			if (i >= j) {
				return j;
			}
			//swap values
			swap(p, i, j);
		}
	}
	//implement quicksort using Hoare partitioning
	public static void quickSort(Point[] p, int low, int high) {
		
		//base case
		if (low >= high) {
			return;
		}
		//rearrange elements based on pivot point
		int pivotIndex = Partition(p, low, high);
		
		//recursive calls to complete the sorting
		quickSort(p, low, pivotIndex);
		quickSort(p, pivotIndex + 1, high);
	}
	
	
	/*
	 * Code for Mergesort adjusted from:
	 * https://www.geeksforgeeks.org/merge-sort/
	 * Adjusted to handle Point class and sort by
	 * the Y values of each point
	 */
	public static void mergeSort(Point[] p,  int l, int r) {
		
		if (l < r) {
			int m = (l + r) / 2;
			
			//continue sorting each side
			mergeSort(p, l, m);
			mergeSort(p, m + 1, r);
			
			//merge the now sorted halves
			merge(p, l, m, r);
		}
		
	}
	//merge the split arrays
	public static void merge(Point[] p, int l, int m, int r) {
		
		//get sizes of temp arrays and initialize
		int left = m - l + 1;
		int right = r - m;
		Point[] pLeft = new Point[left];
		Point[] pRight = new Point[right];
		for (int i = 0; i < left; i++) {
			pLeft[i] = p[l + i];
		}
		for (int i = 0; i < right; i++) {
			pRight[i] = p[m + 1 + i];
		}
		
		//indexes for subarrays
		int i = 0;
		int j = 0;
		int k = l;
		//sort array based on contents of L and R subarrays
		while (i < left && j < right) {
			if (pLeft[i].getY() <= pRight[j].getY()) {
				p[k] = pLeft[i];
				i++;
			}else {
				p[k] = pRight[j];
				j++;
			}
			k++;
		}
		//copy remaining left elements
		while (i < left) {
			p[k] = pLeft[i];
			i++;
			k++;
		}
		//copy remaining right elements
		while (j < right) {
			p[k] = pRight[j];
			j++;
			k++;
		}
		
	}
	
	//implements the brute force solution for algorithm
	//when array size is <= 3 points
	public static float bruteForceSolve(Point[] p, int n) {
		//standard brute force solution
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				float distance = calcDistance(p[i], p[j]);
				//update minimum distance of points*
				if (distance < min) {
					min = distance;
					
					//track indexes of pair
					index1 = p[i].getIndex();
					index2 = p[j].getIndex();
				}
			}
		}
		//return minimum of these points
		return min;
	}
	
	//return the minimum of two doubles
	public static float findMin(float one, float two) {
		if (one < two) {
			return one;
		}else return two;
	}
	
	//return the distance of the two points given as input
	public static float calcDistance(Point one, Point two) {
		return (float) Math.sqrt( Math.pow((two.getX() - one.getX()), 2) + Math.pow((two.getY() - one.getY()), 2) );
	}
	
	//find the minimum distance from the current minimum and minimum within strip, return that value
	public static float computeStrip(Point[] innerStrip, int n, float distance) {
		
		//create minimum that starts as previous minimum
		//use the d^2 so square roots do not have to be repeatedly computed
		float tempMinimum = distance;
		
		//sort points based on y values
		mergeSort(innerStrip, 0, n - 1);
		
		//semi-brute force search the points in the strip
		for (int i = 0; i < n; i++) {			
			int k = i + 1;
			//loop runs a maximum of 6 iterations before moving on to next possible coordinate
			// based on that information, this nested loop runs in linear time rather than n^2
			while (k <= n - 1 && innerStrip[k].getY() - innerStrip[i].getY() < tempMinimum) {
				tempMinimum = findMin( calcDistance(innerStrip[i], innerStrip[k]), tempMinimum );
				//only update minimum if it is smaller than current minimum
				if (tempMinimum < distance) {
					distance = tempMinimum;
					//update indices of points for minimum distance
					index1 = innerStrip[i].getIndex();
					index2 = innerStrip[k].getIndex();
				}
				//increase inner index
				k++;
			}
		}
		//return the smallest distance found so far
		return distance;
	}
	
	//main logic of algorithm
	/*
	 * needs list of points and length of list as input
	 */
	public static float solveClosest(Point[] points, int n) {
		
		float distanceLeft, distanceRight, minDistance;
		
		//when 3 points are left, brute force solve the problem
		if (n <= 3) {
			return bruteForceSolve(points, n);
		}
		
		//get the mid point of array
		int middle = n / 2;
		
		//create array of each half of X values
		Point[] xLeft = Arrays.copyOfRange(points, 0, middle);
		Point[] xRight = Arrays.copyOfRange(points, middle, n - 1);
		
		//recursive calls to find left and right minimums
		distanceLeft = solveClosest(xLeft, xLeft.length);
		distanceRight = solveClosest(xRight, xRight.length);
		
		//get minimum of returned distances
		minDistance = findMin(distanceLeft, distanceRight);
		
		//create array of points within minimum distance of middle strip
		Point[] pointsInStrip = new Point[n];
		int stripIndex = 0;
		for (int i = 0; i < n; i++) {
			//check abs value of difference, if less than minDistance, add to strip
			if(Math.abs(points[i].getX() - points[middle].getX()) < minDistance) {
				pointsInStrip[stripIndex] = points[i];
				stripIndex++;
			}
		}
		
		//return the minimum distance from current min and min in the strip
		return findMin(minDistance, computeStrip(pointsInStrip, stripIndex, minDistance));
	}
	
	//starts the algorithm by sorting points by x value, then calls to solve
	public static float startAlgorithm(Point[] points, int n) {
		
		//sort all of points based on X values
		quickSort(points, 0, points.length - 1);
		
		return solveClosest(points, points.length);
		
	}
	
	
	//main method that starts program
	public static void main(String[] args) {
		
		//get info needed for algorithm
		Scanner input = new Scanner(System.in);
		System.out.println("Input how many points you want: ");
		int n;
		do {
			n = input.nextInt();
		}while(n <= 1);
		input.close();
		
		//create array of point objects with random coordinates
		Random rand = new Random();
		Point[] points = new Point[n];
		for (int i = 0; i < n; i++) {
			int x = rand.nextInt(MAX);
			int y = rand.nextInt(MAX);
			points[i] = new Point(x, y, i);
		}
		
		//get starting time of algorithm
		long startTime = System.nanoTime();
		
		
		//start algorithm with this function call 
		float closestDistance = startAlgorithm(points.clone(), n);
		
		//calculate algorithm runtime in milliseconds
		double runTime = (double) ((System.nanoTime() - startTime) / 1000000.0);

		//output data to console
		System.out.println("The closest pair is: (" + points[index1].getX() + ", " + points[index1].getY()
				+ ") and (" + points[index2].getX() + ", " + points[index2].getY() + ")");
		
		System.out.println(closestDistance);
		System.out.println("Algorithm took " + runTime + " milliseconds");
	}

}

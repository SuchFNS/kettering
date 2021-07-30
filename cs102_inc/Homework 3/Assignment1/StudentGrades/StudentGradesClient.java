/*
* Name:Hayvin Bolton
* Date:1/19/2020
* Question number: 3
* Description: Client Class to test the StudentGrades program
*/
package StudentGrades;
import java.util.*;

public class StudentGradesClient
{
   public static void main(String[] args)
   {
      //create a grades classes
		StudentGrades Grades1 = new StudentGrades(50);
      StudentGrades Grades2 = new StudentGrades(50);
      
      //check sorting method
		Grades1.sortScores();
		System.out.println("Sorted Scores are: " + Grades1.toString() + "\n");
      
      //check if objects equality works
      System.out.println("Checking if Grades1 is the same as Grades2: " + Grades1.equals(Grades2));
      System.out.println("Checking if Grades1 is the same as Grades1: " + Grades1.equals(Grades1) + "\n");
      
      //print highest grade
      System.out.println("The highest score was: " + Grades1.getHighest());
      
      //print the mean, median, and mode
      System.out.println("Score mean: " + Grades1.getAverage()
            + "\nScore median: " + Grades1.getMedian() + "\nScore mode(s): " + Arrays.toString(Grades1.getModes()));
	}
}
/*
* Name:Hayvin Bolton
* Date:1/19/2020
* Question number: 3
* Description: Everything about student grades on a test
*/
package StudentGrades;
import java.util.*;

public class StudentGrades
{
   private int[] testScores;
   
   //Constructor that radnomly generates all students grades
   public StudentGrades(int studentCount) 
   {
      testScores = new int[studentCount];
      for (int i=0; i < studentCount; i++)
      {
         testScores[i] = (int) Math.floor(Math.random() * 101); //returns a random integer between 0 and 100 including both 0 and 100 (math.floor convers the random number in the range 0,100 rounding to smaller number)
      }
   }
   
   //To String Method to return all test scores of the students in a string
   public String toString() 
   {
      String retVal = "Test scores for this class: ";
      for (int i : testScores) 
      {
         retVal += i + ", ";
      }
      return retVal;
   }
	
   // equals method
   public boolean equals(StudentGrades other)
   {
      return other == this;
   }
	
   //Accessor Method (get method to return value of a private field)
   //returns students testscores
   public int[] getScores()
   {
      return this.testScores;
   }
	
   //Mutator Method (set method, no return type, used to set value of private field)
   //sets the students testscores
   public void setScores(int[] testScores) 
   {
      this.testScores = testScores;
   }
	
   //Returning an Array of grades sorted in accesding order
   public int[] sortScores() 
   {
      int n = testScores.length; 
      for (int i = 0; i < n-1; i++) 
      {
         for (int j = 0; j < n-i-1; j++) 
         {
            if (testScores[j] > testScores[j+1]) 
            { 
            	// swap testScores[j+1] and testScores[j] 
               int temp = testScores[j]; 
               testScores[j] = testScores[j+1]; 
               testScores[j+1] = temp; 
            }
         }
      }
      return testScores;
   }
	
   //Method returning highest grade
   public int getHighest()
   {
      int[] sorted = sortScores();
      return sorted[sorted.length - 1];
   }
	
   //Method returning the average grade
   public int getAverage() 
   {
      int sum = 0;
      for (int i = 0; i < testScores.length; i++)
      {
         sum += testScores[i];
      }
      return sum / testScores.length;
   }
	
   //Method to return the median grade
   public int getMedian()
   {
      int[] sorted = sortScores();
      return sorted[sorted.length/2];
   }
   
  //Method to return the mode or modes if there are multiple
   private Integer[] getMultiModes(){
      List<Integer> modes = new ArrayList<Integer>();
      int maxCount=0;   
      for (int i = 0; i < testScores.length; ++i){
         int count = 0;
         for (int j = 0; j < testScores.length; ++j){
            if (testScores[j] == testScores[i]) ++count;
         }
         if (count > maxCount) {
            maxCount = count;
            modes.clear();
            modes.add( testScores[i] );
         } 
         else if ( count == maxCount)
         {
            modes.add( testScores[i] );
         }
      }
      
      return modes.toArray(new Integer[modes.size()]);
   }
   
   private Integer[] dedupeArray(Integer[] arr) {
      List<Integer> retArray = new ArrayList<Integer>();
      int currVal = -1;
      for (Integer a : arr) {
         if (currVal != a) retArray.add(a);
         currVal = a;
      }
      return retArray.toArray(new Integer[retArray.size()]);
   }

   
      
   public Integer[] getModes() {
      return dedupeArray(getMultiModes());
   }

}

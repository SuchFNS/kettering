import java.util.Scanner;

public class driver
{

   public static void main(String args[])
   {
      //initializers
      Queue q = new Queue();
      Stack s = new Stack();
      Scanner scan = new Scanner(System.in);
      
      System.out.println("Please enter something of the form w$w'\n" + 
                         "Where the form is: " +
                         "{w$w': w is a possibly empty string of characters other than $, w'= reverse(w)}\n");
      String input = scan.next();
      
      //populate the queue and stack based on the $ sign location
      boolean signFound = false;
      if (input == null)
      {
         System.out.println("The strings do not fit the w$w' language.");
      }
      else
      {
         for (int i = 0; i < input.length(); i++)
         {
            char curr = input.charAt(i);
            if (curr == '$') 
            {
               signFound = true;
               continue;
            }
            //add to queue
            if (signFound)
            {
               q.enqueue(curr);
            //push to stack
            }
            else
            {
               s.push(curr);
            }
         }
      }
      
      //compare the stack and queue to find if they are equal
      while (q.peek() != null && s.peek() != null)
      {
         if (q.dequeue() != s.pop())
         {
            System.out.println("This string does not fit the language definition");
            return;
         }
      }
      System.out.println("This string fits the definition");

   }

}
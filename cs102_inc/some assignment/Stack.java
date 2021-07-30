public class Stack
{

   public class Node
   {
      private Node next;
      private Object value;
   }
   
   private Node top;
   private int totalNodes = 0;
   
   //constructor
   public Stack()
   {
      this.top = null;
   }

   public boolean isEmpty()
   {
      return top == null;
   } 

   public void push(Object input)
   {
		Node temp = new Node();
      temp.value = input;
      temp.next = top;
		top = temp;
   }
   
   public Object peek()
   {
      if (!isEmpty())
      {
         return top.value;
      }
      else return null;
   }
   
   //also return value when popping from top of stack
   public Object pop()
   {
      Object tempVal = top.value;
      if (!isEmpty())
      {
         top = top.next;
         return tempVal;
      }
      else return null;
   }

}
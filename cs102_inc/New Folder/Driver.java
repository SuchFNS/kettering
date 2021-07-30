public class Driver{

   public static void main(String args[]){
      //values needed for heap
      MaxHeap heap = new MaxHeap(100);
      
      //insert values into heap
      heap.insert(20);
      heap.insert(7);
      heap.insert(1);
      heap.insert(54);
      heap.insert(10);
      heap.insert(15);
      heap.insert(90);
      heap.insert(23);
      heap.insert(77);
      
      heap.print();
      System.out.println("\nThe max of the heap is: " + heap.popHeap() + "\n");
      heap.print();
      
   }

}
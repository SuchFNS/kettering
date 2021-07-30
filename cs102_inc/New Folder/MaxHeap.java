public class MaxHeap{

   int[] heapArr;
   int size;
   int maxSize;
   
   public MaxHeap(int maxSize) 
   { 
       this.maxSize = maxSize; 
       this.size = 0; 
       heapArr = new int[this.maxSize + 1]; 
       heapArr[0] = Integer.MAX_VALUE; 
   } 

//left child node = 2*position
//right child node = (2*position) + 1
   private void heapify(int pos) 
   { 
        //check if current node is a leaf
        if (pos > (size / 2) && pos <= size) 
            return; 
  
        if (heapArr[pos] < heapArr[2 * pos] 
            || heapArr[pos] < heapArr[(2 * pos) + 1]) { 
  
            if (heapArr[2 * pos] 
                > heapArr[(2 * pos) + 1]) { 
                swap(pos, 2 * pos); 
                heapify(2 * pos); 
            } 
            else { 
                swap(pos, (2 * pos) + 1); 
                heapify((2 * pos) + 1); 
            } 
        } 
   }  

   public void swap(int first, int last){
      int temp;
      temp = heapArr[first];
      heapArr[first] = heapArr[last];
      heapArr[last] = temp;
   }
   
   public void insert(int element) 
   { 
         heapArr[++size] = element; 
      
      // Traverse up and fix violated property 
      int current = size; 
      while (heapArr[current] > heapArr[current / 2]) { 
          swap(current, current / 2); 
          current = current / 2; 
      } 
   } 
   
   //remove from the top of the heap
   public int popHeap(){
      int pop = heapArr[1];
      heapArr[1] = heapArr[size--];
      heapify(1);
      return pop;
   }
   
  public void print() 
    { 
        for (int i = 1; i <= size / 2; i++) { 
            System.out.print( 
                " PARENT : " + heapArr[i] 
                + " LEFT CHILD : " + heapArr[2 * i] 
                + " RIGHT CHILD :" + heapArr[2 * i + 1]); 
            System.out.println(); 
        } 
    } 
   

}
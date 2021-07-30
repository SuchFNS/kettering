import java.lang.Math;

public class Driver{
	
	public static void main(String[] args)
	{
		BinarySearchTree tree = new BinarySearchTree();

		int numOfNodes = (int)(Math.random() * 100);
      System.out.println("There are " + numOfNodes + " nodes in the tree.\n");
      
      for (int i = 0; i < numOfNodes; i++){
         tree.insert((int)(Math.random() * 1000));         
      }

      System.out.println("Height of tree is: " + tree.getHeight());
      System.out.println("The maximum value in the tree is: " + tree.getMax());
      System.out.println("The sum of the tree is: " + tree.getSum());
      System.out.println("There are " + tree.oneChild() + " one child nodes");
	}
}
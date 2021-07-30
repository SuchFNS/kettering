// Java program to demonstrate 
// insert operation in binary
// search tree
class BinarySearchTree {

	/* Class containing left 
	and right child of current node
	* and value value*/
	class Node 
	{
		int value;
		Node left;
      Node right;

		public Node(int item)
		{
			value = item;
			left = right = null;
		}
	}

	// Root of BST
	Node root;

	// Constructor
	BinarySearchTree() 
	{ 
		root = null; 
	}

	// This method mainly calls insertRec()
	void insert(int value) 
	{ 
		root = insertRec(root, value); 
	}

	/* A recursive function to 
	insert a new value in BST */
	private Node insertRec(Node root, int value)
	{

		/* If the tree is empty,
		return a new node */
		if (root == null) 
		{
			root = new Node(value);
			return root;
		}

		/* Otherwise, recurse down the tree */
		if (value < root.value){
			root.left = insertRec(root.left, value);
		}else if (value > root.value){
			root.right = insertRec(root.right, value);
      }

		/* return the (unchanged) node pointer */
		return root;
	}
  
   int getHeight(){
      return getHeightRec(this.root);
   }

   private int getHeightRec(Node root){
      if (root == null){
         return -1;
      }else{
         //find height of each subtree
         int left = getHeightRec(root.left);
         int right = getHeightRec(root.right);
         //choose greater height
         if (left > right){
            return left + 1;
         }else return right + 1;
      }
   }

   int getMax(){
      return getMaxRec(this.root);
   }
   
   private int getMaxRec(Node root){
      if (root.right == null){
         return root.value;
      }
      return getMaxRec(root.right);
   }
   
   int getSum(){
      return getSumRec(this.root);
   }
   private int getSumRec(Node root){
      if (root == null){
         return 0;
      }else{
         return (root.value + getSumRec(root.right) + getSumRec(root.left));
      }
   }
   
   int oneChild(){
      return oneChildRec(this.root);
   }
   private int oneChildRec(Node root){
      if (root == null){
         return 0;
      }
      
      if ((root.left == null && root.right != null) || (root.left != null && root.right == null)){
         return oneChildRec(root.right) + oneChildRec(root.left) + 1;
      }else return oneChildRec(root.right) + oneChildRec(root.left);
   }
}

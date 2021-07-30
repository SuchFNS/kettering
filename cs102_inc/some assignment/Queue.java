public class Queue
{
    public class Node 
    {
        public Node(Object o) 
        {
            this.value = o;
        }
        
        public Node next;
        public Object value;
    }
    
    private Node firstNode;
    private Node lastNode;
    private int totalNodes = 0;
    
    public boolean isEmpty() 
    {
        return totalNodes == 0;
    }
    
    public void dequeueAll() 
    {
        if (this.isEmpty()) return;
        this.totalNodes = 0;
        this.firstNode = null;
        this.lastNode = null;
    }
    
    public void enqueue(Object item) 
    {
        // empty case
        if (totalNodes == 0) 
        {
            totalNodes = 1;
            Node n = new Node(item);
            this.firstNode = n;
            this.lastNode = n;
            return;
        }
        // not empty case
        totalNodes += 1;
        this.lastNode.next = new Node(item);
        this.lastNode = this.lastNode.next;
        return;
    }
    
    public Object dequeue()
    {
        // empty case
        if (this.isEmpty()) return null;
        Node retVal = this.firstNode;
        this.firstNode = this.firstNode.next;
        this.totalNodes -= 1;
        return retVal.value;
    }
    
    public Object peek() 
    {
        if (this.isEmpty()) return null;
        return this.firstNode.value;
    }
    
    public static void main(String[] args)
    {
        Queue q = new Queue();
        q.enqueue("hello");
        q.enqueue("2");
        q.enqueue("3");
        q.enqueue("4");
        System.out.println(q.peek());
        System.out.println(q.isEmpty());
        System.out.println(q.dequeue());
        System.out.println(q.dequeue());
        System.out.println(q.dequeue());
        System.out.println(q.dequeue());
        System.out.println(q.dequeue());
        q.enqueue("hello");
        q.enqueue("2");
        q.enqueue("3");
        q.enqueue("4");
        q.dequeueAll();
        System.out.println(q.dequeue());
    }
}

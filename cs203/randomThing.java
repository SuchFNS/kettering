public class randomThing {
   public static void main(String[] args) {

      int i = 0;
      while(i < 20){
         System.out.println(i);
         //increment
         i++;
      }
      System.out.println("_______________");
      recursiveFunction(0);
   }

   public static int recursiveFunction(int input){
      if (input < 20){
         System.out.println(input);
         input++;
         recursiveFunction(input);
      }else return input;
      return -1;
   }
}
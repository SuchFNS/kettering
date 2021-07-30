public class Bag{

public static void main(String args[]){
   stringReverse("Computer");
}

public static String stringReverse(String word){

   if (word.length() <= 1){
      System.out.println(word);
      return null;
   }else{
      stringReverse(word.substring(1));
      System.out.println(word.charAt(0));
      return null;
   }

}

}
/* CheckingAccount Client to test your SavingAccount methods.
  
*/

public class CheckingAccountClient
{
   public static void main( String [] args )
   {
     CheckingAccount c3 = new CheckingAccount( 100.00, 7.50 );
     System.out.println( "New checking account:\n"
                          + c3.toString( )
                          + "; monthly fee is "
                          + c3.getMonthlyFee( ) );

     c3.applyMonthlyFee( );  // charge the fee to the account
     System.out.println( "\nAfter charging monthly fee:\n"
                          + c3.toString( )// supper class, is a method of BankAccount
                          + "; monthly fee is "
                          + c3.getMonthlyFee( ) ); // subclass, is a method of checkingAccount
     
     SavingsAccount person = new SavingsAccount();
     SavingsAccount saver = new SavingsAccount(20000.00, 8.50);
     saver.applyInterest();
     System.out.println(saver.toString());
   }
}

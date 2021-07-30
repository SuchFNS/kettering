/* CheckingAccount class to use for your lab
   
*/

public class CheckingAccount extends BankAccount
{
   public final double DEFAULT_FEE = 5.00;
   private double monthlyFee;

   /** default constructor
   *   explicitly calls the BankAccount default constructor
   *   sets monthlyFee to default value
   */
   public CheckingAccount( )
   {
       super( ); // optional
       monthlyFee = DEFAULT_FEE;
   }

   /** overloaded constructor
   *  calls BankAccount overloaded constructor
   *  @param  balance  starting balance
   *  @param  monthlyFee starting monthly fee
   */
   public CheckingAccount( double balance,
                           double monthlyFee )
   {
      super( balance ); // call BankAccount constructor
      setMonthlyFee( monthlyFee );
   }

   /** applyMonthlyFee method
   * charges the monthly fee to the account
   * @return a reference to this object
   */
   public CheckingAccount applyMonthlyFee( )
   {
     withdraw( monthlyFee );     
     return this;
   }

   /** accessor method for monthlyFee
   *  @return  monthlyFee
   */
   public double getMonthlyFee( )
   {
     return monthlyFee;
   }

   /** mutator method for monthlyFee
   *  @param newMonthlyFee new value for monthlyFee
   *  @return a reference to this object
   */
   public CheckingAccount setMonthlyFee( double monthlyFee )
   {
     if ( monthlyFee >= 0.0 )
        this.monthlyFee = monthlyFee;
     
     return this;
   }
}

#Debug this program.

TAX = 0.06

def sales_tax(total):
    total = total * TAX
    return total

def main():
    print("Sales Tax Calculator\n")
    total = float(input("Enter total: "))
    total_after_tax = round(total + sales_tax(total), 2)
    print("Total after tax: ", total_after_tax)
    

main()

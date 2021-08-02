cost = float(input('input the cost of the meal '))
tip = cost * .18
tax = cost * .07

print('the tip is: ' + str(tip))
print('the tax is: ' + str(tax))
print('Your total cost is: ' + str(cost+tip+tax))

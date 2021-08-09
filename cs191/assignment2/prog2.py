print('By: Colin Quinn')
print('CS 191 Assignment 2')
print('Due: August 13th 2021\n')

# The goal of this program is to find
# a magic date from user input.
# Check to make sure user inputs valid data as well.

#check month
monthValid = 0
while not(monthValid):
	month = int(input('Input the month (MM): '))
	if (month < 1 or month > 12):
		print('err: input a valid month between range 1-12.')
	else:
		monthValid = True

#check day
dayValid = False
while not(dayValid):
	day = int(input("Input the day (DD): "))
	#check months with 31 days
	if (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12) and (day < 1 or day > 31):
		print('err: input a valid day between range 1-31.')
	#check months with 30 days
	elif (month == 4 or month == 6 or month == 9 or month == 1) and (day < 1 or day > 30):
		print('err: input a valid day between range 1-30.')
	#check months with 28 days
	elif (month == 2) and (day < 1 or day > 28):
		print('err: input a valid day between range 1-28.')
	else:
		dayValid = True

#check year
year = -1
while year < 0 or year > 99:
    year = int(input('Please enter a year number (YY): '))
    if (year < 0 or year > 99):
        print('err: input a year between 0-99')

print('\tThis date is: ' + str(month).rjust(2, '0') + '/' + str(day).rjust(2, '0') + '/' + str(year).rjust(2, '0'))
if (month * day == year):
    print('\tYour date is magical!')
else:
    print('\tYour date is not magic..')
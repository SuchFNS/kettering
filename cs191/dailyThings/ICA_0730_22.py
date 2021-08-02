print('List of months: January, February, March, April, May, June, July, August, September, October, November, December')

month = input('Input a month: ')

if (month.upper() == 'JANUARY' or month.upper() == 'MARCH' or month.upper() == 'MAY' or
	month.upper() == 'JULY' or month.upper() == 'AUGUST' or month.upper() == 'OCTOBER' or
	month.upper() == 'DECEMBER'
	):
	print('There are 31 days this month')
elif (month.upper() == 'APRIL' or month.upper() == 'JUNE' or month.upper() == 'SEPTEMBER' or
	  month.upper() == 'NOVEMBER'
	):
	print('There are 30 days this month')
elif (month.upper() == 'FEBRUARY'):
	print('There are 28 days this month')
else:
	print('You input a wrong month, please try again')
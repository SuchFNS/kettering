year = int(input('input the year as [YYYY]:' ))
month = int(input('input the month [1-12]: '))
day = int(input('input the day [1-31]: '))

#new years
if day == 31 and month == 12:
	print('The next day is: ', year+1, '-01-01')
elif day == 31:
	print('The next day is: ', year, '-', month+1, '-01')
else:
	print('The next day is: ', year, '-', month, '-', day+1)
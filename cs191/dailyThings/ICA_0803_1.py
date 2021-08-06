num = int(input("Please input a positive number: "))

while num < 0:
	num = int(input('ERROR: number must be positive\nPlease input a positive number: '))

if num % 2 == 0:
	print('this number is even')
else:
	print('this number is odd')

x = int(input('input a number: '))
y = int(input('input a number: '))
z = int(input('input a number: '))

if (x < y and y < z) or (z < y and y < x):
	print('The median is: ', y)
elif (y < x and x < z) or (z < x and x < y):
	print('The median is: ', x)
elif (x < z and z < y) or (y < z and z < x):
	print('The median is: ', z)
else:
	print('Could not compute median')
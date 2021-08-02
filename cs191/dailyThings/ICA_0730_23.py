x = int(input('Input side 1 of triangle: '))
y = int(input('Input side 2 of triangle: '))
z = int(input('Input side 3 of triangle: '))

if x == y and y == z:
	print('The triangle is equilateral')
elif (x == y and y != z) or (x == z and z != y):
	print('The triangle is isoceles')
else: 
	print('The triangle is scalene')
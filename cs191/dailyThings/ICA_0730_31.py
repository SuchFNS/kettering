age = int(input('Input someones age: '))

if age <= 1:
	print('They are an infant')
elif age > 1 and age < 13:
	print('They are a child')
elif age >= 13 and age < 20:
	print('They are a teenager')
else:
	print('They are an adult')
age = int(input('input a dog\'s age: '))

dogAge = 0.0
for i in range(age+1):
	if i <= 2 and i != 0:
		dogAge += 10.5
	elif i > 2:
		dogAge += 4

print('Your dog is ', dogAge, ' years old')
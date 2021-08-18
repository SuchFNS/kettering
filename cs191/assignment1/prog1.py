print('CS 191 Program 1')
print('By Colin Quinn')
print('Due: July 30, 2021')

#program takes two numbers as input,
#then calculates the percentage of each number
print('\t\t\tMale and Female Percentages')
numMale = int(input('Enter the number of male students in the class: '))
numFemale = int(input('Enter the number of female students in the class: '))
total = numMale + numFemale

#prints for formatting and looking nicer
print('--------------------------------------------------------')
print('\t\t\tTotal number of students: ', total)
print('--------------------------------------------------------')

#convert numbers to rounded decimal percentages
percentMale = round(numMale/total * 100, 2)
percentFemale = round(numFemale/total * 100, 2)
#output results
print('\t\tMale: ', percentMale, '%')
print('\t\tFemale: ', percentFemale, '%')

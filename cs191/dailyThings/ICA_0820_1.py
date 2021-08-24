#Colin Quinn

def main():
    miles = float(input('Enter number of miles: '))
    feet = miles2Feet(miles)
    print(miles, 'miles =', feet, 'feet\n')

def miles2Feet(num):
    return num * 5280

if __name__ == "__main__":
    main()
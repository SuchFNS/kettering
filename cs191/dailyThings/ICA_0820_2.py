#Colin Quinn

import string

def main():
    choice = convMenu().upper()
    if choice == 'A':
        feet = float(input('input number of feet: '))
        meters = feet2Meters(feet)
        print(feet, 'feet =', round(meters, 2), 'meters\n')
    elif choice == 'B':
        meters = float(input('input number of meters: '))
        feet = meters2Feet(meters)
        print(meters, 'meters =', round(feet, 2), 'feet')

def feet2Meters(num):
    return num / 3.2808

def meters2Feet(num):
    return num * 3.2808

def convMenu():
    print('Conversions Menu:\n\tA. Feet to Meters\n\tB. Meters to Feet\n')
    return input('Select a conversion (A or B): ')

if __name__ == "__main__":
    main()
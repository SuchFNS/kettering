#Colin Quinn

import string
from conversions import *

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

if __name__ == "__main__":
    main()
def feet2Meters(num):
    return num / 3.2808

def meters2Feet(num):
    return num * 3.2808

def convMenu():
    print('Conversions Menu:\n\tA. Feet to Meters\n\tB. Meters to Feet\n')
    return input('Select a conversion (A or B): ')
# By Colin Quinn
# Intro to Python

def main():
    print("Prime number checker\n")
    num = getInput()
    factors = getFactors(num)
    checkPrime(factors, num)

def checkPrime(factors, nIn):
    if factors == 2:
        print(nIn, "is a prime number\n")
    else:
        print(nIn, "is NOT a prime number")
        print("it has", factors, "factors\n")

def getFactors(n):
    numFactors = 2
    for i in range(2, int(n/2)+1):
        if (n % i) == 0:
            numFactors += 1
            continue

    return numFactors

def getInput():
    num = -1
    while num <= 1 or num > 5000:
        num = int(input("Please enter an integer betwen 1 and 5000: "))
        if num <= 1 or num > 5000:
            print("Invalid value, please try again.")
        else:
            return num


if __name__ == "__main__":
    main()
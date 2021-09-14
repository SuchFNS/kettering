from random import randint

def main():
    name = input("Please enter your full name: ")
    ssn = []
    for i in range(0, 9):
        ssn.append(randint(0,9))
    print("your name is:", name)
    print("Your SSN is: ", end="")
    for i in range(0, 9):
        if i == 3 or i == 5:
            print("-",end="")
            print(ssn[i],end="")
        else:
            print(ssn[i],end="")
    print()


if __name__ == "__main__":
    main()
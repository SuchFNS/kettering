import random

#print the header
def printHeader():
    print('CS 191 Assignment 3')
    print('By Colin Quinn')
    print('Due 7th Friday\n') 

#print the winner
def endGame(outcome):
    if outcome == 1:
        print('You won!\n')
    elif outcome == 2:
        print('The computer won.. sorry..\n')

#Run the main course of the game
def mainLoop():
    compChoice = random.randrange(3) + 1
    userChoice = int(input('Enter your choice:\n\t1: Rock\n\t2: Paper\n\t3: Scissors\n'))
    #validate user input
    if userChoice < 1 or userChoice > 3:
        return -1
    #convert selections to print
    printSelections(userChoice, compChoice)
    #check who wins the game
    return checkWinner(userChoice, compChoice)

#return who wins the game  
def checkWinner(user, comp):
    #they both guess the same option
    if user == comp:
        return 0
    #cases where the user wins
    elif (user == 1 and comp == 3) or (user == 2 and comp == 1) or (user == 3 and comp == 2):
        return 1
    #cases where the computer wins
    elif (comp == 1 and user == 3) or (comp == 2 and user == 1) or (comp == 3 and user == 2):
        return 2

#display each selection
def printSelections(user, comp):
    #convert numbers to printed strings for user's choice
    if (user == 1):
        print('You chose: Rock')
    elif (user == 2):
        print('You chose: Paper')
    elif(user == 3):
        print('You chose: Scissors')
    #convert numbers to printed strings for computer's choice
    if (comp == 1):
        print('Computer chose: Rock\n')
    elif (comp == 2):
        print('Computer chose: Paper\n')
    elif(comp == 3):
        print('Computer chose: Scissors\n')

#main for the program
def main():
    printHeader()
    outcome = mainLoop()
    while(outcome == 0 or outcome == -1):
        if outcome == -1:
            print('You have enterd an invalid option, please enter a number 1-3.')
        elif outcome == 0:
            print('You tied! Try again..\n')
            outcome = mainLoop()
    endGame(outcome)

#if main is found, run it
if __name__ == "__main__":
    main()
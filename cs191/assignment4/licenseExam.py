correctAnswers = ['A','C','A','A','D','B','C','A','C','B']

def main():
    printHeader()
    answerList = getAnswers()
    wrongAnswers = gradeAnswers(answerList)
    printResults(wrongAnswers)

def printResults(incorrect):
    print()
    numCorrect = 10 - len(incorrect)
    if numCorrect < 7:
        print('Sorry, you failed the test')
    else:
        print('Congratulations! You passed the test')
    print('You got', numCorrect, 'answers right')
    print('And', len(incorrect), 'answers incorrect')
    print('The incorrect questions were:',end='')
    print(incorrect)

def gradeAnswers(answers):
    wrongAnswers = []
    for i in range(10):
        if correctAnswers[i] != answers[i]:
            wrongAnswers.append(i)
    return wrongAnswers

def getAnswers():
    answers = []
    for i in range(10):
        validAnswer = 0
        while not validAnswer:
            selection = input("Enter your answer for question " + str(i+1) + ": ").upper()
            if selection == "A" or selection == "B" or selection == "C" or selection == "D":
                answers.append(selection)

                validAnswer = 1
            else:
                print("Invalid answer, try again")
    return answers

def printHeader():
    print("CS 191 - Assignment 4")
    print("By Colin Quinn\n")

if __name__ == "__main__":
    main()